#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

int main(int argc, char *argv[]){
    std::string file_name{argv[1]};

    // read the data and store them in a map structure
    std::ifstream fin(file_name, std::ios::in);
    std::string line;

    std::unordered_map<std::string, double> mp;

    while (std::getline(fin, line)) {
        std::string id;
        std::string value;
        std::istringstream stream(line);
        
        stream >> id >> value;
        mp.insert({id, std::stod(value)});
    }

    while(1){
        // get a query from the user 
        std::cout << "query> ";

        std::string input;
        std::cin >> input;

        bool foundValue = false;
        if(input[0] == '+'){
            // find all ids and values that deviate 1% from input value
            double dinput = std::stod(input);

            for (auto &it : mp){
                if (it.second > (dinput*0.99) && it.second < (dinput*1.01)) {
                    std::cout << "value[" << (it.first) << "] = " << (it.second) << "\n";
                    foundValue = true;
                }
            }
            if(foundValue == false) std::cout << "No ID for the given value\n";

        }else{

            // Terminate program with keyword END
            if(input == "END"){
                std::cout << "Bye... \n";
                return 0;
            }

            // find values to corresponding key
            (mp.count(input) == 0) ? std::cout << "This ID does not exists\n" : std::cout << "value[" << input << "] = " << mp.at(input) << "\n";
        }
        
    }
}