load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "util",
    srcs = ["src/log.cpp"],
    hdrs = [
        "src/log.h",
        "src/num.h",
        "src/os.h",
    ],
    visibility = [
        "//lib/gfx:__pkg__",
        "//lib/window:__pkg__",
    ],
)
