
#include "src/data/loader_impl.h"

#include <string>

#include "glog/logging.h"

namespace demo {
namespace data {

using std::string;

std::string LoaderImplToString() {
  demo::data::Test t;
  LOG(INFO) << t.ToString();
}

}  // namespace data
}  // namespace demo
