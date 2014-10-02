#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

typedef std::vector<int> island_t;
typedef island_t::iterator island_it;

struct not_num {
  bool operator()(const char& c) { return (c < '0' || c > '9') && (c != '-'); }
};
struct valid {
  static not_num n;
  bool operator()(const std::string& str) { return !std::none_of(str.begin(), str.end(), n);}
};
not_num valid::n;
void invalid() { std::cout << "Invalid input" << std::endl; }

void solve(island_t& island) {
  std::pair<island_it,island_it> minmax = std::minmax_element(island.begin(), island.end());
  int min = *(minmax.first);
  int max = *(minmax.second);
  int pools = 0;
  island_it end = island.end();
  island_it a;
  bool aset = false;
  for (int level = max; level > min; --level) {
    for (island_it it = island.begin(); it != end; ++it) {
      if(!aset && *it >= level) {
	aset = true; a = it;
      } else if (aset && *it >= level) {
	pools += std::distance(a,it) - 1; a = it;
      }
    }
    aset = false;
  }
  std::cout << pools << std::endl;
}

int main(int argc, char ** argv) {
  std::string line;
  while (getline(std::cin, line)) {
    std::vector<std::string> vals;
    island_t island;
    std::istringstream iss(line);
    vals.insert(vals.begin(),
  	     std::istream_iterator<std::string>(iss),
  	     std::istream_iterator<std::string>());
    int size = stoi(vals[0]);
    if (size == 0) { return 0; }
    if (size != (vals.size() - 1)) { invalid(); continue; }
    valid v;
    if (!std::none_of(vals.begin() + 1, vals.end(), v)) { invalid(); continue; }
    else {
      island_t island;
      std::for_each(vals.begin() + 1, vals.end(), [&island](const std::string& s) {
	  island.push_back(stoi(s));
	});
      solve(island);
    }
  }
  return 0;
}
