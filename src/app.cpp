#include "app.h"
#include "app_utils.h"

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_vulkan.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <metavision/sdk/core/algorithms/periodic_frame_generation_algorithm.h>
#include <metavision/sdk/core/utils/cd_frame_generator.h>
#include <opencv2/opencv.hpp>

#include <filesystem>

namespace App {

namespace State {

static auto isDockSpaceLayoutCreated = false;
static auto isRecording = false;
static char fileSavePathBuf[BUFSIZ] = {0};

} // namespace State

static const char *const TOOL_PANE = "Tool";
static const char *const CAMERA_PANE = "Camera Preview";
static const char *const LOG_PANE = "Log";
static const ImGuiWindowFlags paneWindowFlags = ImGuiWindowFlags_NoCollapse;
static const char *const DOCKSPACE_NAME = "MyDockSpace";
static const ImGuiDockNodeFlags dockSpaceNodeFlags =
    (ImGuiDockNodeFlags_)ImGuiDockNodeFlags_NoWindowMenuButton | ImGuiDockNodeFlags_PassthruCentralNode;

// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
// because it would be confusing to have two docking targets within each others.
static const ImGuiWindowFlags dockSpaceWindowflags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
                                                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                                                     ImGuiWindowFlags_NoMove;

static LogWidget log;

App::App(const int argc, char *const *argv) {
    printf("Initializing app\n");

    this->parseArgs(argc, argv);
    auto sources = Metavision::Camera::list_online_sources();
    auto usbCameras = sources[Metavision::OnlineSourceType::USB];

    for (auto camera : usbCameras) {
        printf("Found camera: %s\n", camera.c_str());
        this->cameras_.emplace_back(CameraUtil::from_serial(camera, this->engine_));
    }

    for (auto file : this->eventFiles) {
        printf("Open event file: %s\n", file.c_str());
        this->cameras_.emplace_back(CameraUtil::from_file(file, this->engine_));
    }

    for (auto &camera : cameras_) {
        camera->start();
    }
}

App::~App() { printf("Exit\n"); }

void App::run() {
    log.AddLog("Welcome!\n");

    this->engine_.onFrame([&](Engine::Engine *, VkCommandBuffer &renderCommmandBuffer) {
        for (auto &camera : this->cameras_) {
            camera->update();
        }
        this->render(renderCommmandBuffer);
    });

    this->engine_.run();
}

void createDockSpaceLayout() {
    ImGuiID dockSpaceID = ImGui::GetID(DOCKSPACE_NAME);
    // Clear out existing layout
    ImGui::DockBuilderRemoveNode(dockSpaceID);
    // Add empty node as main node
    ImGui::DockBuilderAddNode(dockSpaceID, dockSpaceNodeFlags | ImGuiDockNodeFlags_DockSpace);
    // Main node should cover entire window
    ImGui::DockBuilderSetNodeSize(dockSpaceID, ImGui::GetWindowSize());

    // Get id of main dock space and split it into left and right areas
    ImGuiID dockMain = dockSpaceID;
    // ImGuiID dockLeft, dockRight, dockRightTop, dockRightBottom;
    ImGuiID dockTop, dockBottom, dockBottomLeft, dockBottomRight;
    ImGui::DockBuilderSplitNode(dockMain, ImGuiDir_Down, 0.4f, &dockBottom, &dockTop);
    ImGui::DockBuilderSplitNode(dockBottom, ImGuiDir_Left, 0.5f, &dockBottomLeft, &dockBottomRight);

    // Place windows into the dock space
    ImGui::DockBuilderDockWindow(CAMERA_PANE, dockTop);
    ImGui::DockBuilderDockWindow(TOOL_PANE, dockBottomLeft);
    ImGui::DockBuilderDockWindow(LOG_PANE, dockBottomRight);
    ImGui::DockBuilderFinish(dockSpaceID);
}

void inline drawToolPane(App *app) {
    ImGui::Begin(TOOL_PANE, nullptr, paneWindowFlags);

    ImGui::SeparatorText("Sources");

    if (app->cameras_.empty()) {
        ImGui::Text("No cameras found.");
    } else {
        if (ImGui::BeginTable("Camera Table", 3,
                              ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_BordersOuterH |
                                  ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersOuterV |
                                  ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg)) {
            char buf[BUFSIZ] = {0};

            // Setup table header and column sizing policy
            {
                ImGui::TableSetupColumn("Index", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn("Source", ImGuiTableColumnFlags_WidthStretch);
                ImGui::TableSetupColumn("Operation", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableHeadersRow();
            }

            // Table body
            for (size_t i = 0; i < app->cameras_.size(); ++i) {
                const auto &camera = app->cameras_[i];
                ImGui::TableNextRow();

                ImGui::TableNextColumn();
                ImGui::Text("%lu", i);

                ImGui::TableNextColumn();
                ImGui::Text("%s", camera->getSource().source.c_str());
                if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort | ImGuiHoveredFlags_NoSharedDelay)) {
                    ImGui::SetItemTooltip("%s", camera->getSource().source.c_str());
                }

                ImGui::TableNextColumn();
                if (camera->paused()) {
                    sprintf(buf, "##%lu", i);
                    if (ImGui::Button(buf)) {
                        camera->resume();
                    }
                    ImGui::SetItemTooltip("Resume");
                } else {
                    sprintf(buf, "##%lu", i);
                    if (ImGui::Button(buf)) {
                        camera->pause();
                    }
                    ImGui::SetItemTooltip("Pause");
                    ImGui::SameLine();
                    sprintf(buf, "##%lu", i);
                    ImGui::Button(buf);
                    ImGui::SetItemTooltip("Start recording");
                }
            }
            ImGui::EndTable();
        }

        ImGui::SeparatorText("Recording");
        static bool isEditingFilename = false;
        static double recordingStartTime = ImGui::GetTime();
        static std::vector<char[9000]> promptCameraSavePaths(app->cameras_.size());

        // Recording
        if (State::isRecording) {
            if (ImGui::Button("Stop recording")) {
                State::isRecording = false;
                for (auto &camera : app->cameras_) {
                    camera->stopRecording();
                }
                log.AddLog("Finished recording.\n");
            }
            ImGui::SameLine(0.0f, 20.0f);
            ImGui::Text("Recording: %.3lfs", ImGui::GetTime() - recordingStartTime);
            goto PartEnd;
        }

        // Prepare for recording (editing filename)
        if (isEditingFilename) {
            ImGui::InputText("Filename", State::fileSavePathBuf, sizeof(State::fileSavePathBuf),
                             ImGuiInputTextFlags_EnterReturnsTrue);
            bool confirm = ImGui::IsItemDeactivatedAfterEdit() || ImGui::Button("Confirm");
            ImGui::SameLine();
            bool cancel = ImGui::Button("Cancel");
            if (cancel) {
                isEditingFilename = false;
                log.AddLog("Cancelled editing filename.\n");
                goto PartEnd;
            }
            if (confirm) {
                // Check if filename is not empty
                if (strlen(State::fileSavePathBuf) == 0) {
                    log.AddLog("Filename cannot be empty.\n");
                    goto PartEnd;
                }

                // Check if file already exists
                for (size_t i = 0; i < app->cameras_.size(); ++i) {
                    sprintf(promptCameraSavePaths[i], "%s_camera_%zu.raw", State::fileSavePathBuf, i);
                    if (std::filesystem::exists(promptCameraSavePaths[i])) {
                        log.AddLog("File %s already exists, please choose a different name.\n",
                                   promptCameraSavePaths[i]);
                        goto PartEnd;
                    }
                }

                // Actually start recording with the provided filename
                isEditingFilename = false;
                for (size_t i = 0; i < app->cameras_.size(); ++i) {
                    strcpy(app->cameras_[i]->savePath, promptCameraSavePaths[i]);
                }
                memset(State::fileSavePathBuf, 0, sizeof(State::fileSavePathBuf)); // Clear the buffer
                State::isRecording = true;
                log.AddLog("Start recording:\n");
                for (auto &camera : app->cameras_) {
                    camera->startRecording(camera->savePath);
                    log.AddLog(" Stream: %s\n", camera->savePath);
                }
                recordingStartTime = ImGui::GetTime();
            }
        } else {
            // Button for prompting editing filename
            if (ImGui::Button("Start recording for all")) {
                isEditingFilename = true;
                log.AddLog("Start editing filename\n");
            }
        }
    }

PartEnd:
    ImGui::End();
}

class GridUtil {
  public:
    uint32_t columns = 2;
    ImVec2 intrinsicSize{};         // x -> width, y -> height
    std::vector<ImVec2> imageSizes; // Computed sizes of images in the grid
    float intrinsicSpacing = 0.0f;  // Intrinsic spacing between images
    float spacing = 0.0f;           // Computed spacing between images

