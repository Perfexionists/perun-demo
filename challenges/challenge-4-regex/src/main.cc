// regex_match example
#include <iostream>
#include <string>
#include <regex>
#include <iostream>
#include <fstream>
#include <algorithm>

int main(int argc, char ** argv)
{
    if (argc != 3) {
        std::cerr << "usage: " << argv[0] << " <regex> <filename>" << std::endl;
        return 1;
    }    

    std::ifstream regex_file;
    regex_file.open(argv[1]);
    if (!regex_file.is_open()) {
        std::cerr << "could not open regex file: " << argv[1] << std::endl;
        return 1;
    }
    std::string line;
    getline(regex_file, line);
    std::regex r(line);
    regex_file.close();

    std::ifstream file;
    file.open (argv[2]);
    if (!file.is_open()) {
        std::cerr << "could not open input file: " << argv[2] << std::endl;
        return 1;
    }

    while(getline( file, line )){
        std::smatch m;
        std::regex_match(line, m, r);
        for(auto v: m) std::cout << "match: " << v << std::endl;
    }
    file.close();
}
