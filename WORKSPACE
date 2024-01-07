workspace(name = "demo")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
#load("//bazel:git_configure.bzl", "git_configure")

git_repository(
    name = "bazel_skylib",
    remote = "https://github.com/bazelbuild/bazel-skylib.git",
    tag = "1.3.0",
)

load("@bazel_skylib//lib:versions.bzl", "versions")

versions.check("5.3.0")

git_repository(
    name = "platforms",
    remote = "https://github.com/bazelbuild/platforms.git",
    tag = "0.0.8",
)

git_repository(
    name = "bazel_gazelle",
    remote = "https://github.com/bazelbuild/bazel-gazelle.git",
    tag = "v0.35.0",
)

git_repository(
    name = "rules_cc",
    remote = "https://github.com/bazelbuild/rules_cc.git",
    tag = "0.0.9",
)

git_repository(
    name = "rules_foreign_cc",
    remote = "https://github.com/bazelbuild/rules_foreign_cc.git",
    tag = "0.9.0",
)

git_repository(
    name = "rules_proto",
    remote = "https://github.com/bazelbuild/rules_proto.git",
    tag = "5.3.0-21.7",
)

git_repository(
    name = "rules_perl",
    remote = "https://github.com/bazelbuild/rules_perl.git",
    tag = "0.2.0",
)

git_repository(
    name = "rules_python",
    remote = "https://github.com/bazelbuild/rules_python.git",
    tag = "0.27.1",
)

git_repository(
    name = "rules_java",
    remote = "https://github.com/bazelbuild/rules_java.git",
    tag = "7.3.2",
)

git_repository(
    name = "build_bazel_rules_swift",
    remote = "https://github.com/bazelbuild/rules_swift.git",
    tag = "1.13.0",
)

git_repository(
    name = "build_bazel_rules_apple",
    remote = "https://github.com/bazelbuild/rules_apple.git",
    tag = "3.1.1",
)

git_repository(
    name = "build_bazel_apple_support",
    remote = "https://github.com/bazelbuild/apple_support.git",
    tag = "1.11.1",
)

git_repository(
    name = "io_bazel_rules_docker",
    remote = "https://github.com/bazelbuild/rules_docker.git",
    tag = "v0.25.0",
)

git_repository(
    name = "io_bazel_rules_go",
    remote = "https://github.com/bazelbuild/rules_go.git",
    tag = "v0.35.0",
)

git_repository(
    name = "rules_pkg",
    remote = "https://github.com/bazelbuild/rules_pkg.git",
    tag = "0.9.1",
)

git_repository(
    name = "rules_jvm_external",
    remote = "https://github.com/bazelbuild//rules_jvm_external.git",
    tag = "5.3",
)

new_git_repository(
    name = "zlib",
    build_file = "//bazel:zlib.BUILD",
    remote = "https://github.com/madler/zlib.git",
    tag = "v1.2.13",
)

http_archive(
    name = "org_bzip_bzip2",
    build_file = "//bazel:bzip2.BUILD",
    #remote = "https://gitlab.com/bzip2/bzip2.git",
    sha256 = "329e4eb98f6af8d39da05cb51bccec88ae015eac99a42b1ee04dec0af7f4b957",
    strip_prefix = "bzip2-bzip2-1.0.8",
    urls = ["https://gitlab.com/bzip2/bzip2/-/archive/bzip2-1.0.8/bzip2-bzip2-1.0.8.tar.gz"],
    #commit = "66c46b8c9436613fd81bc5d03f63a61933a4dcc3",
    #tag = "1.0.8",
)

new_git_repository(
    name = "com_github_facebook_zstd",
    build_file = "//bazel:zstd.BUILD",
    remote = "https://github.com/facebook/zstd.git",
    tag = "v1.5.5",
)

new_git_repository(
    name = "org_lzma_lzma",
    build_file = "//bazel:lzma.BUILD",
    remote = "https://github.com/tukaani-project/xz.git",
    tag = "v5.4.5",
)

