// Inspired from https://medium.com/@mostsignificant/3-ways-to-parse-command-line-arguments-in-c-quick-do-it-yourself-or-comprehensive-36913284460f

#ifndef THAT_THIS_PROGRAM_OPTIONS_HEADER_FILE_IS_ALREADY_INCLUDED
#define THAT_THIS_PROGRAM_OPTIONS_HEADER_FILE_IS_ALREADY_INCLUDED

#include <string>
#include <vector>

namespace program_options {

    void parse(int argc, char* argv[]);

    const std::vector<std::string> input_files();
    std::string get_option(const std::vector<std::string>& args, const std::string& option_name);
    bool has_option(const std::vector<std::string>& args, const std::string& option_name);
    bool has_files(const std::vector<std::string>& args);
    bool show_ends();
    bool show_line_numbers();

    // TODO: Overwrite numpoints if input file specified
    int num_points = 5; // generate 5 random points by default
    // TODO: print how many samples were generated
    int samples = 3; // interpolate between them in 3 samples by default

    std::string method = "spline";

};  // namespace program_options

#endif  // THAT_THIS_PROGRAM_OPTIONS_HEADER_FILE_IS_ALREADY_INCLUDED