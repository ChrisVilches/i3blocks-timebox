#include "utils.h"

#include <fcntl.h>
#include <unistd.h>

#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>

namespace utils {
std::string format_seconds(int seconds) {
  const int minutes = seconds / 60;
  const int secs = seconds % 60;

  std::stringstream ss;
  ss << std::setw(2) << std::setfill('0') << minutes << ":";
  ss << std::setw(2) << std::setfill('0') << secs;
  return ss.str();
}

void redirect_to_dev_null() {
  const int fd = open("/dev/null", O_WRONLY);
  dup2(fd, 1);
  dup2(fd, 2);
  close(fd);
}

void print_line(const std::string& s) {
  std::lock_guard<std::mutex> lock(print_mtx);
  std::cout << s << std::endl;
}

}  // namespace utils
