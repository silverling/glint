#include "engine_theme.h"
#include "static/index.h"

#include <imgui.h>

#include <filesystem>

// Adapted theme from https://github.com/ocornut/imgui/issues/707#issuecomment-2605839926
void config_imgui_style() {
    ImGuiStyle &style = ImGui::GetStyle();
    ImVec4 *colors = style.Colors;

    // Base Colors
    ImVec4 bgColor = ImVec4(0.10f, 0.105f, 0.11f, 1.00f);
    ImVec4 lightBgColor = ImVec4(0.15f, 0.16f, 0.17f, 1.00f);
    ImVec4 panelColor = ImVec4(0.17f, 0.18f, 0.19f, 1.00f);
    ImVec4 panelHoverColor = ImVec4(0.20f, 0.22f, 0.24f, 1.00f);
    ImVec4 panelActiveColor = ImVec4(0.23f, 0.26f, 0.29f, 1.00f);
    ImVec4 textColor = ImVec4(0.86f, 0.87f, 0.88f, 1.00f);
    ImVec4 textDisabledColor = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    ImVec4 borderColor = ImVec4(0.14f, 0.16f, 0.18f, 1.00f);

    // Text
    colors[ImGuiCol_Text] = textColor;
    colors[ImGuiCol_TextDisabled] = textDisabledColor;

    // Windows
    colors[ImGuiCol_WindowBg] = bgColor;
    colors[ImGuiCol_ChildBg] = bgColor;
    colors[ImGuiCol_PopupBg] = bgColor;
    colors[ImGuiCol_Border] = borderColor;
    colors[ImGuiCol_BorderShadow] = borderColor;

    // Headers
    colors[ImGuiCol_Header] = panelColor;
    colors[ImGuiCol_HeaderHovered] = panelHoverColor;
    colors[ImGuiCol_HeaderActive] = panelActiveColor;

    // Buttons
    colors[ImGuiCol_Button] = panelColor;
    colors[ImGuiCol_ButtonHovered] = panelHoverColor;
    colors[ImGuiCol_ButtonActive] = panelActiveColor;

    // Frame BG
    colors[ImGuiCol_FrameBg] = lightBgColor;
    colors[ImGuiCol_FrameBgHovered] = panelHoverColor;
    colors[ImGuiCol_FrameBgActive] = panelActiveColor;

    // Tabs
    colors[ImGuiCol_Tab] = panelColor;
    colors[ImGuiCol_TabHovered] = panelHoverColor;
    colors[ImGuiCol_TabActive] = panelActiveColor;
    colors[ImGuiCol_TabUnfocused] = panelColor;
    colors[ImGuiCol_TabUnfocusedActive] = panelHoverColor;

    // Title
    colors[ImGuiCol_TitleBg] = bgColor;
    colors[ImGuiCol_TitleBgActive] = bgColor;
    colors[ImGuiCol_TitleBgCollapsed] = bgColor;

    // Scrollbar
    colors[ImGuiCol_ScrollbarBg] = bgColor;
    colors[ImGuiCol_ScrollbarGrab] = panelColor;
    colors[ImGuiCol_ScrollbarGrabHovered] = panelHoverColor;
    colors[ImGuiCol_ScrollbarGrabActive] = panelActiveColor;

    // Checkmark
    colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);

    // Slider
    colors[ImGuiCol_SliderGrab] = panelHoverColor;
    colors[ImGuiCol_SliderGrabActive] = panelActiveColor;

    // Resize Grip
    colors[ImGuiCol_ResizeGrip] = panelColor;
    colors[ImGuiCol_ResizeGripHovered] = panelHoverColor;
    colors[ImGuiCol_ResizeGripActive] = panelActiveColor;

    // Separator
    colors[ImGuiCol_Separator] = borderColor;
    colors[ImGuiCol_SeparatorHovered] = panelHoverColor;
    colors[ImGuiCol_SeparatorActive] = panelActiveColor;

    // Plot
    colors[ImGuiCol_PlotLines] = textColor;
    colors[ImGuiCol_PlotLinesHovered] = panelActiveColor;
    colors[ImGuiCol_PlotHistogram] = textColor;
    colors[ImGuiCol_PlotHistogramHovered] = panelActiveColor;

    // Text Selected BG
    colors[ImGuiCol_TextSelectedBg] = panelActiveColor;

    // Modal Window Dim Bg
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.10f, 0.105f, 0.11f, 0.5f);

    // Tables
    colors[ImGuiCol_TableHeaderBg] = panelColor;
    colors[ImGuiCol_TableBorderStrong] = borderColor;
    colors[ImGuiCol_TableBorderLight] = borderColor;
    colors[ImGuiCol_TableRowBg] = bgColor;
    colors[ImGuiCol_TableRowBgAlt] = lightBgColor;

    // Styles
    style.FrameBorderSize = 1.0f;
    style.FrameRounding = 2.0f;
    style.WindowBorderSize = 1.0f;
    style.PopupBorderSize = 1.0f;
    style.ScrollbarSize = 12.0f;
    style.ScrollbarRounding = 2.0f;
    style.GrabMinSize = 7.0f;
    style.GrabRounding = 2.0f;
    style.TabBorderSize = 1.0f;
    style.TabRounding = 2.0f;

    // Reduced Padding and Spacing
    style.WindowPadding = ImVec2(5.0f, 5.0f);
    style.FramePadding = ImVec2(4.0f, 3.0f);
    style.ItemSpacing = ImVec2(6.0f, 4.0f);
    style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
}

void config_imgui_font(const GLFWvidmode *vid_mode) {
    ImGuiIO &io = ImGui::GetIO();

    io.IniFilename = nullptr;                         // We don't want to save/load .ini file
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport

    auto exe_dir = std::filesystem::canonical("/proc/self/exe").parent_path();

    // Base font sizes in standard resolution (1920x1080)
    float font_base_size = 18.0f;     // Base font size for latin characters
    float font_cjk_base_size = 24.0f; // Base font size for CJK characters
    float computed_font_size = font_base_size * (vid_mode->width / 1920.0f);
    float computed_cjk_font_size = font_cjk_base_size * (vid_mode->width / 1920.0f);

    // Load base font (e.g., Latin alphabet)
    ImFontConfig config;
    config.MergeMode = false; // First font, no merge
    config.PixelSnapH = true;
    io.Fonts->AddFontFromFileTTF((exe_dir / "res/fonts/Iosevka_Fixed/IosevkaFixed-Regular.ttf").c_str(),
                                 computed_font_size, &config, io.Fonts->GetGlyphRangesDefault());

    // Enable font merging
    config.MergeMode = true; // Merge into previous font

    // Load Chinese, Japanese, Korean (CJK) font
    io.Fonts->AddFontFromFileTTF((exe_dir / "res/fonts/Noto_Serif_SC/NotoSerifSC-Regular.ttf").c_str(),
                                 computed_cjk_font_size, &config, io.Fonts->GetGlyphRangesChineseFull());

    // Load FontAwesome font for icons.
    io.Fonts->AddFontFromFileTTF((exe_dir / "res/fonts/FontAwesome/otfs/Font Awesome 6 Free-Solid-900.otf").c_str(),
                                 computed_font_size, &config, fontawesome_solid_glyph_ranges);

    io.Fonts->Build();
}