#include "src/void_data_maker.h"
#include <vector>
using std::vector;
using protobuf_plugin_demo::VoidDataMaker;
using foo::Foo;
using bar::Bar;
using protobuf_plugin_demo::BaseTypeMemory;

int main(const int argc, const char** argv) {
  vector<int> field_ids;
  Foo foo_fields;
  vector<const void *> void_data;
  BaseTypeMemory memory_holder;
  VoidDataMaker::Build(field_ids, foo_fields, &void_data, & memory_holder);
  return 0;
}
