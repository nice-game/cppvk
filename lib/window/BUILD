load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "window",
    srcs = ["src/window.cpp"],
    hdrs = [
        "src/os.h",
        "src/window.h",
    ],
    copts = select({
        "@bazel_tools//src/conditions:windows": ["-std:c++17"],
        "//conditions:default": ["-std=c++17"],
    }),
    linkopts = select({
        "@bazel_tools//src/conditions:windows": ["-DEFAULTLIB:user32.lib"],
        "//conditions:default": [],
    }),
    visibility = ["//:__pkg__"],
    deps = ["//lib/util"],
)
