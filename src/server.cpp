#include "server.hpp"


namespace mpl {


    Server::Server(boost::asio::io_service& service, const unsigned int port_num) 
        : ep_(ip::tcp::v4(), port_num),
          acceptor_ (service, ep_)
    {
        std::cout << "Server ip: <" 
                  << ep_.address().to_string()
                  << ">\nport: <" 
                  << ep_.port()
                  <<  ">\n" 
                  << "host: <"
                  << ip::host_name()
                  << ">"
                  << std::endl;

        LOG_INFO("Server ip: <", ep_.address().to_string(), ">\nport: <", ep_.port(),  ">\n", "host: <", ip::host_name(), ">")
        start_accept();
    }
   

    void Server::start_accept ()
    {
        std::cout << "Connect is accepting..." << std::endl;
        LOG_INFO("Connect is accepting...") 
 
        Connection::Connect new_connection = Connection::create (acceptor_.get_io_service());
        acceptor_.async_accept(new_connection->get_socket(), 
            boost::bind(&Server::handle_accept, this, new_connection,
               boost::asio::placeholders::error)); 
        
    }

    void Server::handle_accept(Connection::Connect new_connection, const boost::system::error_code& error)
    {
        if (!error) {
            	++connect_count;
                std::cout << "New connect, number: " << connect_count << std::endl;
                LOG_INFO("New connect, number: ")
                new_connection->start();
        }
        
        start_accept();
    }
    
}
