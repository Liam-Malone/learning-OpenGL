const glfw = @cImport({
    @cDefine("GLFW_INCLUDE_NONE", "1");
    @cInclude("GLFW/glfw3.h");
});

// Re-Export Constants
pub const GLFW_CONTEXT_VERSION_MAJOR = glfw.GLFW_CONTEXT_VERSION_MAJOR;
pub const GLFW_CONTEXT_VERSION_MINOR = glfw.GLFW_CONTEXT_VERSION_MINOR;
pub const GLFW_OPENGL_PROFILE = glfw.GLFW_OPENGL_PROFILE;
pub const GLFW_OPENGL_CORE_PROFILE = glfw.GLFW_OPENGL_CORE_PROFILE;

// Bind Types
pub const Input = struct {
    pub const Key = enum (c_int) {
        hat_centered = 0,
        hat_up = 1,
        hat_right = 2,
        hat_down = 4,
        hat_left = 8,
        hat_right_up = (glfw.GLFW_HAT_RIGHT | glfw.GLFW_HAT_UP),
        hat_right_down = (glfw.GLFW_HAT_RIGHT | glfw.GLFW_HAT_DOWN),
        hat_left_up = (glfw.GLFW_HAT_LEFT  | glfw.GLFW_HAT_UP),
        hat_left_down = (glfw.GLFW_HAT_LEFT  | glfw.GLFW_HAT_DOWN),

        key_unknown = -1,
        key_null = -2,

        //* Printable keys */
        key_space = 32,
        key_apostrophe = 39,
        key_comma = 44,
        key_minus = 45,
        key_period = 46,
        key_slash = 47,
        key_0 = 48,
        key_1 = 49,
        key_2 = 50,
        key_3 = 51,
        key_4 = 52,
        key_5 = 53,
        key_6 = 54,
        key_7 = 55,
        key_8 = 56,
        key_9 = 57,
        key_semicolon = 59,
        key_equal = 61,
        key_a = 65,
        key_b = 66,
        key_c = 67,
        key_d = 68,
        key_e = 69,
        key_f = 70,
        key_g = 71,
        key_h = 72,
        key_i = 73,
        key_j = 74,
        key_k = 75,
        key_l = 76,
        key_m = 77,
        key_n = 78,
        key_o = 79,
        key_p = 80,
        key_q = 81,
        key_r = 82,
        key_s = 83,
        key_t = 84,
        key_u = 85,
        key_v = 86,
        key_w = 87,
        key_x = 88,
        key_y = 89,
        key_z = 90,
        key_left_bracket = 91,
        key_backslash = 92,
        key_right_bracket = 93,
        key_grave_accent = 96,
        key_world_1 = 161,
        key_world_2 = 162,

        // /* Function keys */
        key_escape = 256,
        key_enter = 257,
        key_tab = 258,
        key_backspace = 259,
        key_insert = 260,
        key_delete = 261,
        key_right = 262,
        key_left = 263,
        key_down = 264,
        key_up = 265,
        key_page_up = 266,
        key_page_down = 267,
        key_home = 268,
        key_end = 269,
        key_caps_lock = 280,
        key_scroll_lock = 281,
        key_num_lock = 282,
        key_print_screen = 283,
        key_pause = 284,
        key_f1 = 290,
        key_f2 = 291,
        key_f3 = 292,
        key_f4 = 293,
        key_f5 = 294,
        key_f6 = 295,
        key_f7 = 296,
        key_f8 = 297,
        key_f9 = 298,
        key_f10 = 299,
        key_f11 = 300,
        key_f12 = 301,
        key_f13 = 302,
        key_f14 = 303,
        key_f15 = 304,
        key_f16 = 305,
        key_f17 = 306,
        key_f18 = 307,
        key_f19 = 308,
        key_f20 = 309,
        key_f21 = 310,
        key_f22 = 311,
        key_f23 = 312,
        key_f24 = 313,
        key_f25 = 314,
        key_kp_0 = 320,
        key_kp_1 = 321,
        key_kp_2 = 322,
        key_kp_3 = 323,
        key_kp_4 = 324,
        key_kp_5 = 325,
        key_kp_6 = 326,
        key_kp_7 = 327,
        key_kp_8 = 328,
        key_kp_9 = 329,
        key_kp_decimal = 330,
        key_kp_divide = 331,
        key_kp_multiply = 332,
        key_kp_subtract = 333,
        key_kp_add = 334,
        key_kp_enter = 335,
        key_kp_equal = 336,
        key_left_shift = 340,
        key_left_control = 341,
        key_left_alt = 342,
        key_left_super = 343,
        key_right_shift = 344,
        key_right_control = 345,
        key_right_alt = 346,
        key_right_super = 347,
        key_menu = 348,

        //key_last = glfw.GLFW_KEY_MENU,

    };
    pub const MouseButton = enum (c_int) {
        left = 0,
        right,
        middle,
        mb_4,
        mb_5,
        mb_6,
        mb_7,
        mb_8,
    };
    pub const Action = enum (c_int) {
        release = 0,
        press,
        repeat,
    };
    pub const Modifier = enum (c_int) {
    };
};

// Re-Export Types
pub const Window = glfw.GLFWwindow;

// Bind Functions
pub fn setWindowShouldClose(window: *Window, b: bool) void {
    if (b) {
        glfw.glfwSetWindowShouldClose(window, glfw.GLFW_TRUE);
    } else {
        glfw.glfwSetWindowShouldClose(window, glfw.GLFW_FALSE);
    }

}

pub fn getKey(window: *Window, key: Input.Key) Input.Action {
    return @enumFromInt(glfw.glfwGetKey(window, @intFromEnum(key)));
}
pub fn getMouseButton(window: *Window, button: Input.MouseButton) Input.Action {
    return @enumFromInt(glfw.glfwGetMouseButton(window, @intFromEnum(button)));
}


// Re-Export Functions
pub const windowHint = glfw.glfwWindowHint;
pub const terminate = glfw.glfwTerminate;
pub const init = glfw.glfwInit;
pub const createWindow = glfw.glfwCreateWindow;
pub const setErrorCallback = glfw.glfwSetErrorCallback;
pub const setFramebufferSizeCallback = glfw.glfwSetFramebufferSizeCallback;
pub const destroyWindow = glfw.glfwDestroyWindow;
pub const makeContextCurrent = glfw.glfwMakeContextCurrent;
pub const windowShouldClose = glfw.glfwWindowShouldClose;
pub const swapBuffers = glfw.glfwSwapBuffers;
pub const getProcAddress = glfw.glfwGetProcAddress;
pub const pollEvents = glfw.glfwPollEvents;
