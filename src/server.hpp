#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <boost/asio.hpp>
#include <string>
#include <boost/bind.hpp>
#include "connection.hpp"
#include <boost/system/error_code.hpp>
#include "logger.hpp"

using namespace boost::asio;

namespace mpl {

class Server
{
public:
     Server() = delete;
     Server(const Server&) = delete;
     const Server& operator = (const Server&) = delete;

     Server(boost::asio::io_service&, const unsigned int); 

private:
     void start_accept ();
     
     void handle_accept(Connection::Connect, const boost::system::error_code&);      


     ip::tcp::endpoint ep_;
     ip::tcp::acceptor acceptor_;
     unsigned long long connect_count = 0;
};
}

#endif
     
