#include "embedded_resource.h"
#include <string_view>

// These symbols are provided by the linker when we use llvm-objcopy to embed the resource.
// The symbols are: _binary_sample_json_start and _binary_sample_json_end
extern "C" {
  extern const char _binary_sample_json_start[];
  extern const char _binary_sample_json_end[];
}

std::string_view get_embedded_resource() {
  const char* begin = _binary_sample_json_start;
  const char* end   = _binary_sample_json_end;
  return std::string_view(begin, end - begin);
}