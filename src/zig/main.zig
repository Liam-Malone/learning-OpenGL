const std = @import("std");
const builtin = @import("builtin");
const gl = @import("gl");
const glfw = @import("glfw.zig");

const log = std.log;
const gl_log = std.log.scoped(.gl);

pub const exit_key: glfw.Input.Key = switch (builtin.mode) {
    .Debug => .key_q,
    else => .key_null,
};
const Color = struct {
    r: f32,
    g: f32,
    b: f32,
    a: f32,
};

fn logGLFWError(error_code: c_int, description: [*c]const u8) callconv(.C) void {
    std.log.err("{d}: {s}\n", .{ error_code, description });
}
/// Procedure table that will hold loaded OpenGL functions.
var gl_procs: gl.ProcTable = undefined;
const stdout = std.io.getStdOut().writer();
pub fn main() !void {
    const color: Color = .{
        .r = 0.1,
        .g = 0.3,
        .b = 0.3,
        .a = 1.0,
    };

    const res = glfw.init();
    if (res != 1) {
        try stdout.print(" :: Failed to initialize GLFW: {d}\n", .{res});
        std.process.exit(1);
    }
    _ = glfw.setErrorCallback(logGLFWError);
    defer glfw.terminate();
    glfw.windowHint(glfw.GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfw.windowHint(glfw.GLFW_CONTEXT_VERSION_MINOR, 3); //* Setting version to 3.4 fails as 'invalid version' */
    glfw.windowHint(glfw.GLFW_OPENGL_PROFILE, glfw.GLFW_OPENGL_CORE_PROFILE);


    const window: *glfw.Window = glfw.createWindow(800, 600, "LearnOpenGL", null, null) orelse {
        try stdout.print("  :: Failed to initialize GLFW window ::\n", .{});
        std.process.exit(1);
    };
    defer glfw.destroyWindow(window);
    glfw.makeContextCurrent(window);

    // Initialize the OpenGL procedure table.
    if (!gl_procs.init(glfw.getProcAddress)) {
        gl_log.err("failed to load OpenGL functions", .{});
        return error.GLInitFailed;
    }

    // Make the OpenGL procedure table current.
    gl.makeProcTableCurrent(&gl_procs);
    defer gl.makeProcTableCurrent(null);

    gl.Viewport(0, 0, 800, 600);
    _ = glfw.setFramebufferSizeCallback(window, framebuffer_size_callback);

    while (glfw.windowShouldClose(window) == 0) {
        handle_input(window);
        gl.Clear(gl.COLOR_BUFFER_BIT);
        gl.ClearColor(color.r, color.g, color.b, color.a);
        glfw.swapBuffers(window);
        glfw.pollEvents();
    }
}

fn framebuffer_size_callback(window: ?*glfw.Window, width: c_int, height: c_int) callconv(.C) void {
    _ = window;
    gl.Viewport(0, 0, width, height);
}

fn handle_input(window: *glfw.Window) void {
    if (glfw.getKey(window, exit_key) == .press)
        glfw.setWindowShouldClose(window, true);

}
