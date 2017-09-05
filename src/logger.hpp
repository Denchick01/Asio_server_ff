#ifndef __BPS_LOGGER_HPP_
#define __BPS_LOGGER_HPP_
  
#include <cassert>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iostream>

#ifndef LOG_FILE_NAME
    #define LOG_FILE_NAME "server.log"
#endif

#define LOG_INFO(...)\
    mpl::Logger::get_logger(LOG_FILE_NAME).push_log_string("FILE: ", __FILE__ , " LINE: ", __LINE__, " ", "FUNCTION: ", __FUNCTION__, "INFO: " , __VA_ARGS__);

#define LOG_BUFF_SIZE 1024
 
namespace mpl {

class Logger {
public:
    typedef std::chrono::system_clock::time_point Lg_time;

    static Logger& get_logger(std::string path_to_file); 
    Logger() = delete;
    Logger(const Logger&) = delete;
    Logger& operator = (const Logger&) = delete;
    void set_time_point();
    double show_time();
private:
    void push_log_string() {
        curr_buff_size += log_str_.size();
        log_stack_.push_back(log_str_);
        
        if (curr_buff_size > LOG_BUFF_SIZE) {
            print_log();
            clear_log();
            curr_buff_size = 0;
        } 
        log_str_.clear();
    }
public:
    template<typename T, typename... Args>
    void push_log_string(const T& value, const Args&... args) 
    {
        std::stringstream ss;
        ss << " " << value;
        log_str_ += ss.str();
        push_log_string(args...);
    }
    void print_log();
    void clear_log();    
private:
    Logger(std::string path_to_file);
    ~Logger();
    bool time_point_f_;
    Lg_time log_time_point_;
    std::string log_str_;   
    size_t curr_buff_size;
    std::vector<std::string> log_stack_;
    std::ofstream log_out_;
};
}

#endif
