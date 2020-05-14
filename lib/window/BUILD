load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "window",
    srcs = ["src/window.cpp"],
    hdrs = ["src/window.h"],
    linkopts = select({
        "@bazel_tools//src/conditions:windows": ["-DEFAULTLIB:user32.lib"],
        "//conditions:default": [],
    }),
    visibility = ["//:__pkg__"],
    deps = ["//lib/util"],
)
