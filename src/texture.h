#pragma once

#include <opencv2/core.hpp>
#include <vulkan/vulkan.h>

namespace Engine {

class Texture {
  public:
    ~Texture();

    uint32_t width;
    uint32_t height;

    VkImage image = VK_NULL_HANDLE;
    VkDeviceSize imageSize = 0;

    VkDeviceMemory imageMemory = VK_NULL_HANDLE;
    VkImageView imageView = VK_NULL_HANDLE;
    VkSampler sampler = VK_NULL_HANDLE;
    VkDescriptorSet descriptorSet = VK_NULL_HANDLE;

    VkBuffer stagingBuffer = VK_NULL_HANDLE;
    VkDeviceMemory stagingBufferMemory = VK_NULL_HANDLE;
};

} // namespace Engine