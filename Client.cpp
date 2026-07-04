#include "Client.h"
#include <iostream>

ClientSocket::ClientSocket(boost::asio::ip::tcp::socket socket)
    : socket_(std::move(socket)) {
}

void ClientSocket::start() {
    do_write("Hello!!\n");
    do_read();
}

void ClientSocket::do_write(const std::string& message) {
    auto self = shared_from_this();
    write_buffer_ = message;

    boost::asio::async_write(socket_,
        boost::asio::buffer(write_buffer_),
        [self](boost::system::error_code ec, size_t) {
            if (ec) {
                std::cerr << "Write error: " << ec.message() << std::endl;
            }
        });
}

void ClientSocket::do_read() {
    auto self = shared_from_this();

    boost::asio::async_read_until(socket_, read_buffer_, '\n',
        [this, self](boost::system::error_code ec, size_t bytes_transferred) {
            if (ec) {
                std::cout << "Client disconnected: " << ec.message() << std::endl;
                return;
            }

            std::istream input_stream(&read_buffer_);
            std::string line;
            std::getline(input_stream, line);

            if (!line.empty()) {
                std::cout << "Received: " << line << std::endl;
            }

            read_buffer_.consume(read_buffer_.size());

            do_read();
        });
}