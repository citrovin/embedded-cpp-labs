#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

int main() {
    string file_name = "data/full_10.txt";

    map<string, double> data;
    string id;
    double value;

    ifstream inputFile(file_name);

    while (inputFile >> id >> value) {
        data[id] = value;
    }

    string query;
    cout << "query> ";
    while (cin >> query && query != "END") {
        if(data.count(query) == 1) {
                cout << "value[" << query << "]= " << data[query] << endl; 
        } else {
            cout << "This ID does not exist" << endl << "query> ";
        }
    }
    cout << "Bye..." << endl;
    return 0;
}
