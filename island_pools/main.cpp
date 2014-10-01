#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <utility>

typedef std::vector<int> island_t;
typedef island_t::iterator island_it;
typedef island_t::reverse_iterator island_rit;

std::pair<int,int> sub(island_t& island, int& answer) {
  assert(island.size() > 0);
  int left = 0;
  int right = island.size() - 1;
  while (right - left > 1) {
    if (island[left] < island[left+1]) ++left;
    else break;
  }
  while (right - left > 1) {
    if (island[right] < island[right-1]) --right;
    else break;
  }

  int dist = right - left - 1;
  int height = (island[left] < island[right] ? island[left] : island[right]);
  int area = dist * height;

  for (int i = left + 1; i < right; ++i) {
    area -= (island[i] < height) ? island[i] : height;
  }  

  for (int i = left; i < island.size(); ++i) {
    if (island[i] > height) island[i] -= height;
    else island[i] = 0;
  }

  answer += area;
  return std::make_pair(0,0);
}

void solve(island_t& island) {
  int answer = 0;
  sub(island, answer);
  std::cout << answer << std::endl;
}

void invalid_input() { std::cout << "Invalid input" << std::endl; }

bool not_number(char& c) { return (c < '0' || c > '9') && c != '-'; }

int main(int argc, char **argv) {
  std::string line;
 outer: while (getline(std::cin, line)) {
        std::stringstream ss;
        island_t island;
        int n;
	int size;
        ss << line;
	ss >> line;
	if (!std::none_of(line.begin(), line.end(), not_number)) {
	  invalid_input();
	  goto outer;
	}
	size = stoi(line);
	if (size == 0) { break; }
        while(ss >> line) {
            if (!std::none_of(line.begin(), line.end(), not_number)) {
                invalid_input();
                goto outer;
            }
            n = stoi(line);
            island.push_back(n);
        }
        if (island.empty()) { invalid_input(); goto outer; }
	if (island.size() != size) { invalid_input(); goto outer; }
        solve(island);
    }
    return 0;
}
