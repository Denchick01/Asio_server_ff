#include "connection.hpp"



namespace mpl {

    Connection::Connection(io_service& service) 
        : socket_(service)
    {
    }

    ip::tcp::socket& Connection::get_socket()    
    {
        return socket_;
    }
 
    void Connection::start()
    {
        input_buffer_.fill('\0');

        socket_.async_read_some(
            boost::asio::buffer(input_buffer_, BUFFER_SIZE),
            boost::bind(&Connection::do_receive, shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }

    void Connection::do_receive(const boost::system::error_code& error, size_t bytes_transferred)
    {
        if (error == boost::asio::error::eof) {
           std::cout << "diconnect..." << std::endl;
           LOG_INFO("diconnect...")
        }
        else if (!error) {
            if (bytes_transferred < BUFFER_SIZE) {
      
                Make_answer answer;               

                answer.make_answer(output_buffer_);
                
                output_buffer_.clear();
 
                boost::asio::async_write(socket_, boost::asio::buffer(answer.get_answer()),
                boost::bind(&Connection::do_write, shared_from_this(),
                boost::asio::placeholders::error, 
                boost::asio::placeholders::bytes_transferred));
             }
             else {
               output_buffer_ += input_buffer_.data();
               start();
             }
        }
        else {
            std::cerr << "Error number: " << error.value() << " error message: " << error.message() << std::endl;
            LOG_INFO("Error number: ", error.value(), " error message: ", error.message())
        }
     }


     void Connection::do_write(const boost::system::error_code& error, size_t bytes_transferred)
     {
     }

     Connection::Connect Connection::create(boost::asio::io_service& service) {
         return Connect(new Connection(service));
     }
}   
             
     
            

        