    ImVec2 updateIntrinsicSize(App *app, uint32_t _spacing) {
        size_t cameraCount = app->cameras_.size();
        this->intrinsicSize = ImVec2(0, 0);
        this->imageSizes.resize(cameraCount);
        this->intrinsicSpacing = (float)_spacing;

        if (cameraCount == 0) {
            return intrinsicSize;
        }

        if (cameraCount == 1) {
            intrinsicSize.x = app->cameras_[0]->getWidth();
            intrinsicSize.y = app->cameras_[0]->getHeight();
        } else if (cameraCount > 1) {
            for (size_t i = 0; i < cameraCount; i += columns) {
                // From the first camera at each row
                uint32_t rowHeight = 0;
                uint32_t rowWidth = 0;
                size_t j = 0;
                for (; j < columns && (i + j) < cameraCount; ++j) { // For each camera in the row
                    rowWidth += app->cameras_[i + j]->getWidth();
                    rowHeight = std::max(rowHeight, app->cameras_[i + j]->getHeight());
                }
                rowWidth += (j - 1) * _spacing; // Add spacing between cameras in the row
                intrinsicSize.x = std::max(intrinsicSize.x, (float)rowWidth);
                if (i >= columns) {              // If this is not the first row
                    intrinsicSize.y += _spacing; // Add spacing before the row
                }
                intrinsicSize.y += rowHeight;
            }
        }
        return intrinsicSize;
    }

