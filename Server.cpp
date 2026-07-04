#include <boost/asio.hpp>
#include <iostream>
#include <string>

#include "Server.h"
#include "Client.h"

ServerSocket::ServerSocket(boost::asio::io_context& io, boost::asio::ip::tcp::endpoint& endpoint)
	:acceptor_(io, endpoint) {
	do_accept();
}
void ServerSocket::do_accept() {
	acceptor_.async_accept([this](boost::system::error_code ec, boost::asio::ip::tcp::socket client_socket) {
		if (!ec) {
			std::cout << "New Connect client" << std::endl;
			auto session = std::make_shared<ClientSocket>(std::move(client_socket));
			session->start();
		}
		ServerSocket::do_accept();
		});
}