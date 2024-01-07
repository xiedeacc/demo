
#include "src/data/loader_impl.h"

#include <string>

#include "glog/logging.h"
#include "gtest/gtest.h"

namespace demo {
namespace data {

using std::string;

TEST(LoaderImpl, ToString) {
  demo::data::Test t;
  LOG(INFO) << t.ToString();
}

}  // namespace data
}  // namespace demo
