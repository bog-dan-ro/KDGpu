#pragma once

#include <kdgpu/gpu_core.h>
#include <kdgpu/bind_group_description.h>

namespace KDGpu {

struct ResourceBindingLayout {
    uint32_t binding;
    uint32_t count{ 1 };
    ResourceBindingType resourceType;
    ShaderStageFlags shaderStages;

    bool isCompatible(const ResourceBindingLayout &other) const noexcept
    {
        return binding == other.binding &&
                count == other.count &&
                resourceType == other.resourceType;
    }
};

// The following struct describes a bind group (descriptor set) layout and from this we
// will be able to subsequently allocate the actual bind group (descriptor set). Before
// the bind group can be used we will need to populate it with the specified bindings.
struct BindGroupLayoutOptions {
    std::vector<ResourceBindingLayout> bindings;
};

} // namespace KDGpu