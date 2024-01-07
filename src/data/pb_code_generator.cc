#include "src/data/pb_code_generator.h"

#include <algorithm>
#include <map>
#include <memory>
#include <utility>

#include "glog/logging.h"
#include "google/protobuf/compiler/plugin.h"
#include "google/protobuf/io/zero_copy_stream.h"
#include "src/util/util.h"

using demo::util::Util;
using google::protobuf::Descriptor;
using google::protobuf::FieldDescriptor;
using google::protobuf::FileDescriptor;
using google::protobuf::compiler::GeneratorContext;
using google::protobuf::io::Printer;
using google::protobuf::io::ZeroCopyOutputStream;
using std::map;
using std::set;
using std::string;
using std::vector;

namespace demo {
namespace data {

PBCodeGenerator::PBCodeGenerator(const string& template_dir) {
  this->file_ = nullptr;
  this->template_dir_ = template_dir;
  this->generator_context_ = nullptr;
}

bool PBCodeGenerator::Generate(const FileDescriptor* file,
                               const string& parameter,
                               GeneratorContext* generator_context,
                               string* error) const {
  generator_context_ = generator_context;
  file_ = file;
  return GenerateLoaderImpl();
}

bool PBCodeGenerator::GenerateLoaderImpl() const {
  string loader_impl_content;
  for (int idx = 0; idx < file_->message_type_count(); ++idx) {
    auto& level1_msg = *(file_->message_type(idx));
    loader_impl_content.append("//");
    loader_impl_content.append(level1_msg.name());
  }
  string loader_impl_data = Util::LoadContent(GetFullPath("loader_impl.h"));
  Util::Replace(string("/** loader_impl_content **/"), loader_impl_content,
                &loader_impl_data);
  Print("loader_impl.h", loader_impl_data);
  LOG(INFO) << loader_impl_data;
  return true;
}

bool PBCodeGenerator::Print(const string& file_name,
                            const string& content) const {
  if (file_name.size() <= 0 || content.size() <= 0) {
    LOG(ERROR) << "Empty file or context.file_name=" << file_name;
    return false;
  }
  std::unique_ptr<ZeroCopyOutputStream> output(
      generator_context_->Open(file_name));
  Printer printer(output.get(), '$', nullptr);
  printer.Print(content.c_str());
  return true;
}

string PBCodeGenerator::GetFullPath(const string& file_name) const {
  return template_dir_ + "/" + file_name;
}

}  // namespace data
}  // namespace demo

int main(int argc, char* argv[]) {
  string runfiles_dir = Util::RealPath(argv[0]) + ".runfiles";
  LOG(INFO) << "runfiles_dir: " << runfiles_dir;

  vector<string> all_files;
  if (!Util::ListDir(runfiles_dir, &all_files, true)) {
    LOG(ERROR) << "fail to list directory: " << runfiles_dir;
    return -1;
  }

  string template_dir;
  for (auto& path : all_files) {
    string prefix = "src/data/template";
    if (path.find(prefix) != string::npos) {
      LOG(INFO) << path;
      template_dir = Util::DirName(path);
      break;
    }
  }
  LOG(INFO) << "template_dir: " << template_dir;
  demo::data::PBCodeGenerator generator(template_dir);
  return google::protobuf::compiler::PluginMain(argc, argv, &generator);
}
