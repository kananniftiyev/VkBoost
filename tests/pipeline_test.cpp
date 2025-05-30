#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "vk_deck/pipeline.hpp"

TEST_CASE("Default Rasterization Info", "[Pipeline]")
{
  auto info = vk_deck::pipeline::defaultRasterizerStateInfo();

  REQUIRE(info.sType == VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO);
  REQUIRE(info.pNext == nullptr);
  REQUIRE(info.flags == 0);
  REQUIRE(info.depthClampEnable == VK_FALSE);
  REQUIRE(info.rasterizerDiscardEnable == VK_FALSE);
  REQUIRE(info.polygonMode == VK_POLYGON_MODE_FILL);
  REQUIRE(info.cullMode == VK_CULL_MODE_FRONT_BIT);
  REQUIRE(info.frontFace == VK_FRONT_FACE_COUNTER_CLOCKWISE);
  REQUIRE(info.depthBiasEnable == VK_FALSE);
  REQUIRE(info.depthBiasClamp == Catch::Approx(0.0f));
  REQUIRE(info.depthBiasSlopeFactor == Catch::Approx(0.0f));
  REQUIRE(info.lineWidth == Catch::Approx(1.0f));
}

TEST_CASE("Default Color Blender Info", "[Pipeline]")
{
  auto info = vk_deck::pipeline::defaultColorBlendStateInfo();

  REQUIRE(info.sType == VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO);
  REQUIRE(info.pNext == nullptr);
  REQUIRE(info.flags == 0);
  REQUIRE(info.attachmentCount == 1);
  REQUIRE(info.pAttachments != nullptr);

  const VkPipelineColorBlendAttachmentState &attachment = info.pAttachments[0];
  REQUIRE(attachment.colorWriteMask == 0xf);
  REQUIRE(attachment.blendEnable == VK_FALSE);
}

TEST_CASE("Default Multisample State Info", "[Pipeline]")
{
  auto info = vk_deck::pipeline::defaultMultisampleStateInfo();

  REQUIRE(info.sType == VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO);
  REQUIRE(info.pNext == nullptr);
  REQUIRE(info.flags == 0);
  REQUIRE(info.rasterizationSamples == VK_SAMPLE_COUNT_1_BIT);
  REQUIRE(info.sampleShadingEnable == VK_FALSE);
  REQUIRE(info.minSampleShading == Catch::Approx(0.0f));
  REQUIRE(info.pSampleMask == nullptr);
  REQUIRE(info.alphaToCoverageEnable == VK_FALSE);
  REQUIRE(info.alphaToOneEnable == VK_FALSE);
}

TEST_CASE("Default Input Assembly State Info", "[Pipeline]")
{
  auto info = vk_deck::pipeline::defaultInputAssemblyStateInfo();

  REQUIRE(info.sType == VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO);
  REQUIRE(info.pNext == nullptr);
  REQUIRE(info.flags == 0);
  REQUIRE(info.topology == VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);
  REQUIRE(info.primitiveRestartEnable == VK_FALSE);
}

TEST_CASE("Default Depth Stencil State Info", "[Pipeline]")
{
  auto info = vk_deck::pipeline::defaultDepthStencilStateInfo();

  REQUIRE(info.sType == VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO);
  REQUIRE(info.pNext == nullptr);
  REQUIRE(info.flags == 0);
  REQUIRE(info.depthTestEnable == VK_TRUE);
  REQUIRE(info.depthWriteEnable == VK_TRUE);
  REQUIRE(info.depthCompareOp == VK_COMPARE_OP_LESS);
  REQUIRE(info.depthBoundsTestEnable == VK_FALSE);
  REQUIRE(info.stencilTestEnable == VK_TRUE);
}