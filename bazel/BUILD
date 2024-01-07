package(default_visibility = ["//visibility:public"])

load("@bazel_skylib//lib:selects.bzl", "selects")

exports_files([
    "config.lzma-linux.h",
])

filegroup(
    name = "exported_testdata",
    srcs = glob(["**"]),
)

exports_files(glob(["**"]))
