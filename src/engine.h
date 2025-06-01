#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "texture.h"

#include <opencv2/core.hpp>
#include <optional>

namespace Engine {

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() { return graphicsFamily.has_value() && presentFamily.has_value(); }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class Engine {
  public:
    Engine();
    ~Engine();

    void run();

    Texture createTexture(uint32_t width, uint32_t height);
    void updateTexture(Texture &texture, const cv::Mat &frame, VkCommandBuffer commandBuffer = VK_NULL_HANDLE);
    void destroyTexture(Texture &texture);

    std::vector<std::function<void(Engine *)>> onStartHooks;
    std::vector<std::function<void(Engine *)>> onEndHooks;
    std::vector<std::function<void(Engine *, VkCommandBuffer &)>> onFrameHooks;
    std::vector<std::function<void(Engine *, uint32_t width, uint32_t height)>> onWindowResizedHooks;

    void onStart(std::function<void(Engine *)> hook) { onStartHooks.push_back(hook); }
    void onEnd(std::function<void(Engine *)> hook) { onEndHooks.push_back(hook); }
    void onFrame(std::function<void(Engine *, VkCommandBuffer &)> hook) { onFrameHooks.push_back(hook); }
    void onWindowResized(std::function<void(Engine *, uint32_t width, uint32_t height)> hook) {
        onWindowResizedHooks.push_back(hook);
    }

    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);

  private:
    GLFWwindow *pWindow;
    GLFWmonitor *pMonitor;
    const GLFWvidmode *pVidmode;

    VkInstance instance = VK_NULL_HANDLE;
    VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;
    VkSurfaceKHR surface;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;

    VkQueue graphicsQueue;
    VkQueue presentQueue;

    VkSwapchainKHR swapchain;
    std::vector<VkImage> swapchainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapchainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;

    VkRenderPass renderPass;

    VkDescriptorPool descriptorPool;
    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    uint32_t currentFrame = 0;

    bool framebufferResized = false;

    void createWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();

    void cleanupSwapchain();
    void recreateSwapChain();
    void createInstance();

    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);

    void setupDebugMessenger();
    void createSurface();

    void pickPhysicalDevice();

    void createLogicalDevice();

    void createSwapchain();
    void createImageViews();

    void createRenderPass();

    void createFramebuffers();

    void createCommandPool();
    void createCommandBuffers();

    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

    void createSyncObjects();

    void drawFrame();

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

    SwapChainSupportDetails querySwapchainSupport(VkPhysicalDevice device);

    bool isDeviceSuitable(VkPhysicalDevice device);

    bool checkDeviceExtensionSupport(VkPhysicalDevice device);

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    std::vector<const char *> getRequiredExtensions();

    bool checkValidationLayerSupport();

    static std::vector<char> readFile(const std::string &filename);

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                        VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                        const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                                                        void *pUserData);

    void createImGui();

    void createDescriptorPool();

    static void checkVkResult(VkResult err);

    void cleanupImGui();

    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(this->physicalDevice, &memProperties);

        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
            if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                return i;
            }
        }
        throw std::runtime_error("failed to find suitable memory type!");
    };

    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer,
                      VkDeviceMemory &bufferMemory);
};
} // namespace Engine
