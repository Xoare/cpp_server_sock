#include "Obfuscation.h"
#include "Client.h"
#include <iostream>

// string -> byte
std::vector<uint8_t> Obffuscation::maskRequest(const std::string& raw_request) {
	std::vector<uint8_t> byte_raw_request;
	uint16_t bite = static_cast<uint8_t>(raw_request.size());
	byte_raw_request.push_back(bite);
	byte_raw_request.insert(byte_raw_request.end(), raw_request.begin(), raw_request.end());
	for (int index = 0; index < byte_raw_request.size(); index++) {
		std::cout << std::hex << static_cast<int>(byte_raw_request[index]) << " ";
	}
	return byte_raw_request;
}

// byte -> string
std::string Obffuscation::unmaskResponse(const std::vector<uint8_t>& masked_data) {
	std::string response;
	for (uint8_t byte : masked_data) {
		response += static_cast<char>(byte);
	}
	return response;
}

// response that the server is alive
std::string Obffuscation::generateDummyResponse() const {
	std::string dummy =
		"HTTP/1.1 200 OK\r\n"
		"Content-Length: 15\r\n"
		"Content-Type: text/html; charset=utf-8\r\n"
		"Connection: close\r\n"
		"\r\n"
		"<html>OK</html>";
	return dummy;
}

std::vector<uint8_t> Obffuscation::addNoise(const std::vector<uint8_t>& data) {


}