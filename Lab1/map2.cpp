#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main() {
    string file_name = "data/full_1000.txt";

    map<string, double> data;
    unordered_multimap<double, string> val_to_id;
    string id;
    double value;

    ifstream inputFile(file_name);

    while (inputFile >> id >> value) {
        data[id] = value;
        val_to_id.emplace(value, id);
    }

    string query;
    
    cout << "query> ";
    while (cin >> query && query != "END") {
        if (query[0] == '+') {
            double value = stod(query);
            double lower_bound = value * 0.99;
            double upper_bound = value * 1.01;
            for (auto it = val_to_id.begin(); it != val_to_id.end(); ++it) {
                if (it->first >= lower_bound && it->first <= upper_bound) {
                    cout << "value[" << it->second << "]=" << " " << it->first << endl;
                }
            }
        } else {
            if(data.count(query) == 1) {
                cout << "value[" << query << "]= " << data[query] << endl; 
            } else {
                cout << "This ID does not exist" << endl << "query> ";
            }
        }
        cout << "query> ";
    }
    cout << "Bye..." << endl;
    return 0;
}
