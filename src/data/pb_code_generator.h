#ifndef DEMO_PB_CODE_GENERATOR
#define DEMO_PB_CODE_GENERATOR
#pragma once

#include <set>
#include <string>
#include <vector>

#include "google/protobuf/compiler/code_generator.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/io/printer.h"

namespace demo {
namespace data {

class PBCodeGenerator : public google::protobuf::compiler::CodeGenerator {
 public:
  explicit PBCodeGenerator(const std::string& template_dir_);

 public:
  bool Generate(const google::protobuf::FileDescriptor* file,
                const std::string& parameter,
                google::protobuf::compiler::GeneratorContext* generator_context,
                std::string* error) const;

 private:
  bool GenerateLoaderImpl() const;

 private:
  bool Print(const std::string& file_name, const std::string& content) const;
  std::string GetFullPath(const std::string& file_name) const;

 private:
  const mutable google::protobuf::FileDescriptor* file_;
  mutable google::protobuf::compiler::GeneratorContext* generator_context_;
  std::string template_dir_;
};

}  // namespace data
}  // namespace demo

#endif /* DEMO_PB_CODE_GENERATOR */
