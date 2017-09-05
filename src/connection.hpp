
#ifndef __CONNECTION_HPP__
#define __CONNECTION_HPP__

#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <array>
#include <boost/system/error_code.hpp>
#include <memory>
#include "make_answer.hpp"
#include "logger.hpp"


using namespace boost::asio;

namespace mpl  {

class Connection : public std::enable_shared_from_this<Connection> {
public:
    using Connect = std::shared_ptr<Connection>;
    static const std::size_t BUFFER_SIZE = 256;

    Connection() = delete;
 
    Connection(io_service&);

    ip::tcp::socket& get_socket();

    static Connect create(boost::asio::io_service&);

    void start();

    void do_receive(const boost::system::error_code&, size_t);

    void do_write(const boost::system::error_code&, size_t bytes_transferred);

private:
    std::array<char, BUFFER_SIZE> input_buffer_;
    std::string output_buffer_;
    ip::tcp::socket socket_;

};
}
#endif