http_archive(
    name = "openssl",
    build_file = "//bazel:openssl.BUILD",
    repo_mapping = {
        "@com_github_madler_zlib": "@zlib",
    },
    sha256 = "e2f8d84b523eecd06c7be7626830370300fbcc15386bf5142d72758f6963ebc6",
    strip_prefix = "openssl-1.1.1u",
    urls = [
        "https://github.com/openssl/openssl/releases/download/OpenSSL_1_1_1u/openssl-1.1.1u.tar.gz",
    ],
)

git_repository(
    name = "com_github_nelhage_rules_boost",
    commit = "f1065639e6f33741abe2a6a78fa79dd1a07bbf5d",
    remote = "https://github.com/nelhage/rules_boost.git",
    repo_mapping = {
        "@boringssl": "@openssl",
    },
)

git_repository(
    name = "com_google_googletest",
    remote = "https://github.com/google/googletest.git",
    tag = "v1.14.0",
)

git_repository(
    name = "com_google_absl",
    remote = "https://github.com/abseil/abseil-cpp.git",
    tag = "20220623.1",
)

git_repository(
    name = "com_github_glog_glog",
    remote = "https://github.com/google/glog.git",
    tag = "v0.6.0",
)

git_repository(
    name = "com_github_gflags_gflags",
    remote = "https://github.com/gflags/gflags.git",
    tag = "v2.2.2",
)

git_repository(
    name = "com_google_protobuf",
    remote = "https://github.com/protocolbuffers/protobuf.git",
    repo_mapping = {
        "@com_github_google_glog": "@com_github_glog_glog",
        "@com_github_curl_curl": "@curl",
        #"@zlib": "@com_github_madler_zlib",
    },
    tag = "v21.7",
)

git_repository(
    name = "com_grail_bazel_compdb",
    commit = "bc8a4da42f39b13fc298428837bf2a87e5bcd704",
    remote = "https://github.com/grailbio/bazel-compilation-database.git",
)

new_git_repository(
    name = "cpplint",
    build_file = "//bazel:cpplint.BUILD",
    commit = "7b88b68187e3516540fab3caa900988d2179ed24",
    remote = "https://github.com/cpplint/cpplint.git",
)

new_git_repository(
    name = "snappy",
    build_file = "//bazel:snappy.BUILD",
    remote = "https://github.com/google/snappy.git",
    tag = "1.1.10",
)

new_git_repository(
    name = "com_github_google_leveldb",
    build_file = "//bazel:leveldb.BUILD",
    remote = "https://github.com/google/leveldb.git",
    repo_mapping = {
        "@com_github_google_snappy": "@snappy",
    },
    tag = "1.23",
)

new_git_repository(
    name = "com_github_google_crc32c",
    build_file = "//bazel:crc32c.BUILD",
    remote = "https://github.com/google/crc32c.git",
    tag = "1.1.2",
)

git_repository(
    name = "double-conversion",
    remote = "https://github.com/google/double-conversion.git",
    tag = "v3.3.0",
)

new_git_repository(
    name = "com_github_fmtlib_fmt",
    build_file = "//bazel:fmt.BUILD",
    remote = "https://github.com/fmtlib/fmt.git",
    tag = "9.1.0",
)

load("@io_bazel_rules_go//go:deps.bzl", "go_register_toolchains", "go_rules_dependencies")
load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")
load("@com_grail_bazel_compdb//:deps.bzl", "bazel_compdb_deps")
load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")
load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
load("@rules_pkg//:deps.bzl", "rules_pkg_dependencies")
load("@rules_perl//perl:deps.bzl", "perl_register_toolchains")
load("@rules_python//python:repositories.bzl", "py_repositories")

py_repositories()

perl_register_toolchains()

rules_foreign_cc_dependencies()

rules_proto_dependencies()

rules_proto_toolchains()

rules_pkg_dependencies()

boost_deps()

bazel_compdb_deps()
