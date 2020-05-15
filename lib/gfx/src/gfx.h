#pragma once
#include "lib/util/src/num.h"

#define NG_MAKE_VERSION(major, minor, patch) \
    (((major) << 22) | ((minor) << 12) | (patch))

struct Gfx;

Gfx* ngCreateGfx(const char* appName, u32 appVersion);
void ngDestroyGfx(Gfx* gfx);
