#pragma once

#include "camera_util.h"
#include "engine.h"

#include <metavision/sdk/stream/camera.h>

namespace App {

class App {
  public:
    App(const int argc, char *const *argv);
    ~App();

    Engine::Engine engine_;

    // Application parameters (command line arguments)
    std::vector<std::string> eventFiles;

    // Metavision Camera objects
    std::vector<std::unique_ptr<CameraUtil>> cameras_;

    void run();
    void render(VkCommandBuffer commandBuffer);

  private:
    void parseArgs(const int argc, char *const *argv);
};

} // namespace App