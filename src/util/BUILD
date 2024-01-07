load("//tools:cpplint.bzl", "cpplint")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "util",
    srcs = ["util.cc"],
    hdrs = [
        "util.h",
    ],
    deps = [
        "@boost//:algorithm",
        "@boost//:beast",
        "@boost//:filesystem",
        "@boost//:iostreams",
        "@com_github_fmtlib_fmt//:fmt",
        "@com_github_glog_glog//:glog",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/time",
        "@com_google_protobuf//:protobuf",
    ],
)

cpplint()
