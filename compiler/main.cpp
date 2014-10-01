#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

int main(int argc, char ** argv) {
  typedef std::function<void()> func_t;
  std::vector<func_t> vec;
  vec.push_back([]() { std::cout << "Hello World" << std::endl; });
  std::for_each(vec.begin(), vec.end(), [](func_t f) { f(); });
  return 0;
}
    
