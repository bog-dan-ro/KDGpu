#pragma once

#include <toy_renderer/handle.h>
#include <toy_renderer/toy_renderer_export.h>

namespace ToyRenderer {

class GraphicsApi;
struct Device_t;
struct Sampler_t;
struct SamplerOptions;

class TOY_RENDERER_EXPORT Sampler
{
public:
    Sampler();
    ~Sampler();

    Sampler(Sampler &&);
    Sampler &operator=(Sampler &&);

    Sampler(const Sampler &) = delete;
    Sampler &operator=(const Sampler &) = delete;

    Handle<Sampler_t> handle() const noexcept { return m_sampler; }
    bool isValid() const noexcept { return m_sampler.isValid(); }

    operator Handle<Sampler_t>() const noexcept { return m_sampler; }

private:
    Sampler(GraphicsApi *api, const Handle<Device_t> &device, const SamplerOptions &options);

    GraphicsApi *m_api{ nullptr };
    Handle<Device_t> m_device;
    Handle<Sampler_t> m_sampler;

    friend class Device;
    friend TOY_RENDERER_EXPORT bool operator==(const Sampler &, const Sampler &);
};

TOY_RENDERER_EXPORT bool operator==(const Sampler &a, const Sampler &b);
TOY_RENDERER_EXPORT bool operator!=(const Sampler &a, const Sampler &b);

} // namespace ToyRenderer
