#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip>

using std::string;
using std::vector;

int main(int argc, char *argv[]) {
  const int MAX = 8000;

  string file_name{argv[1]};
  std::vector <double> buf;
  std::vector <int> vec(MAX/100,0);
  std::ifstream fin(file_name, std::ios::in);

  string line;
  auto mean = 0.0;

  while (std::getline(fin, line)) {
    auto d = std::stod(line);
    buf.push_back(d);
    mean = (buf.size() == 1) ? d : mean + (d - mean) / buf.size();
    if ( d>0 && d<MAX) vec.at((int)(d/100))++; 
  }

  std::sort(buf.begin(), buf.end());

  auto mid = buf.size() / 2;
  double median = (buf.size() % 2) 
                        ? buf[mid] : (buf[mid - 1] + buf[mid]) / 2;

  std::cout << "number of elements = " << buf.size()
            << ", median = " << median
            << ", mean = " << mean << std::endl;
  
  double highest = *std::max_element(vec.begin(), vec.end());

  for (auto it = vec.begin(); it != vec.end(); ++it){
    std::cout << std::right << std::setw(8) << (it-vec.begin())*100  << std::setw(8) << *(it) << " ";
    for (int i=0; i<(*it/highest)*60; i++) std::cout << "*";
    std::cout << "\n";
  }
}
