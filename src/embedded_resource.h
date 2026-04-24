#pragma once

#include <string_view>

// Returns the embedded resource data as a string_view.
// The data is the content of data/sample.json, embedded at link time.
// The returned string_view points to read-only memory and is valid for the lifetime of the program.
std::string_view get_embedded_resource();