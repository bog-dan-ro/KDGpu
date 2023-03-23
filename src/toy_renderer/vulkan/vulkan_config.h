#pragma once

#include <vulkan/vulkan.h>

#include <array>

namespace ToyRenderer {

//
// Instance Config
//

#if defined(NDEBUG) || defined(__arm__)
constexpr bool enableValidationLayers = false;
const std::vector<const char *> requestedInstanceLayers = {};
#else
constexpr bool enableValidationLayers = true;
const std::vector<const char *> requestedInstanceLayers = {
    "VK_LAYER_KHRONOS_validation",
};
#endif

constexpr std::array<const char *, 1> requestedInstanceExtensions = {
    VK_EXT_DEBUG_UTILS_EXTENSION_NAME
};

std::vector<const char *> getDefaultRequestedInstanceExtensions()
{
    std::vector<const char *> extensions;
    extensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
#if defined(PLATFORM_LINUX)
    extensions.push_back("VK_KHR_xcb_surface");
#if defined(PLATFORM_WAYLAND)
    extensions.push_back("VK_KHR_wayland_surface");
#endif
#elif defined(PLATFORM_WIN32)
    extensions.push_back("VK_KHR_win32_surface");
#elif defined(PLATFORM_MACOS)
    extensions.push_back("VK_EXT_metal_surface");
#endif
    if (enableValidationLayers)
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    return extensions;
}

//
// Device Config
//
std::vector<const char *> getDefaultRequestedDeviceExtensions()
{
    std::vector<const char *> extensions;
    extensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
#if defined(PLATFORM_MACOS)
    extensions.push_back("VK_KHR_portability_subset");
#else
    extensions.push_back(VK_KHR_SYNCHRONIZATION_2_EXTENSION_NAME);
#endif
    return extensions;
}

} // namespace ToyRenderer
