#pragma once

#include <kdgpu/api/api_instance.h>

#include <vulkan/vulkan.h>

namespace KDGpu {

class VulkanResourceManager;

struct VulkanInstance : public ApiInstance {
    explicit VulkanInstance(VulkanResourceManager *_vulkanResourceManager, VkInstance _instance);

    std::vector<Extension> extensions() const final;
    std::vector<Handle<Adapter_t>> queryAdapters(const Handle<Instance_t> &instanceHandle) final;
    Handle<Surface_t> createSurface(const SurfaceOptions &options) final;

    VulkanResourceManager *vulkanResourceManager{ nullptr };
    VkInstance instance{ VK_NULL_HANDLE };
};

} // namespace KDGpu