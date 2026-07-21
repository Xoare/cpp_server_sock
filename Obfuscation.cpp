#include "Obfuscation.h"
#include "Client.h"

#include <iostream>
#include <random>

// string -> byte
std::vector<uint8_t> Obffuscation::maskRequest(const std::string& raw_request) {
	std::vector<uint8_t> data = stringToBytes(raw_request);
	for (int index = 0; index < data.size(); index++) {
		std::cout << std::hex << static_cast<int>(data[index]) << " ";
	}

	xorEncrypt(data, XOR_KEY);
		
	addNoise(data);

	return tlsMask(data);
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

// noise -> + -> + -> byte
std::vector<uint8_t> Obffuscation::addNoise(std::vector<uint8_t>& data) {
	if (data.empty()) {
		return data;
	}

	size_t index = NOISE_INTERVAL;

	while (index < data.size()) {
		uint8_t noise_byte = static_cast<uint8_t>(rand() % 256);
		data.insert(data.begin() + index, noise_byte);
		index += NOISE_INTERVAL + 1;
	}

	return data;
}

// noise -> - -> - byte
std::vector<uint8_t> Obffuscation::removeNoise(std::vector<uint8_t>& data) {
	int index = 16;
	while (index < data.size()) {
		data.erase(data.begin() + index);
		index += NOISE_INTERVAL + 1;
	}
	return data;
}

// tls + data + noise: {0x17, 0x03, 0x03, sen byte, jun byte data, noise...}
std::vector<uint8_t> Obffuscation::tlsMask(std::vector<uint8_t>& data) {
    std::vector<uint8_t> result;
	std::cout << "hello";
    result.push_back(0x17);
    result.push_back(0x03);
    result.push_back(0x03);
    result.push_back((data.size() >> 8) & 0xFF);
    result.push_back(data.size() & 0xFF);

    result.insert(result.end(), data.begin(), data.end());
	for (int index = 0; index < result.size(); index++) {
		std::cout << std::hex << static_cast<int>(result[index]) << " ";
	}

    return result;
}

// data - tls
std::vector<uint8_t> Obffuscation::tlsUnmask(const std::vector<uint8_t>& data) {
	if (data.size() < 5) {
		return data;
	}

	std::vector<uint8_t> result(data.begin() + 5, data.end());
	return result;

}

// byte = byte xor key
std::vector<uint8_t> Obffuscation::xorEncrypt(std::vector<uint8_t>& data, uint8_t key) {
	for (int index = 0; index < data.size(); index++) {
		data[index] ^= key;
	}
	return data;
}

//byte xor key = byte
void Obffuscation::xorDecrypt(std::vector<uint8_t>& data, uint8_t key) {
	xorEncrypt(data, key);
}


std::vector<uint8_t> Obffuscation::stringToBytes(const std::string& data) {
	std::vector<uint8_t> byte_raw_request;
	uint16_t bite = static_cast<uint16_t>(data.size());
	byte_raw_request.push_back(bite);
	byte_raw_request.insert(byte_raw_request.end(), data.begin(), data.end());

	return byte_raw_request;
}