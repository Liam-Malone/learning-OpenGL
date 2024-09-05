const std = @import("std");

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});
    const exe = b.addExecutable(.{
        .name = "C-3d",
        .target = target,
        .optimize = optimize,
    });

    const build_flags = [_][]const u8{
        "-std=c99",
        "-Wall",
        "-Wextra",
    };

    exe.defineCMacro("ZIG_CC", "1"); // Ensure that program knows it's compiled with `zig cc`
    exe.root_module.addCSourceFile(.{
        .file = b.path("src/main.c"),
        .flags = &build_flags,
    });

    const stdout = std.io.getStdOut().writer();
    switch(target.result.os.tag) {
        .linux => {
            try stdout.print("  :: Building for linux target ::\n", .{});
            exe.linkSystemLibrary("GL");
            exe.linkSystemLibrary("X11");
            exe.linkSystemLibrary("Xi");
            exe.linkSystemLibrary("pthread");
            exe.linkSystemLibrary("m");
            exe.linkSystemLibrary("dl");
            exe.linkSystemLibrary("Xrandr");
        },
        .windows => {
            exe.linkSystemLibrary("static");
            exe.linkSystemLibrary("lgdi32");
            exe.linkSystemLibrary("lm");
            exe.linkSystemLibrary("lopengl32");
            exe.linkSystemLibrary("lwinmm");
            exe.linkSystemLibrary("ggdb");
        },
        .macos => {
            exe.linkFramework("Foundation");
            exe.linkFramework("CoreGraphics");
            exe.linkFramework("AppKit");
            exe.linkFramework("IOKit");
            exe.linkSystemLibrary("lm");
        },
        else => {
            try stdout.print("target is:: {any}\n", .{target.result.os.tag});
            try stdout.print("target is:: {any}\n", .{target.result.os.tag});
        },
    }
    exe.linkLibC();
    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);

    run_cmd.step.dependOn(b.getInstallStep());

    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);

}
