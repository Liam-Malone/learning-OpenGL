const std = @import("std");
const glfw = @import("glfw");

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "learnGL-zig",
        .root_source_file = b.path("src/zig/main.zig"),
        .target = target,
        .optimize = optimize,
    });

    if (b.lazyDependency("glfw", .{
        .target = target,
        .optimize = optimize,
        .x11 = true,
        .wayland = true,
        .metal = false,
        .opengl = true,
    })) |dep| {
        exe.linkLibrary(dep.artifact("glfw"));
    }

    const gl_bindings = @import("zigglgen").generateBindingsModule(b, .{
        .api = .gl,
        .version = .@"4.1",
        .profile = .core,
    });
    exe.root_module.addImport("gl", gl_bindings);

    // exe.linkSystemLibrary("GL");
    exe.linkSystemLibrary("X11");
    exe.linkSystemLibrary("Xi");
    exe.linkSystemLibrary("dl");
    exe.linkSystemLibrary("m");
    exe.linkSystemLibrary("Xrandr");
    exe.linkSystemLibrary("rt");

    b.installArtifact(exe);
    const run_cmd = b.addRunArtifact(exe);

    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run the program");
    run_step.dependOn(&run_cmd.step);
}
