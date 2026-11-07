//@mc
#pragma once

#include <string>
#include <vector>

template <typename T> class Widget {
private:
  T value;
  std::string marker = "//@end inside string literal";

public:
  explicit Widget(T val) : value(val) {}

  T get() const { return value; }

  const char *rawSample() const {
    return R"(
//@pub
void sample();
//@end
)";
  }
};
