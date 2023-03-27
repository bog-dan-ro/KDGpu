#pragma once

#include <kdgpu_kdgui/engine_layer.h>
#include <kdgpu_kdgui/view.h>

#include <kdgpu/device.h>
#include <kdgpu/gpu_semaphore.h>
#include <kdgpu/instance.h>
#include <kdgpu/queue.h>
#include <kdgpu/surface.h>
#include <kdgpu/swapchain.h>
#include <kdgpu/texture.h>
#include <kdgpu/texture_view.h>
#include <kdgpu/vulkan/vulkan_graphics_api.h>

#include <kdgpu_kdgui/kdgpu_kdgui_export.h>

#include <array>
#include <memory>
#include <vector>

using namespace KDGpu;

namespace KDGpuKDGui {

// This determines the maximum number of frames that can be in-flight at any one time.
// With the default setting of 2, we can be recording the commands for frame N+1 whilst
// the GPU is executing those for frame N. We cannot then record commands for frame N+2
// until the GPU signals it is done with frame N.
constexpr uint32_t MAX_FRAMES_IN_FLIGHT = 2;

class KDGPU_KDGUI_EXPORT ExampleEngineLayer : public EngineLayer
{
public:
    ExampleEngineLayer();
    explicit ExampleEngineLayer(const SampleCountFlagBits samples);
    ~ExampleEngineLayer() override;

    View *window() { return m_window.get(); }

protected:
    virtual void initializeScene() = 0;
    virtual void cleanupScene() = 0;
    virtual void updateScene() = 0;
    virtual void render() = 0;
    virtual void resize() = 0;

    void onAttached() override;
    void onDetached() override;

    void recreateSwapChain();
    void waitForUploadBufferData(const Handle<Buffer_t> &destinationBuffer,
                                 const void *data,
                                 DeviceSize byteSize,
                                 DeviceSize dstOffset = 0);
    void uploadBufferData(const Handle<Buffer_t> &destinationBuffer,
                          PipelineStageFlags dstStages,
                          AccessFlags dstMask,
                          const void *data,
                          DeviceSize byteSize,
                          DeviceSize dstOffset = 0);

    void waitForUploadTextureData(const Handle<Texture_t> &destinationTexture,
                                  const void *data,
                                  DeviceSize byteSize,
                                  Extent3D textureExtent,
                                  Offset3D textureOffset,
                                  TextureLayout oldLayout,
                                  TextureLayout newLayout);
    void uploadTextureData(const Handle<Texture_t> &destinationTexture,
                           PipelineStageFlags dstStages,
                           AccessFlags dstMask,
                           const void *data,
                           DeviceSize byteSize,
                           Extent3D textureExtent,
                           Offset3D textureOffset,
                           TextureLayout oldLayout,
                           TextureLayout newLayout);

    void releaseStagingBuffers();

    std::unique_ptr<GraphicsApi> m_api;
    std::unique_ptr<View> m_window;

    const SampleCountFlagBits m_samples{ SampleCountFlagBits::Samples1Bit };
    Instance m_instance;
    Surface m_surface;
    Device m_device;
    Queue m_queue;
    PresentMode m_presentMode;
    Swapchain m_swapchain;
    std::vector<TextureView> m_swapchainViews;
    Texture m_depthTexture;
    TextureView m_depthTextureView;

    uint32_t m_currentSwapchainImageIndex{ 0 };
    uint32_t m_inFlightIndex{ 0 };
    std::array<GpuSemaphore, MAX_FRAMES_IN_FLIGHT> m_presentCompleteSemaphores;
    std::array<GpuSemaphore, MAX_FRAMES_IN_FLIGHT> m_renderCompleteSemaphores;

    struct StagingBuffer {
        Fence fence;
        Buffer buffer;
        CommandBuffer commandBuffer;
    };
    std::vector<StagingBuffer> m_stagingBuffers;

    const Format m_swapchainFormat{ Format::B8G8R8A8_UNORM };
    const Format m_depthFormat{ Format::D24_UNORM_S8_UINT };
};

} // namespace KDGpuKDGui