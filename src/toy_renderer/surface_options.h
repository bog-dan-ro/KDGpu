#pragma once

#if defined(TOY_RENDERER_PLATFORM_WIN32)
#define NOMINMAX
#include <windows.h>
#endif

#if defined(TOY_RENDERER_PLATFORM_LINUX)
#include <xcb/xproto.h>
#endif

#if defined(TOY_RENDERER_PLATFORM_MACOS)
#ifdef __OBJC__
@class CAMetalLayer;
#else
typedef void CAMetalLayer;
#endif
#endif

namespace ToyRenderer {

struct SurfaceOptions {
#if defined(TOY_RENDERER_PLATFORM_WIN32)
    HWND hWnd;
#endif
#if defined(TOY_RENDERER_PLATFORM_LINUX)
    // TODO: Add Wayland support
    xcb_connection_t *connection;
    xcb_window_t window;
#endif
#if defined(TOY_RENDERER_PLATFORM_MACOS)
    CAMetalLayer *layer;
#endif
};

} // namespace ToyRenderer
