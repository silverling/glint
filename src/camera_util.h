#pragma once

#include "engine.h"

#include <metavision/sdk/core/utils/cd_frame_generator.h>
#include <metavision/sdk/stream/camera.h>
#include <opencv2/core.hpp>

#include <filesystem>
#include <string>

namespace App {

enum CameraInitType {
    FromSerial = 0,
    FromFile = 1,
    UNKNOWN = 0x7fffffff,
};

struct Source {
    CameraInitType type;
    std::string source;
};

class CameraUtil {

  public:
    // static CameraUtil *from_file(const std::string &filePath, Engine::Engine &engine);
    // static CameraUtil *from_serial(const std::string &serial, Engine::Engine &engine);
    static std::unique_ptr<CameraUtil> from_serial(const std::string &serial, Engine::Engine &engine);
    static std::unique_ptr<CameraUtil> from_file(const std::string &file_path, Engine::Engine &engine);
    ~CameraUtil();

    char savePath[9000] = {0};

    // void setSavePath;

    void update();
    bool startRecording(const std::filesystem::path &file_path);
    bool stopRecording(const std::filesystem::path &file_path = std::string());

    inline void start() { camera.start(); }
    inline void stop() { camera.stop(); }
    const uint32_t &getWidth() const { return width; }
    const uint32_t &getHeight() const { return height; }
    const Source getSource() const { return source_; }
    const VkDescriptorSet &getDescriptorSet() const { return texture.descriptorSet; }
    bool paused() const { return paused_; }
    inline void pause() { paused_ = true; }
    inline void resume() { paused_ = false; }

  private:
    CameraUtil(CameraInitType type, const std::string &source, Engine::Engine &engine);

    Source source_;
    Engine::Engine &engine;
    Metavision::Camera camera;

    uint32_t width;
    uint32_t height;

    cv::Mat image;
    std::mutex imageMutex;
    Engine::Texture texture;

    Metavision::CDFrameGenerator *frameGenerator;
    std::mutex frameGeneratorMutex;

    bool paused_ = false;
};

} // namespace App