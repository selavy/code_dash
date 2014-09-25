#include <iostream>
#include <string>
#include <cstddef>
#include <cstdlib>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>

using scalar_t = boost::multiprecision::cpp_int;
using index_t = int64_t;
typedef std::vector<scalar_t> seq_t;
typedef seq_t::iterator seq_it;
typedef seq_t::const_iterator seq_cit;

namespace {
  const scalar_t& fib(index_t s) {
    static seq_t seq;
    const std::size_t size = seq.size();
    if (size > s) {
      return seq[s];
    }
    if (size == 0) {
      seq.push_back(0);
      seq.push_back(1);
    }
    scalar_t last(0);
    for(index_t i = (size == 0 ? 2 : size); i <= s; ++i) {
      seq.push_back(seq[i-1] + seq[i-2]);
    }
    return seq[s];
  }
}

int main(int argc, char ** argv) {
  std::string line;
  while (getline(std::cin, line)) {
    index_t scalar = std::strtoll(line.c_str(), NULL, 10);
    std::cout << fib(scalar) << std::endl;
  }
  return 0;
}
