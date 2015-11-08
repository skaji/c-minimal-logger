#include "logger.h"

int main(void) {
  LOG_DEBUG("prints if LOG_DEBUG=1");
  LOG_INFO("hello %s!", "John");
  LOG_WARN("...");
  LOG_ERROR("failed %d tests", 100);
  return 0;
}
