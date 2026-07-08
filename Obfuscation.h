#pragma once

#include <string>
#include <vector>
#include <cstdint>

class Obffuscation {
public:

    std::vector<uint8_t> maskRequest(const std::string& raw_request);

    std::string unmaskResponse(const std::vector<uint8_t>& masked_data);

    std::string generateDummyResponse() const;

    std::vector<uint8_t> addNoise(std::vector<uint8_t>& data);

    std::vector<uint8_t> removeNoise(std::vector<uint8_t>& data);

    std::vector<uint8_t> tlsMask( std::vector<uint8_t>& data);

    std::vector<uint8_t> tlsUnmask(const std::vector<uint8_t>& data);

    std::vector<uint8_t> xorEncrypt( std::vector<uint8_t>& data, uint8_t key);

    void xorDecrypt(std::vector<uint8_t>& data, uint8_t key);

private:

    static constexpr uint8_t XOR_KEY = 0xAA; 

    static constexpr size_t NOISE_INTERVAL = 16; 

    static std::vector<uint8_t> stringToBytes(const std::string& str);

    static std::string bytesToString(const std::vector<uint8_t>& bytes);
};