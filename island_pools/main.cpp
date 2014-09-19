#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

typedef std::vector<int> island_t;
typedef island_t::iterator island_it;
typedef island_t::const_iterator island_cit;

void solve(island_t& island) {
    island_it max = std::max_element(island.begin(), island.end());
    std::cout << *max << std::endl;

    int ** box = new int*[*max];
    for (int i = 0; i < *max; ++i) { box[i] = new int[*max]; }

    

    for (int i = 0; i < *max; ++i) { delete box[i]; }
    delete box;
}

void invalid_input() { std::cout << "Invalid input" << std::endl; }

bool not_number(char& c) { return c < '0' || c > '9'; }

int main(int argc, char **argv) {
    if (argc < 1) { return 0; }
    std::ifstream ifs(argv[1]);
    if (!ifs.good()) { return 0; }
    std::string line;
outer: while (getline(ifs, line)) {
        std::stringstream ss;
        island_t island;
        int n;
        ss << line;
        while(ss >> line) {
            if (!std::none_of(line.begin(), line.end(), not_number)) {
                invalid_input();
                goto outer;
            }
            n = stoi(line);
            island.push_back(n);
        }
        if (island.empty()) { invalid_input(); goto outer; }
        if (island.size() == 1 && island.at(0) == 0) { break; }
        solve(island);
    }
    ifs.close();
    return 0;
}
