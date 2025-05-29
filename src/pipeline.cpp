#include "vk_boost/pipeline.hpp"

[[nodiscard]]
VkPipelineRasterizationStateCreateInfo vk_boost::pipeline::defaultRasterizerStateInfo()
{
    return VkPipelineRasterizationStateCreateInfo{.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
                                                  .pNext = nullptr,
                                                  .flags = 0,
                                                  .depthClampEnable = VK_FALSE,
                                                  .rasterizerDiscardEnable = VK_FALSE,
                                                  .polygonMode = VK_POLYGON_MODE_FILL,
                                                  .cullMode = VK_CULL_MODE_FRONT_BIT,
                                                  .frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE,
                                                  .depthBiasEnable = VK_FALSE,
                                                  .lineWidth = 1.0f};
}

[[nodiscard]]
VkPipelineColorBlendStateCreateInfo vk_boost::pipeline::defaultColorBlendStateInfo()
{
    VkPipelineColorBlendAttachmentState blend_attachment_state{};
    blend_attachment_state.colorWriteMask = 0xf;
    blend_attachment_state.blendEnable = VK_FALSE;

    return VkPipelineColorBlendStateCreateInfo{.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
                                               .pNext = nullptr,
                                               .flags = 0,
                                               .attachmentCount = 1,
                                               .pAttachments = &blend_attachment_state};
}

[[nodiscard]]
VkPipelineMultisampleStateCreateInfo vk_boost::pipeline::defaultMultisampleStateInfo()
{
    return VkPipelineMultisampleStateCreateInfo{.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
                                                .pNext = nullptr,
                                                .flags = 0,
                                                .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
                                                .sampleShadingEnable = VK_FALSE,
                                                .minSampleShading = 0.0f,
                                                .pSampleMask = nullptr,
                                                .alphaToCoverageEnable = VK_FALSE,
                                                .alphaToOneEnable = VK_FALSE};
}

[[nodiscard]]
VkPipelineInputAssemblyStateCreateInfo vk_boost::pipeline::defaultInputAssemblyStateInfo()
{
    return VkPipelineInputAssemblyStateCreateInfo{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        .primitiveRestartEnable = VK_FALSE,
    };
}

[[nodiscard]]
VkPipelineDepthStencilStateCreateInfo vk_boost::pipeline::defaultDepthStencilStateInfo()
{
    return VkPipelineDepthStencilStateCreateInfo{.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
                                                 .pNext = nullptr,
                                                 .flags = 0,
                                                 .depthTestEnable = VK_TRUE,
                                                 .depthWriteEnable = VK_TRUE,
                                                 .depthCompareOp = VK_COMPARE_OP_LESS,
                                                 .depthBoundsTestEnable = VK_FALSE,
                                                 .stencilTestEnable = VK_TRUE};
}
