# Description
#    lzma is a general purpose data compression library https://tukaani.org/xz/
#    Public Domain

load("@bazel_skylib//rules:copy_file.bzl", "copy_file")
load("@bazel_skylib//lib:selects.bzl", "selects")

# Hopefully, the need for these OSxCPU config_setting()s will be obviated by a fix to https://github.com/bazelbuild/platforms/issues/36

config_setting(
    name = "osx_arm64",
    constraint_values = [
        "@platforms//os:osx",
        "@platforms//cpu:aarch64",
    ],
)

config_setting(
    name = "osx_x86_64",
    constraint_values = [
        "@platforms//os:osx",
        "@platforms//cpu:x86_64",
    ],
)

copy_file(
    name = "copy_config",
    src = selects.with_or({
        "@platforms//os:android": "@demo//bazel:config.lzma-android.h",
        "@platforms//os:linux": "@demo//bazel:config.lzma-linux.h",
        ":osx_arm64": "//bazel:config.lzma-osx-arm64.h",
        ":osx_x86_64": "//bazel:config.lzma-osx-x86_64.h",
        ("@platforms//os:ios", "@platforms//os:watchos", "@platforms//os:tvos"): "apple_config",
        "@platforms//os:windows": "//bazel:config.lzma-windows.h",
    }),
    out = "src/liblzma/api/config.h",  # minimize the number of exported include paths
)

# Configuration is the same across iOS, watchOS, and tvOS
alias(
    name = "apple_config",
    actual = select({
        "@platforms//cpu:arm64": "//:config.lzma-ios-arm64.h",
        "@platforms//cpu:armv7": "//:config.lzma-ios-armv7.h",
        "@platforms//cpu:x86_64": "//:config.lzma-osx-x86_64.h",  # Configuration same as macOS
        "@platforms//cpu:x86_32": "//:config.lzma-ios-i386.h",
    }),
)

# Note: lzma is bundled with Apple platforms, but sadly, not considered public API because its header is not exposed. lzma is not bundled on Android.

cc_library(
    name = "lzma",
    srcs = [
        "src/common/tuklib_cpucores.c",
        "src/common/tuklib_physmem.c",
        "src/liblzma/api/config.h",  # Generated, so missed by glob.
    ] + glob(
        [
            "src/**/*.h",
            "src/liblzma/**/*.c",
        ],
        exclude = [
            "src/liblzma/check/*_small.c",
            "src/liblzma/**/*_tablegen.c",
        ],
    ),
    hdrs = glob(["src/liblzma/api/**/*.h"]),
    copts = select({
        "@platforms//os:windows": [],
        "//conditions:default": [
            "-std=c99",
            "-O3",
            "-g",
            "-fPIC",
            "-march=native",
            "-fvisibility=hidden",
            "-Wall",
            "-Wextra",
            "-Wvla",
            "-Wc99-c11-compat",
            "-Wformat=2",
            "-Winit-self",
            "-Wshift-overflow=2",
            "-Wstrict-overflow=3",
            "-Walloc-zero",
            "-Wduplicated-cond",
            "-Wfloat-equal",
            "-Wundef",
            "-Wshadow",
            "-Wpointer-arith",
            "-Wbad-function-cast",
            "-Wwrite-strings",
            "-Wdate-time",
            "-Wsign-conversion",
            "-Wfloat-conversion",
            "-Wlogical-op",
            "-Waggregate-return",
            "-Wstrict-prototypes",
            "-Wold-style-definition",
            "-Wmissing-prototypes",
            "-Wmissing-declarations",
            "-Wredundant-decls",
        ],
    }),
    defines = select({
        "@platforms//os:windows": ["LZMA_API_STATIC"],
        "//conditions:default": [],
    }),
    includes = [
        "src/common",
        "src/liblzma/api",
        "src/liblzma/check",
        "src/liblzma/common",
        "src/liblzma/delta",
        "src/liblzma/lz",
        "src/liblzma/lzma",
        "src/liblzma/rangecoder",
        "src/liblzma/simple",
    ],
    linkopts = select({
        "@platforms//os:android": [],
        "//conditions:default": ["-pthread"],
    }),
    linkstatic = select({
        "@platforms//os:windows": True,
        "//conditions:default": False,
    }),
    local_defines = [
        "HAVE_CONFIG_H",
        "TUKLIB_SYMBOL_PREFIX=lzma_",
    ],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "xzdec",
    srcs = [
        "src/common/sysdefs.h",
        "src/common/tuklib_common.h",
        "src/common/tuklib_config.h",
        "src/common/tuklib_exit.c",
        "src/common/tuklib_exit.h",
        "src/common/tuklib_gettext.h",
        "src/common/tuklib_progname.c",
        "src/common/tuklib_progname.h",
        "src/xzdec/xzdec.c",
    ],
    copts = [
        "-std=c99",
        "-march=native",
        "-O3",
    ],
    local_defines = [
        "HAVE_CONFIG_H",
    ],
    deps = [
        ":lzma",
    ],
)

cc_binary(
    name = "xz",
    srcs = [
        "src/common/mythread.h",
        "src/common/sysdefs.h",
        "src/common/tuklib_common.h",
        "src/common/tuklib_config.h",
        "src/common/tuklib_exit.c",
        "src/common/tuklib_exit.h",
        "src/common/tuklib_gettext.h",
        "src/common/tuklib_integer.h",
        "src/common/tuklib_mbstr.h",
        "src/common/tuklib_mbstr_fw.c",
        "src/common/tuklib_mbstr_width.c",
        "src/common/tuklib_open_stdxxx.c",
        "src/common/tuklib_open_stdxxx.h",
        "src/common/tuklib_progname.c",
        "src/common/tuklib_progname.h",
        "src/liblzma/api/config.h",
        "src/xz/args.c",
        "src/xz/args.h",
        "src/xz/coder.c",
        "src/xz/coder.h",
        "src/xz/file_io.c",
        "src/xz/file_io.h",
        "src/xz/hardware.c",
        "src/xz/hardware.h",
        "src/xz/list.c",
        "src/xz/list.h",
        "src/xz/main.c",
        "src/xz/main.h",
        "src/xz/message.c",
        "src/xz/message.h",
        "src/xz/mytime.c",
        "src/xz/mytime.h",
        "src/xz/options.c",
        "src/xz/options.h",
        "src/xz/private.h",
        "src/xz/signals.c",
        "src/xz/signals.h",
        "src/xz/suffix.c",
        "src/xz/suffix.h",
        "src/xz/util.c",
        "src/xz/util.h",
    ],
    copts = [
        "-std=c99",
        "-O3",
        "-march=native",
    ],
    includes = [
        "src/common",
        "src/liblzma/api",
        "src/liblzma/check",
        "src/liblzma/common",
        "src/liblzma/delta",
        "src/liblzma/lz",
        "src/liblzma/lzma",
        "src/liblzma/rangecoder",
        "src/liblzma/simple",
    ],
    local_defines = [
        "LOCALEDIR=\"/usr/local/share/locale\"",
        "HAVE_CONFIG_H",
    ],
    deps = [
        ":lzma",
    ],
)
