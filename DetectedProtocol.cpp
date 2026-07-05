#include "DetectedProtocol.h"
#include <iostream>
#include <boost/beast/http.hpp>


DetectedProtocol::DetectedProtocol(std::string line)
    : line_(std::move(line)) {
}

void DetectedProtocol::detected_protocol_request() {
    boost::beast::http::request_parser<boost::beast::http::string_body> parser;

    boost::system::error_code ec;
    parser.put(boost::asio::buffer(line_), ec);

    if (ec == boost::beast::http::error::need_more) {
        std::cout << "Insufficient data" << std::endl;
        return;
    }
    if (ec) {
        std::cout << "Error parser: " << ec.message() << std::endl;
        return;
    }

    auto& req = parser.get();

    std::cout << "Method: " << req.method_string() << std::endl;
    std::cout << "Target: " << req.target() << std::endl;

    std::string host;
    auto it = req.find("Host");
    if (it != req.end()) {
        auto const& value = it->value();
        host = std::string(value.data(), value.size());
        std::cout << "Domain: " << host << std::endl;
    }
    else {
        std::cout << "Domain: not specified" << std::endl;
    }
}