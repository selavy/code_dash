#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>

typedef std::vector<std::string> players_t;
typedef players_t::iterator players_it;
typedef players_t::const_iterator players_cit;
typedef std::vector<int> scores_t;
typedef scores_t::iterator scores_it;
typedef scores_t::const_iterator scores_cit;

typedef bool direction_t;
#define FORWARD true
#define BACKWARD false

void whoops() { std::cout << "Whoops!"; }

bool contains_seven(int n) { 
  while(n > 1) {
    if (n % 10 == 7) { return true; }
    n /= 10;
  }
  return false;
}

bool sum_digits(int n) {
  int sum = 0;
  while(n > 0) {
    sum += n % 10;
    n /= 10;
  }
  return sum % 7 == 0;
}

void play_game(players_t& players, int games) {
  scores_t scores;
  scores.resize(players.size());
  size_t pos = 0;
  for (int i = 0; i < games; ++i) {
    direction_t direction = FORWARD;
    int n = 1;
    bool lose = false;
    bool last_whoops = false;
    while (!lose) {
      std::cout << players[pos] << "-";
      if (contains_seven(n)) {
	if (players[pos] == "Michael") {
	  std::cout << n; lose = true; scores[pos]++;
	} else if (players[pos] == "JR") {
	  std::cout << n; lose = true; scores[pos]++;
	} else {
	  whoops(); direction ^= FORWARD; ++n; last_whoops = true;
	}
      } else if (n % 7 == 0) {
	if (players[pos] == "Tim") {
	  std::cout << n; lose = true; scores[pos]++;
	} else if (players[pos] == "JR") {
	  std::cout << n; lose = true; scores[pos]++;
	} else {
	  whoops(); direction ^= FORWARD; ++n; last_whoops = true;
	}
      } else if (sum_digits(n)) {
	if (players[pos] == "JR") {
	  std::cout << n; lose = true; scores[pos]++;
	} else if (players[pos] == "Lyndsey") {
	  std::cout << n; lose = true; scores[pos]++;
	} else {
	  whoops(); direction ^= FORWARD; ++n; last_whoops = true;
	}
      } else { 
	if (players[pos] == "Richard" && last_whoops) {
	  lose = true; scores[pos]++;
	} else {
	  std::cout << n; ++n;
	}
	last_whoops = false;
      }
      std::cout << std::endl;
    
      if(!lose) {
	if (direction == FORWARD) {
	  pos = (pos + 1) % players.size();
	} else {
	  pos = (pos == 0 ? players.size() - 1 : pos - 1);
	}
      }
      // safety catch
      if (n > 1000) { lose = true; }
      if (lose) { std::cout << "END OF ROUND" << std::endl; }
    }

  }
  players_cit player = players.begin();
  for (scores_cit it = scores.begin(); it != scores.end(); ++it, ++player) {
    std::cout << *player << ": " << *it << std::endl;
  }
  std::cout << "--" << std::endl;
}

int main(int argc, char ** argv) {
  std::string line;
  while(getline(std::cin, line)) {
    players_t players;
    auto pos = 0;
    auto ppos = 0;
    pos = line.find(' ');
    while(pos != std::string::npos) {
      players.push_back(line.substr(ppos, pos-ppos));
      ppos = pos+1;
      pos = line.find(' ', ppos);
    }
    players.push_back(line.substr(ppos));
    int games = 0;
    getline(std::cin, line);
    games = std::stoi(line.c_str(), NULL, 10);
    play_game(players, games);
  }
  return 0;
}
