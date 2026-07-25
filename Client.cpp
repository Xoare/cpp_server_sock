#include "Client.h"
#include "DetectedProtocol.h"
#include "Obfuscation.h"

#include <iostream>

std::vector<uint8_t> ClientSocket::TestFunctionStringInDoWrite(const std::string message) {
    Obffuscation obf;
    std::vector<uint8_t> result_message = obf.maskRequest(message);
    return result_message;
}


ClientSocket::ClientSocket(boost::asio::ip::tcp::socket socket)
    : socket_(std::move(socket)) {
}

void ClientSocket::start() {
    std::vector<uint8_t> result_message = TestFunctionStringInDoWrite("HTTP/1.1 200 OK\r\n"
        "Content-Length: 20\r\n"
        "Content-Type: text/html\r\n"
        "\r\n"
        "<html><body><h1>Hello from C++!</h1></body></html>\r\n");
    do_write(std::move(result_message));
    do_read();
}

void ClientSocket::do_write(const std::vector<uint8_t> message_byte) {
    auto self = shared_from_this();
    std::cout << "\n\n\n\n";

    std::vector<uint8_t> byte = std::move(message_byte);

    boost::asio::async_write(socket_,
        boost::asio::buffer(byte),
        [self, byte = std::move(byte)](boost::system::error_code ec, size_t transferred) {
            if (ec) {
                std::cerr << "Write error: " << ec.message() << std::endl;
            }
        });
}

void ClientSocket::do_read() {
    auto self = shared_from_this();

    boost::asio::async_read_until(socket_, read_buffer_, "\r\n\r\n",
        [this, self](boost::system::error_code ec, size_t bytes_transferred) {
            if (ec) {
                std::cout << "Client disconnected: " << ec.message() << std::endl;
                return;
            }

            std::string request_data;
            request_data.resize(bytes_transferred);
            boost::asio::buffer_copy(
                boost::asio::buffer(request_data),
                read_buffer_.data()
            );

            std::cout << "=== HTTP Request (" << bytes_transferred << " bytes) ===" << std::endl;
            std::cout << request_data << std::endl;
            std::cout << "=====================================" << std::endl;

            DetectedProtocol detected(request_data);
            detected.detected_protocol_request();

            read_buffer_.consume(bytes_transferred);

            do_read();
        });
}