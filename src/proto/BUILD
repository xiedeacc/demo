load("@rules_proto//proto:defs.bzl", "proto_library")

package(default_visibility = ["//visibility:public"])

cc_proto_library(
    name = "cc_config",
    deps = [
        ":config_proto",
    ],
)

proto_library(
    name = "config_proto",
    srcs = ["config.proto"],
    deps = [],
)

filegroup(
    name = "proto_files",
    srcs = glob(["*.proto"]),
)
