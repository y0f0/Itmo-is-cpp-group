#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

using namespace std;


vector<string> Split(const string& str) {

    istringstream iss(str);
    vector<string> results((istream_iterator<string>(iss)),
                                 istream_iterator<string>());
    return results; 
}

class Report {
private:
    vector<string> template_report;
    vector<string> params;
public:
    Report(const vector<string>& new_template_report, const vector<string>& new_params) {
        template_report = new_template_report;
        params = new_params; 
    }
    vector<vector<string> > GenerateTemplate() {
        vector<vector<string> > result;
        for (const string& line : template_report) {
            result.push_back(Split(line));
        }
        int i = 0;
        for (vector<string>& vs : result) {
            for (string& str : vs) {
                if (str[0] == '{') {
                    str = '{' + params[i++] + '}';
                }
            }
        }        
        return result;
    }
};


vector<string> ReadFile(const string& path) {
    string line;
    vector<string> input_data;

    ifstream in(path); 

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

    for (auto v : r.GenerateTemplate()) {
        for (auto str : v) {
            cout << str <<  ' ';
        }
        cout << endl;
    }
    return 0; 
}