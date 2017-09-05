#ifndef __MAKE_ANSWER_HPP__
#define __MAKE_ANSWER_HPP__

#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <unistd.h>
#include <ctime>
#include <fstream>
#include "logger.hpp"

namespace mpl {

class Make_answer {
public:
 
    struct Answer_msg {
        std::vector<std::string> header;
        std::string data;
    };

    Make_answer(const Make_answer&) = delete;
    const Make_answer& operator = (Make_answer&);

    Make_answer() {}

    const std::string& get_answer() {
        return prep_answer_;
    }

    void make_answer(std::string request) {
        std::regex pat {R"(^(?:\s*)(GET|HEAD)(?:\s+)(.*)(?:\s+)(HTTP/(?:\d+(?:\.\d+)?))(?:\s+)(?:.+))"};
        std::smatch matches;
        regex_search(request, matches, pat);
        Answer_msg answer;

        prep_answer_.clear();

        std::string temp_data;
        
        std::ifstream fin(matches.str(2));

        if (matches.str(1) != "GET" && matches.str(1) != "HEAD") {
            answer.header.push_back((matches.str(3) + " 400 Bad Request")); 
            temp_data = "400 Bad Request";
        }
        else if (!fin.is_open()) {
            answer.header.push_back((matches.str(3) + " 404 Not Found"));
            temp_data = "404 File Not Found";
        }
        else {
                answer.header.push_back((matches.str(3) + " 200 OK"));   
                answer.header.push_back("Content-Description: File Transfer");
                answer.header.push_back("Content-Disposition: attachment; filename=" + matches.str(2)); 
                answer.header.push_back("Expires: 0");
                answer.header.push_back("Pragma: public");
                answer.header.push_back("Cache-Control: must-revalidate");

                std::string str_f;
                while (std::getline(fin, str_f)) {
                    temp_data += str_f + "\n";
                }
            }

        fin.close();
        
        std::time_t t = std::time(nullptr);

        std::string time(std::asctime(std::gmtime(&t)));
        time.pop_back();
        answer.header.push_back("Date: " + time + " GMT");
     
        answer.data = temp_data;

        answer.header.push_back("Content-Length: " + std::to_string(answer.data.size()));

        for (std::string std_a : answer.header)  {
            prep_answer_ += (std_a + "\n");
        }

        prep_answer_ += "\n";
    
        prep_answer_ += answer.data;
     }


private:
    std::string prep_answer_;
};
}


#endif
