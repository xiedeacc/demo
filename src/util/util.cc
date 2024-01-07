
#include "src/util/util.h"

#include <charconv>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <random>
#include <thread>

#include "absl/time/clock.h"
#include "boost/algorithm/string.hpp"
#include "boost/algorithm/string/trim_all.hpp"
#include "boost/beast/core/detail/base64.hpp"
#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"
#include "boost/iostreams/device/mapped_file.hpp"
#include "fmt/core.h"
#include "fmt/format.h"
#include "glog/logging.h"
#include "google/protobuf/util/json_util.h"

using absl::FormatTime;
using absl::FromUnixMillis;
using absl::GetCurrentTimeNanos;
using absl::LoadTimeZone;
using absl::Milliseconds;
using absl::SleepFor;
using absl::Time;
using absl::TimeZone;
using namespace std;
using namespace google::protobuf::util;

namespace demo {
namespace util {

const char *Util::kPathDelimeter = "/";

int64_t Util::CurrentTimeMillis() {
  return absl::GetCurrentTimeNanos() / 1000000;
}

int64_t Util::NanoTime() { return GetCurrentTimeNanos(); }

uint64_t Util::Now() {
  auto duration_since_epoch = chrono::system_clock::now().time_since_epoch();
  auto microseconds_since_epoch =
      chrono::duration_cast<chrono::microseconds>(duration_since_epoch).count();
  time_t seconds_since_epoch =
      static_cast<time_t>(microseconds_since_epoch / 1000000);  // second
  return seconds_since_epoch;
}

uint64_t Util::StrTimeToTimestamp(const string &time, int32_t offset) {
  absl::Time t;
  string err;
  if (!absl::ParseTime("%Y-%m-%d%ET%H:%M:%E3S%Ez", time, &t, &err)) {
    LOG(ERROR) << "convert " << time << " " << err;
    return 0;
  }
  return absl::ToUnixMillis(t) + offset;
}

string Util::ToTimeString(const int64_t ts) {
  TimeZone time_zone;
  LoadTimeZone("Asia/Shanghai", &time_zone);
  return FormatTime("%Y-%m-%d %H:%M:%S", FromUnixMillis(ts), time_zone);
}

string Util::GetTodayString() {
  absl::Time now = absl::Now();
  absl::TimeZone loc = absl::LocalTimeZone();
  return absl::FormatTime("%Y-%m-%d", now, loc);
}

int64_t Util::Random(int64_t start, int64_t end) {
  static thread_local mt19937 generator(NanoTime());
  uniform_int_distribution<int64_t> distribution(start, end - 1);
  return distribution(generator);
}

void Util::Sleep(int64_t ms) {
  this_thread::sleep_for(chrono::milliseconds(ms));
}

void Util::SleepUntil(const Time &time) {
  volatile bool signal = false;
  SleepUntil(time, &signal);
}

bool Util::SleepUntil(const Time &time, volatile bool *stop_signal) {
  auto now = absl::Now();
  if (time <= now) {
    return true;
  }
  while (absl::Now() < time) {
    if (*stop_signal) {
      return false;
    }
    SleepFor(Milliseconds(100));
  }
  return true;
}

string Util::GetNacosNamingServiceUrl(const string &nacos_sdk_addr,
                                      const string &service_name,
                                      const string &group_name,
                                      const string &namespace_id,
                                      const string &clusters,
                                      bool healthy_only) {
  return string("nacos://") + "serviceName=" + service_name +
         "&groupName=" + group_name + "&namespaceId=" + namespace_id +
         "&clusters=" + clusters +
         "&healthyOnly=" + (healthy_only ? "true" : "false");
}

string Util::DirName(const string &path) {
  boost::filesystem::path file_path(path);
  return file_path.parent_path().string();
}

string Util::BaseName(const string &path) {
  boost::filesystem::path file_path(path);
  return file_path.filename().string();
}

std::string Util::FileExtention(const std::string &path) {
  boost::filesystem::path file_path(path);
  return file_path.extension().string();
}

bool Util::Remove(const string &dir, const string &file) {
  string path;
  if (dir.empty()) {
    path = file;
  } else if (dir[dir.size() - 1] == '/') {
    path = dir + file;
  } else {
    path = dir + "/" + file;
  }

  try {
    if (boost::filesystem::exists(path)) {
      return boost::filesystem::remove(path);
    }
  } catch (exception &e) {
    LOG(ERROR) << e.what();
    return false;
  }

  return true;
}

bool Util::Remove(const string &dir) {
  try {
    if (boost::filesystem::exists(dir)) {
      return boost::filesystem::remove_all(dir);
    }
  } catch (const boost::filesystem::filesystem_error &e) {
    LOG(ERROR) << e.what();
    return false;
  }

  return true;
}

bool Util::Mkdir(const string &dir) {
  try {
    boost::filesystem::create_directory(dir);
  } catch (const std::exception &e) {
    LOG(ERROR) << "Mkdir " << dir << " error";
    return false;
  }
  return true;
}

bool Util::Exist(const string &path) {
  return access(path.c_str(), F_OK) != -1;
}

string Util::TruncatePath(const string &src, const string &path) {
  string real_path = boost::filesystem::canonical(src).string();
  std::string::size_type n = real_path.find(path);
  if (n != string::npos) {
    return real_path.substr(0, n);
  }
  return "";
}

string Util::RealPath(const string &path) {
  return boost::filesystem::canonical(path).string();
}

bool Util::ListDir(const string &path, vector<string> *files,
                   const bool recursive) {
  if (!files) {
    return true;
  }
  try {
    boost::filesystem::path dir_path(path);
    if (!boost::filesystem::is_directory(dir_path)) {
      return false;
    }
    if (recursive) {
      boost::filesystem::recursive_directory_iterator it(dir_path);
      boost::filesystem::recursive_directory_iterator end;
      for (; it != end; ++it) {
        if (boost::filesystem::is_regular_file(it->status())) {
          files->emplace_back(it->path().string());
        }
      }
    } else {
      boost::filesystem::directory_iterator it(dir_path);
      boost::filesystem::directory_iterator end;
      for (; it != end; ++it) {
        if (boost::filesystem::is_regular_file(it->status())) {
          files->emplace_back(it->path().string());
        }
      }
    }
  } catch (const exception &e) {
    LOG(ERROR) << e.what();
    return false;
  }
  return true;
}

bool Util::CopyFile(const string &src_file_path, const string dst_file_path) {
  return boost::filesystem::copy_file(src_file_path, dst_file_path);
}

bool Util::Copy(const string &src_path, const string dst_path) {
  try {
    boost::filesystem::copy(src_path, dst_path,
                            boost::filesystem::copy_options::recursive);
  } catch (std::exception &e) {
    LOG(ERROR) << "copy " << src_path << " to " << dst_path << " exception, "
               << e.what();
    return false;
  }
  return true;
}

bool Util::WriteToFile(const string &dir, const string &file,
                       const string &content) {
  boost::filesystem::path path;
  if (dir.empty()) {
    path = file;
  } else if (dir[dir.size() - 1] == '/') {
    path = dir + file;
  } else {
    path = dir + "/" + file;
  }

  try {
    if (!boost::filesystem::exists(dir)) {
      boost::filesystem::create_directories(dir);
    }

    if (boost::filesystem::exists(path)) {
      boost::filesystem::remove(path);
    }

    boost::filesystem::ofstream ofs(path);
    if (ofs.is_open()) {
      ofs << content;
      ofs.close();
    } else {
    }

  } catch (exception &e) {
    LOG(ERROR) << path.string() << " " << e.what();
    return false;
  }

  return true;
}

std::istream &Util::GetLine(std::istream &is, std::string *line) {
  line->clear();
  std::istream::sentry se(is, true);
  std::streambuf *sb = is.rdbuf();

  for (;;) {
    int c = sb->sbumpc();
    switch (c) {
      case '\n':
        return is;
      case '\r':
        if (sb->sgetc() == '\n') sb->sbumpc();
        return is;
      case std::streambuf::traits_type::eof():
        if (line->empty()) is.setstate(std::ios::eofbit);
        return is;
      default:
        line->push_back((char)c);
    }
  }
}

string Util::LoadContent(const string &file_name) {
  ifstream in(file_name);
  if (!in) {
    LOG(ERROR) << "Fail to open " << file_name;
    return "";
  }
  stringstream buffer;
  buffer << in.rdbuf();
  in.close();
  return buffer.str();
}

vector<string> Util::LoadLines(const string &file_name) {
  ifstream in(file_name);
  if (!in) {
    LOG(ERROR) << "Fail to open " << file_name;
    return vector<string>();
  }
  vector<string> ret;
  string line;
  while (getline(in, line)) {
    ret.push_back(line);
  }
  in.close();
  return ret;
}

string Util::ToUpper(const string &str) {
  string ret = str;
  transform(ret.begin(), ret.end(), ret.begin(),
            [](unsigned char c) { return toupper(c); });
  // transform(ret.begin(), ret.end(), ret.begin(), ::toupper);
  return ret;
}

string Util::ToLower(const string &str) {
  string ret = str;
  transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
  return ret;
}

void Util::ToLower(string *str) {
  transform(str->begin(), str->end(), str->begin(), ::tolower);
}

void Util::Trim(string &str) {
  boost::algorithm::trim_right(str);
  boost::algorithm::trim_left(str);
}

bool Util::ToInt(const string &str, uint32_t *value) {
  auto result = std::from_chars(str.data(), str.data() + str.size(), *value);
  if (result.ec != std::errc{}) {
    return false;
  }
  return true;
}

bool Util::StartWith(const string &str, const string &prefix) {
  return boost::starts_with(str, prefix);
}

void Util::ReplaceAll(string &s, const string &from, const string &to) {
  boost::algorithm::replace_all(s, from, to);
}

void Util::Split(const string &str, const string &delim, vector<string> &result,
                 bool trim_empty) {
  result.clear();
  if (str.empty()) {
    return;
  }
  if (trim_empty) {
    string trimed_str = boost::algorithm::trim_all_copy(str);
    boost::split(result, trimed_str, boost::is_any_of(delim));
    return;
  }
  boost::split(result, str, boost::is_any_of(delim));
}

string Util::ToString(const set<uint64_t> &ids) {
  string ret;
  ret.resize(512);
  bool first = true;
  for (auto id : ids) {
    if (first) {
      first = false;
      ret.append(to_string(id));
      continue;
    }
    ret.append(",");
    ret.append(to_string(id));
  }
  return ret;
}

std::string Util::ToString(const map<string, string> &vars) {
  string ret;
  ret.resize(512);
  bool first = true;
  for (auto &p : vars) {
    if (first) {
      first = false;
      ret.append(p.first);
      ret.append("=");
      ret.append(p.second);
      continue;
    }
    ret.append("&");
    ret.append(p.first);
    ret.append("=");
    ret.append(p.second);
  }
  return ret;
}

string Util::Base64Encode(const string &input) {
  string output;
  try {
    output.resize(boost::beast::detail::base64::encoded_size(input.size()));
    auto const ret = boost::beast::detail::base64::encode(
        output.data(), input.data(), input.size());
    output.resize(ret);
  } catch (exception &e) {
    LOG(INFO) << "Base64 encode error";
  }
  return output;
}

string Util::Base64Decode(const string &input) {
  string output;
  try {
    output.resize(boost::beast::detail::base64::decoded_size(input.size()));
    auto const ret = boost::beast::detail::base64::decode(
        output.data(), input.data(), input.size());
    output.resize(ret.first);
  } catch (exception &e) {
    LOG(INFO) << "Base64 decode error";
  }
  return output;
}

uint64_t Util::HexStrToUInt64(const string &in) {
  try {
    return std::stoull(in, nullptr, 16);
  } catch (std::exception &e) {
    LOG(ERROR) << "Parse error: " << in;
  }
  return 0;
}

string Util::UInt64ToHexStr(const uint64_t in) {
  try {
    return fmt::format("{:016x}", in);
  } catch (std::exception &e) {
    LOG(ERROR) << "Parse error: " << in;
  }
  return "";
}

void Util::PrintProtoMessage(const google::protobuf::Message &msg) {
  JsonOptions option;
  option.add_whitespace = false;
  option.always_print_primitive_fields = true;
  option.preserve_proto_field_names = true;
  string json_value;
  if (!MessageToJsonString(msg, &json_value, option).ok()) {
    LOG(ERROR) << "to json string failed";
  }
  LOG(INFO) << "json_value: " << json_value;
}

void Util::Replace(const string &from, const string &to, string *str) {
  size_t start_pos = str->find(from);
  if (start_pos == std::string::npos) {
    return;
  }
  str->replace(start_pos, from.length(), to);
}

}  // namespace util
}  // namespace demo