    void updateImageSize(App *app, ImVec2 availableSize) {
        float scale = getFitScale(this->intrinsicSize, availableSize);
        // printf("intrinsicSize %f %f, availableSize %f %f, scale %f\n", this->intrinsicSize.x, this->intrinsicSize.y,
        //        availableSize.x, availableSize.y, scale);
        for (size_t i = 0; i < app->cameras_.size(); ++i) {
            this->imageSizes[i] = ImVec2(app->cameras_[i]->getWidth() * scale, app->cameras_[i]->getHeight() * scale);
        }
        this->spacing = intrinsicSpacing * scale;
    }

    float getFitScale(const ImVec2 &a, const ImVec2 &b) {
        // printf("getFitScale a: %f %f, b: %f %f\n", a.x, a.y, b.x, b.y);
        if (a.x <= 0 || a.y <= 0 || b.x <= 0 || b.y <= 0) {
            return 1.0f; // Avoid division by zero
        }

        return std::min(b.x / a.x, b.y / a.y);
    }

    void drawImageGrid(App *app) {
        for (size_t i = 0; i < app->cameras_.size(); ++i) {
            ImVec2 imageSize = this->imageSizes[i];
            if (i % this->columns != 0) {          // The image is not at the first column
                ImGui::SameLine(0, this->spacing); // Add spacing ahead the image
            } else if (i > 0) {                    // The image is at the first column but is not at the first one row
                ImGui::Dummy(ImVec2(0, 0));
            }
            ImGui::Image((ImTextureID)app->cameras_[i]->getDescriptorSet(), imageSize);
        }
    }
};

void inline drawCameraPane(App *app) {

    ImGui::Begin(CAMERA_PANE, nullptr, paneWindowFlags);

    static bool firstTime = true;
    static GridUtil gridUtil;

    if (firstTime) {
        gridUtil.updateIntrinsicSize(app, 10);
        firstTime = false;
    }

    gridUtil.updateImageSize(app, ImGui::GetContentRegionAvail());
    gridUtil.drawImageGrid(app);
    // ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

    ImGui::End();
}

void inline drawLogPane(App *) {
    ImGui::Begin(LOG_PANE, nullptr, paneWindowFlags);
    ImGui::End();
    log.Draw(LOG_PANE, nullptr);
}

void App::render(VkCommandBuffer commandBuffer) {
    ImGui_ImplVulkan_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    {
        const ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        ImGui::Begin("DockSpace Demo", nullptr, dockSpaceWindowflags);
        ImGui::PopStyleVar(3);

        // Submit the DockSpace
        {
            ImGui::DockSpace(ImGui::GetID(DOCKSPACE_NAME), ImVec2(0.0f, 0.0f), dockSpaceNodeFlags);

            if (!State::isDockSpaceLayoutCreated) {
                State::isDockSpaceLayoutCreated = true;
                createDockSpaceLayout();
            }
        }

        // Draw panes
        drawToolPane(this);
        drawCameraPane(this);
        drawLogPane(this);

        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), commandBuffer);
}

} // namespace App