#include "swapchain.h"

#include <kdgpu/graphics_api.h>
#include <kdgpu/resource_manager.h>
#include <kdgpu/api/api_swapchain.h>
#include <kdgpu/swapchain_options.h>

namespace KDGpu {

Swapchain::Swapchain()
{
}

Swapchain::Swapchain(GraphicsApi *api, const Handle<Device_t> &device, const SwapchainOptions &options)
    : m_api(api)
    , m_device(device)
    , m_swapchain(m_api->resourceManager()->createSwapchain(m_device, options))
{
    // Fetch the textures owned by the swapchain
    auto apiSwapchain = m_api->resourceManager()->getSwapchain(m_swapchain);
    const auto textureHandles = apiSwapchain->getTextures();
    const uint32_t textureCount = textureHandles.size();
    m_textures.reserve(textureCount);
    for (uint32_t i = 0; i < textureCount; ++i)
        m_textures.emplace_back(Texture(m_api, m_device, textureHandles[i]));
}

Swapchain::Swapchain(Swapchain &&other)
{
    m_api = other.m_api;
    m_device = other.m_device;
    m_swapchain = other.m_swapchain;
    m_textures = std::move(other.m_textures);

    other.m_api = nullptr;
    other.m_device = {};
    other.m_swapchain = {};
}

Swapchain &Swapchain::operator=(Swapchain &&other)
{
    if (this != &other) {
        if (isValid())
            m_api->resourceManager()->deleteSwapchain(handle());

        m_api = other.m_api;
        m_device = other.m_device;
        m_swapchain = other.m_swapchain;
        m_textures = std::move(other.m_textures);

        other.m_api = nullptr;
        other.m_device = {};
        other.m_swapchain = {};
    }
    return *this;
}

Swapchain::~Swapchain()
{
    if (isValid())
        m_api->resourceManager()->deleteSwapchain(handle());
}

AcquireImageResult Swapchain::getNextImageIndex(uint32_t &imageIndex, const Handle<GpuSemaphore_t> &semaphore)
{
    auto apiSwapchain = m_api->resourceManager()->getSwapchain(m_swapchain);
    return apiSwapchain->getNextImageIndex(imageIndex, semaphore);
}

} // namespace KDGpu