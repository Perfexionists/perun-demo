// regex_match example
#include <iostream>
#include <string>
#include <regex>
#include <iostream>
#include <fstream>
#include <algorithm>

int main(int argc, char ** argv)
{
    std::ifstream file;
	file.open (argv[1]);
	if (!file.is_open()) return 0;

    std::ifstream regex_file;
	regex_file.open (argv[2]);
	if (!regex_file.is_open()) return 0;
	std::string line;
	getline(file, line);
	std::regex r(line);

	while(getline( file, line )){
		std::smatch m;
		std::regex_match(line, m, r);
    	for(auto v: m) std::cout << "# " << v << "|" << std::endl;
    }
	file.close();
}
