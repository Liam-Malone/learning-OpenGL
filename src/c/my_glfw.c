/* Feature checks */
#if (defined(__linux__) || defined(PLATFORM_WEB)) && (_POSIX_C_SOURCE < 199309L)
    #undef _POSIX_C_SOURCE
    #define _POSIX_C_SOURCE 199309L // Required for: CLOCK_MONOTONIC if compiled with c99 without gnu ext.
#endif
#if (defined(__linux__) || defined(PLATFORM_WEB)) && !defined(_GNU_SOURCE)
    #undef _GNU_SOURCE
    #define _GNU_SOURCE // Required for: ppoll if compiled with c99 without gnu ext.
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
    #define _GLFW_WIN32
#endif
#if defined(__linux__)
    #if !defined(_GLFW_WAYLAND) && !defined(_GLFW_X11)
        #error "Cannot disable Wayland and X11 at the same time"
    #endif
#endif
#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__DragonFly__)
    #define _GLFW_X11
#endif
#if defined(__APPLE__)
    #define _GLFW_COCOA
    #define _GLFW_USE_MENUBAR       // To create and populate the menu bar when the first window is created
    #define _GLFW_USE_RETINA        // To have windows use the full resolution of Retina displays
#endif
#if defined(__TINYC__)
    #define _WIN32_WINNT_WINXP      0x0501
#endif

#include "external/glfw/src/init.c"
#include "external/glfw/src/platform.c"
#include "external/glfw/src/context.c"
#include "external/glfw/src/monitor.c"
#include "external/glfw/src/window.c"
#include "external/glfw/src/input.c"
#include "external/glfw/src/vulkan.c"
#include "external/glfw/src/posix_module.c"
#include "external/glfw/src/posix_thread.c"
#include "external/glfw/src/posix_time.c"
#include "external/glfw/src/posix_poll.c"
#include "external/glfw/src/linux_joystick.c"
#include "external/glfw/src/xkb_unicode.c"
#include "external/glfw/src/egl_context.c"
#include "external/glfw/src/osmesa_context.c"

int _glfwConnectNull(int platform_Id, _GLFWplatform* platform) {
    return GLFW_TRUE;
}

/* Linux */
#if defined(__linux__) 
    /* Wayland */
    #if defined(_GLFW_WAYLAND)
        #include "external/glfw/src/wl_init.c"
        #include "external/glfw/src/wl_monitor.c"
        #include "external/glfw/src/wl_window.c"
    #endif
    /* X11 */
    #if defined(_GLFW_X11)
        #include "external/glfw/src/x11_init.c"
        #include "external/glfw/src/x11_monitor.c"
        #include "external/glfw/src/x11_window.c"
        #include "external/glfw/src/glx_context.c"
    #endif
#endif
