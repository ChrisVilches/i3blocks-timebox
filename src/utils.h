#pragma once
#include <mutex>
#include <string>

namespace utils {
static std::mutex print_mtx;

std::string format_seconds(int seconds);
void redirect_to_dev_null();
void print_line(const std::string& s);
}  // namespace utils
