load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "cppvk",
    srcs = ["src/main.cpp"],
    copts = select({
        "@bazel_tools//src/conditions:windows": ["-std:c++17"],
        "//conditions:default": ["-std=c++17"],
    }),
    deps = ["//lib/window"],
)
