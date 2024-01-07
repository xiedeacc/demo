load("//tools:cpplint.bzl", "cpplint")
load("//bazel:pb_code_gen_plugin.bzl", "cc_proto_plugin")

package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "pb_code_generator",
    srcs = [
        "pb_code_generator.cc",
        "pb_code_generator.h",
    ],
    data = [
        "//src/data/template:loader_impl.h",
    ],
    linkstatic = True,
    deps = [
        "//src/util",
        "@com_google_absl//absl/strings",
        "@com_google_protobuf//:protoc_lib",
    ],
)

cc_proto_plugin(
    name = "pb_code_generator_plugin",
    src = "//src/proto:config.proto",
    outs = [
        "loader_impl.h",
    ],
    data = [
        "//src/data/template:loader_impl.h",
    ],
    linkstatic = True,
    plugin = ":pb_code_generator",
    proto_deps = ["//src/proto:config.proto"],
    proto_path = "src/proto",
    protoc = "@com_google_protobuf//:protoc",
    deps = [
        "//src/util",
    ],
)

cc_test(
    name = "loader_impl_test",
    srcs = ["loader_impl_test.cc"],
    deps = [
        ":pb_code_generator_plugin",
        "//src/test_util:test_main",
        "@com_github_glog_glog//:glog",
    ],
)

cpplint()
