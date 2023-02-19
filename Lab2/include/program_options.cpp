// Inspired from https://medium.com/@mostsignificant/3-ways-to-parse-command-line-arguments-in-c-quick-do-it-yourself-or-comprehensive-36913284460f

#include "program_options.h"

#include <string>
#include <filesystem>
#include <stdexcept>
#include <vector>

namespace { // namespace

static std::vector<std::string> _input_files;
static bool _show_line_numbers = false;
static bool _show_ends = false;
static int num_points;
static int samples;
static std::string method;

}  // namespace

void program_options::parse(int argc, char* argv[]) {
    const std::vector<std::string> args(argv + 1, argv + argc);

    if(has_option(args, "-n")) {
        num_points = std::stoi(get_option(args, "-n"));
    }
    if(has_option(args, "-s")) {
        samples = std::stoi(get_option(args, "-s"));
    }
    if(has_files(args)) {
        num_points = -1;
    }
    if(has_option(args, "-m")){
        method = get_option(args, "-m");
    } 
}

const std::vector<std::string> program_options::input_files() {
    return _input_files;
}

bool program_options::show_ends() {
    return _show_ends;
}

bool program_options::show_line_numbers() {
    return _show_line_numbers;
}

std::string program_options::get_option(
    const std::vector<std::string>& args, 
    const std::string& option_name) {
    for (auto it = args.begin(), end = args.end(); it != end; ++it) {
        if (*it == option_name)
            if (it + 1 != end)
                return *(it + 1);
    }
    
    return "";
}

bool program_options::has_option(
    const std::vector<std::string>& args, 
    const std::string& option_name) {
    for (auto it = args.begin(), end = args.end(); it != end; ++it) {
        if (*it == option_name)
            return true;
    }
    
    return false;
}

bool program_options::has_files(const std::vector<std::string>& args) {
    bool file_found = false;
    for (const auto& arg : args) {
        if (std::filesystem::exists(arg) && std::filesystem::is_regular_file(arg)) {
            file_found = true;
            _input_files.push_back(arg);
        }
    }
    return file_found;
}