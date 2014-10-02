#include <cstddef>
#include <string>
#include <iterator>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <unordered_map>

typedef int32_t scalar_t;
typedef std::vector<std::string> names_t;
typedef names_t::iterator names_it;

bool contain_seven(scalar_t n) {
  while (n > 6) {
    if (n % 10 == 7) return true;
    n /= 10;
  }
  return false;
}
bool divisible_by_seven(scalar_t n) { return n % 7 == 0; }
bool sum_is_seven(scalar_t n) {
  int sum = 0;
  while (n > 0) {
    sum += n % 10;
    n /= 10;
  }
  return sum == 7;
}

void whoops(bool& dir, bool& w) { std::cout << "Whoops!"; dir ^= true; w = true; }

// Whoops on:
// containing a 7
// divisible by 7
// sum of digits = 7
void play_game(const names_t& names, scalar_t games) {
  int player = 0;
  int num_players = names.size();
  typedef std::unordered_map<std::string, scalar_t> scores_t;
  scores_t scores;
  for_each(names.begin(), names.end(), [&scores](const std::string& it) { scores.insert(std::make_pair(it, 0));});

  for (int g = 0; g < games; ++g) {
  int n = 1;
  bool dir = true;
  bool w = false;
  bool wrong = false;
  for (;!wrong;) {
    std::string p = names[player];
    std::cout << p << "-";

    if (w && p == "Richard") {
      wrong = true;
      scores[p]++;
    } else {
      bool cs = contain_seven(n);
      bool ds = divisible_by_seven(n);
      bool ss = sum_is_seven(n);
      if (p == "JR" && (cs || ds || ss)) {
	std::cout << n; wrong = true; scores[p]++;
      } else if (cs && !ds && !ss && p == "Michael") {
	std::cout << n; wrong = true; scores[p]++;
      } else if (!cs && ds && !ss && p == "Tim") {
	std::cout << n; wrong = true; scores[p]++;
      } else if (!cs && !ds && ss && p == "Lyndsey") {
	std::cout << n; wrong = true; scores[p]++;
      } else if (cs || ds || ss) {
	whoops(dir, w);
      } else {
	w = false;
	std::cout << n;
      }
    }
    ++n;
    std::cout << std::endl;
    // go to next player
    if(!wrong) {
      if (dir) { player = (player + 1) % num_players; }
      else { player = ((player == 0) ? num_players - 1 : player - 1); }
    }
  }
  std::cout << "END OF ROUND" << std::endl;
  }

  for_each(names.begin(), names.end(), [&scores](const std::string& it) {
      std::cout << it << ": " << scores[it] << std::endl;
    });
  std::cout << "--" << std::endl;
}

int main(int argc, char ** argv) {
  std::string line;
  while (getline(std::cin, line)) {
    names_t names;
    std::istringstream iss(line);
    names.insert(names.begin(), 
		 std::istream_iterator<std::string>(iss),
		 std::istream_iterator<std::string>());
    if(!getline(std::cin, line)) { return 0; }
    scalar_t games = std::stoi(line, nullptr);
    play_game(names, games);
  }
  return 0;
}
