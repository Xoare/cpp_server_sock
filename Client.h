#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <string>

class ClientSocket : public std::enable_shared_from_this<ClientSocket> {
public:
    explicit ClientSocket(boost::asio::ip::tcp::socket socket);
    std::vector<uint8_t> TestFunctionStringInDoWrite(const std::string message);
    void start();

private:
    void do_read();
    void do_write(const std::vector<uint8_t> message_byte);

    boost::asio::ip::tcp::socket socket_;
    boost::asio::streambuf read_buffer_;
    std::string write_buffer_;
};