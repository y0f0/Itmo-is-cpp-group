#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>


std::vector<std::string> Split(const std::string& str) {

    std::istringstream iss(str);
    std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                 std::istream_iterator<std::string>());
    return results; 
}

class Report {
private:
    std::vector<std::string> template_report;
    std::vector<std::string> params;
public:
    Report(const std::vector<std::string>& new_template_report, const std::vector<std::string>& new_params):
        template_report(new_template_report),
        params(new_params) {}
 
    std::vector<std::vector<std::string> > GenerateTemplate() {
        std::vector<std::vector<std::string> > result;
        for (const std::string& line : template_report) {
            result.push_back(Split(line));
        }
        int i = 0;
        for (std::vector<std::string>& vs : result) {
            for (std::string& str : vs) {
                if (str[0] == '{') {
                    str = params[i++]; 
                }
            }
        }        
        return result;
    }
};

std::vector<std::string> ReadFile(const std::string& path) {
    std::string line;
    std::vector<std::string> input_data;

    std::ifstream in(path); 

    if (in.is_open()) {
        while (getline(in, line)) {
            input_data.push_back(line);
        }
    }
    
    in.close();     

    return input_data;
}


int main() {

    Report r (ReadFile("input"), ReadFile("params"));

    for (const auto& v : r.GenerateTemplate()) {
        for (const auto& str : v) {
            std::cout << str <<  ' ';
        }
        std::cout << std::endl;
    }

    return 0; 
}