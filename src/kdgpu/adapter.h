#pragma once

#include <kdgpu/adapter_features.h>
#include <kdgpu/adapter_properties.h>
#include <kdgpu/adapter_queue_type.h>
#include <kdgpu/adapter_swapchain_properties.h>
#include <kdgpu/device.h>
#include <kdgpu/handle.h>

#include <kdgpu/kdgpu_export.h>

#include <stdint.h>
#include <span>
#include <string>
#include <vector>

namespace KDGpu {

class GraphicsApi;

struct Adapter_t;
struct Instance_t;
struct Surface_t;

struct AdapterOptions {
    std::vector<std::string> layers;
    std::vector<std::string> extensions;
};

class KDGPU_EXPORT Adapter
{
public:
    ~Adapter();

    Handle<Adapter_t> handle() const noexcept { return m_adapter; }
    bool isValid() const noexcept { return m_adapter.isValid(); }

    operator Handle<Adapter_t>() const noexcept { return m_adapter; }

    std::vector<Extension> extensions() const;
    const AdapterProperties &properties() const noexcept;
    const AdapterFeatures &features() const noexcept;
    std::span<AdapterQueueType> queueTypes() const;

    AdapterSwapchainProperties swapchainProperties(const Handle<Surface_t> &surface) const;
    bool supportsPresentation(const Handle<Surface_t> &surface, uint32_t queueTypeIndex) const noexcept;

    FormatProperties formatProperties(Format format) const;

    Device createDevice(const DeviceOptions &options = DeviceOptions());

private:
    explicit Adapter(GraphicsApi *api, const Handle<Adapter_t> &adapter);

    GraphicsApi *m_api{ nullptr };
    Handle<Adapter_t> m_adapter;

    mutable AdapterProperties m_properties;
    mutable bool m_propertiesQueried{ false };

    mutable AdapterFeatures m_features;
    mutable bool m_featuresQueried{ false };

    mutable std::vector<AdapterQueueType> m_queueTypes;

    friend class Instance;
};

} // namespace KDGpu