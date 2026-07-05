#pragma once
#include <string>

class DetectedProtocol {

public:
    explicit DetectedProtocol(std::string line);

    void detected_protocol_request();

private:
    std::string line_;

};
