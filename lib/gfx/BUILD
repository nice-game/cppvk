load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "gfx",
    srcs = ["src/gfx.cpp"],
    hdrs = [
        "src/gfx.h",
        "src/vulkan/vk_platform.h",
        "src/vulkan/vulkan.h",
        "src/vulkan/vulkan_core.h",
    ],
    visibility = ["//:__pkg__"],
    deps = ["//lib/util"],
)
