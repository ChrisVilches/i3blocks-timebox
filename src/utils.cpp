#include "utils.h"

#include <fcntl.h>
#include <unistd.h>

#include <iomanip>

namespace utils {
std::string format_seconds(int seconds) {
  const int minutes = seconds / 60;
  const int secs = seconds % 60;

  std::stringstream ss;
  ss << std::setw(2) << std::setfill('0') << minutes << ":";
  ss << std::setw(2) << std::setfill('0') << secs;
  return ss.str();
}

void redirect_to_file(const std::string& file) {
  const int fd = open(file.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0666);
  if (fd == -1) {
    perror("Failed to open file");
    return;
  }

  dup2(fd, STDOUT_FILENO);
  dup2(fd, STDERR_FILENO);
  close(fd);
}
}  // namespace utils
