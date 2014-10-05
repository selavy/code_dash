#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cstddef>
#include <cassert>
#include <climits>

template<int64_t N> struct length_of;

template<> struct length_of<0> { enum { length = 1 }; };

template <int64_t N>
struct length_of {
  enum { length = 1 + (N / 10 > 0 ? length_of<N / 10>::length : 0) };
};


// struct BigNum {
//   BigNum() : str_(), too_big_(false), n_(0) {}

//   explicit BigNum(int64_t n) : str_(std::to_string(n)), n_(n), too_big_(false) {
//   }
//   explicit BigNum(std::string str) : str_(str), too_big_(true) {
//     if (str.length() < (length_of<LLONG_MAX>::length - 1)) {
//       too_big_ = false;
//       n_ = stoll(str);
//     }
//   }
//   ~BigNum() {}
//   std::string to_str() const {
//     return str_;
//   }
//   BigNum& 
// private:
//   friend std::ostream& operator<< (std::ostream& os, const BigNum& n) {
//     os << n.to_str();
//     return os;
//   }
//   std::string str_;
//   int64_t n_;
//   bool too_big_;
// };

enum type_t { ARITHMETIC = 0, GEOMETRIC };
typedef int64_t scalar_t;
typedef std::vector<std::pair<scalar_t, scalar_t> > errors_t;
typedef errors_t::iterator errors_it;
typedef errors_t::const_iterator errors_cit;

typedef std::vector<scalar_t> series_t;
typedef series_t::iterator series_it;
typedef series_t::const_iterator series_cit;
typedef std::string::iterator string_it;
typedef std::string::const_iterator string_cit;

int arith = 0;
int geo = 0;
int total_errors = 0;


std::ostream& print_results(std::ostream& os, int ar, int geo, int errors) {
  os << "Total of " << ar << " arithmetic and " << geo << " geometric progressions, total of ";
  if (errors == 1) {
    os << "1 error.";
  } else {
    os << errors << " errors.";
  }
  os << std::endl;
  return os;
}

std::ostream& print_line(std::ostream& os, type_t type, int line, int terms, errors_t& errors) {
  static int n = 1;
  os << n << ". Line " << line << ": " << (type == ARITHMETIC ? "arithmetic" : "geometric") << ": " << terms << " terms, ";
  total_errors += errors.size();
  if (errors.size() == 1) {
    os << "1 error";
  } else {
    os << errors.size() << " errors";
  }
  
  if (!errors.empty()) {
    os << ": ";
    errors_cit end = errors.end();
    for (errors_it it = errors.begin(); it != end; ++it) {
      os << it->first << ": " << it->second;
      if ((it + 1) != end) { os << ", "; }
    }
  }
  os << '\n';
  n++;
  return os;
}

bool is_num(char c) {
  return c >= '0' && c <= '9';
}
bool is_period(char c) {
  return c == '.';
}
bool is_eol(char c) {
  return c == '\n';
}

bool is_arith(series_t& series) {
  assert(series.size() > 2);

  int diff = series[1] - series[0];
  if (diff == (series[2] - series[1])) { ++arith; return true; }
  else { ++geo; return false; }
}

std::ostream& solve(std::ostream& os, int line, series_t& series) {
  assert(series.size() > 2);
  bool arithmetic = is_arith(series);
  errors_t errors;
  if (arithmetic) {
    // first 3 terms must be correct
    int diff = series[1] - series[0];
    for (series_it it = series.begin() + 1; it != series.end(); ++it) {
      if (diff != (*it - *(it - 1))) {
	scalar_t correct = *(it - 1) + diff;
	errors.emplace_back(*it, correct);
	*it = correct;
      }
    }
    print_line(os, ARITHMETIC, line, series.size(), errors);
  } else {
    assert(series[0] != 0);
    int m = series[1] / series[0];
    for (series_it it = series.begin() + 1; it != series.end(); ++it) {
      if ((*(it-1) * m) != *it) {
	scalar_t correct = *(it-1) * m;
	errors.emplace_back(*it, correct);
	*it = correct;
      }
    }
    print_line(os, GEOMETRIC, line, series.size(), errors);
  }
  return os;
}

int main(int argc, char ** argv) {
  // BigNum b(0);
  // std::cout << b << std::endl;
  // BigNum c(std::string("0"));
  // std::cout << c << std::endl;
  // return 0;


  std::string line;
  series_t series;
  int line_number = 0;
  int start_line = 0;
  
  while (getline(std::cin, line)) {
    ++line_number;
    string_cit end = line.end();
    for (string_cit it = line.begin(); it < end; ++it) {
      if (series.empty()) { start_line = line_number; } 
      if (is_num(*it)) {
 	std::string num;
 	num.push_back(*it);
 	++it;
 	while (it < end) {
 	  if (is_num(*it) && (it + 1) >= end) {
 	    num.push_back(*it);
 	    if (!getline(std::cin, line)) {
 	      solve(std::cout, line_number, series); goto end;
 	    }
 	    ++line_number;
 	    it = line.begin();
 	    end = line.end();
 	    continue;
 	  } else if (!is_num(*it)) {
 	    break;
 	  }
 	  num.push_back(*it);
 	  ++it;
 	}
 	series.push_back(std::stod(num));
 	--it;
      } else if (!series.empty() && is_period(*it)) {
 	solve(std::cout, start_line, series);
 	series.clear();
      }
    }
  }

 end:
  print_results(std::cout, arith, geo, total_errors);
  return 0;
}
