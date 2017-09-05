#include <iostream>
#include <boost/asio.hpp>
#include <cstdlib>
#include <boost/system/error_code.hpp>
#include <boost/bind.hpp>
#include <array>
#include "server.hpp"
#include "connection.hpp"
#include <exception>
#include "logger.hpp"

using namespace boost::asio;

int main (int argc, char** argv)
{
try {
    if (argc != 2) {
        std::cerr << "Number of arguments is Invalid\n";
        exit (2);
    }
    else if (std::string(argv[1]).find_first_not_of("1234567890") != 
              std::string::npos) {
        std::cerr << "Argument format is Invalid\n";
        exit(2);
    }

    io_service service;

    unsigned int port_num = atoi(argv[1]);

    mpl::Server server(service, port_num);
        
    service.run();
}
catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
}   
    return 0;    
}
