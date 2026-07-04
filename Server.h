#pragma once

#include <iostream>
#include <boost/asio.hpp>

class ServerSocket {
public:
	ServerSocket(boost::asio::io_context& io, boost::asio::ip::tcp::endpoint& endpoint);
private:
	void do_accept();

	boost::asio::ip::tcp::acceptor acceptor_;
};