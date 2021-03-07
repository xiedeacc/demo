load("//tools:plugin.bzl", "cc_proto_plugin")

package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "demo",
    srcs = [
        "main.cc",
    ],
    deps = [
        "@protobuf_plugin_demo//src:pb_code_generator_plugin",
        "@com_google_absl//absl/container:inlined_vector",
        "@glog",
    ],
)

