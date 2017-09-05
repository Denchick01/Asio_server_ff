
#include "logger.hpp"

namespace mpl {

Logger::Logger(std::string path_to_file) 
{
    log_out_.open(path_to_file, std::ios_base::out);
    log_out_.exceptions(log_out_.failbit);
    curr_buff_size = 0;
    set_time_point();       
}

void Logger::set_time_point()
{
    log_time_point_ = std::chrono::system_clock::now();
    time_point_f_ = true;
}

double Logger::show_time()
{
    assert(time_point_f_);
    std::chrono::system_clock::time_point current_time  =  std::chrono::system_clock::now();
    size_t time = std::chrono::duration_cast<std::chrono::seconds>(current_time - log_time_point_).count();
    return time/60.0;
}

void Logger::clear_log()
{
    log_stack_.clear();
}

void Logger::print_log()
{
    for (size_t it = 0; it < log_stack_.size(); it++) {
        log_out_ << log_stack_[it] << std::endl;
    }
}

Logger& Logger::get_logger(std::string path_to_file) 
{
    static Logger logger(path_to_file);
    return logger;
}

Logger::~Logger()
{
    print_log();
    log_out_ << "Statistics:" << std::endl;
    log_out_ << "Time: " << show_time() << " min" << std::endl;
    log_out_ << "Number of iterations: " << log_stack_.size() << std::endl;
    log_out_.close();
}
}
