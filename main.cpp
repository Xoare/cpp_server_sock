#include <boost/asio.hpp>
#include <iostream>
#include <string>

#include "Server.h"


int main() {
    std::cout << "Boost Version: " << BOOST_VERSION << std::endl;

    boost::asio::io_context io;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address_v4("192.168.1.55"), 8080);
    
    ServerSocket server(io, endpoint);

    std::cout << "🚀 Server started on 192.168.1.55:8080" << std::endl;

    io.run();

    std::cout << "Boost.Asio is working!" << std::endl;
    return 0;
}