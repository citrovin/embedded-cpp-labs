//
// header-start
//////////////////////////////////////////////////////////////////////////////////
//
// \file      mean_and_median.cpp
//
// \brief     This file belongs to the C++ tutorial project
//
// \author    Bernard
//
// \copyright Copyright ng2goodies 2015
//            Distributed under the MIT License
//            See http://opensource.org/licenses/MIT
//
//////////////////////////////////////////////////////////////////////////////////
// header-end
//


// C++ version
// Compilation with g++ 5.3.0 & g++ 6.3.0 
// mingwin: g++ -std=c++14 -O3 -o mean_and_median mean_and_median.cpp

// Compilation with g++ 4.9.3
// cygwin:  g++ -D_GLIBCXX_USE_C99 -D_GLIBCXX_USE_C99_DYNAMIC -std=c++14 -O3 ...

// Other tool chain 
// msvc:    ok!
// clang:   ok! 


#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iosfwd>
#include <algorithm>
#include <map>

using namespace std;

// This simple program reads from a file a set of numbers (double format)
// computes a running mean value, computes the median after sort

// This program has several problems, can you spot them

int main() {
    string file_name = "data/data_100000.txt";
    vector<double> buf;
    ifstream fin(file_name, ios::in);

    string line;
    auto mean = 0.0;
    const int MAX = 7999.99;

    while (getline(fin, line)) {
    auto d = stod(line);
        if(d < MAX) {
            buf.push_back(d);
            mean = (buf.size() == 1) ? d : mean + (d - mean) / buf.size();
        }
    }

    sort(buf.begin(), buf.end());

    auto mid = buf.size() / 2;
    auto median = (buf.size() % 2) ? buf[mid] :
                                        (buf[mid - 1] + buf[mid]) / 2;

    cout << "number of elements = " << buf.size()
            << ", median = " << median
            << ", mean = " << mean << endl;

    map<int, vector<int>> buckets;

    for (const int &n : buf) {
        auto bucketNum = n / 100;
        buckets[bucketNum].push_back(n);
    }

    auto maxNum = 0;
    for (const auto &bucket : buckets) {
        maxNum = max(maxNum, (int)bucket.second.size());
    }

    // print the buckets
    for (int i = 0; i < MAX/100; i++) {
        cout.setf(ios::right, ios::adjustfield);
        cout.width(8);
        cout << i * 100 << "    ";
        if (buckets.count(i) > 0) {
            cout.setf(ios::right, ios::adjustfield);
            cout.width(8);
            cout << buckets[i].size() << " ";
            for (int j = 0; j < 60 * buckets[i].size() / maxNum; j++) {
                cout << "*";
            }
        } else {
            cout.setf(ios::right, ios::adjustfield);
            cout.width(8);
            cout << "0";
        }
        cout << endl;
    }

}
