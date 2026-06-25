#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")

std::string get_wsa_error_message() {
    char buffer[256];
    FormatMessageA(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        WSAGetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        buffer,
        sizeof(buffer),
        nullptr
    );
    return std::string(buffer);
}
// Без обработки ошибок подключения
int main()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);


    SOCKET server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in server_addr {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);


    if (bind(server_fd, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed: " << get_wsa_error_message() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    if (listen(server_fd, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed: " << get_wsa_error_message() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }


    std::cout << "server start on port 8080" << std::endl;

    while (true) {
        struct sockaddr_in client_addr{};
        int client_len = sizeof(client_addr);

        SOCKET conn = accept(server_fd, reinterpret_cast<sockaddr*>(&client_addr), &client_len);

        if (conn == INVALID_SOCKET) {
            std::cerr << "Accept failed: " << get_wsa_error_message() << std::endl;
            continue; 
        }
        while (true) {
            char bufer[1024];
            std::cout << "Me: ";
            std::cin.getline(bufer, sizeof(bufer));
            int len = static_cast<int>(strlen(bufer));

            std::string fullText;

            int byte_send = send(conn, bufer, len, 0);
            int byte_recv = recv(conn, bufer, sizeof(bufer), 0);

            std::string text(bufer, byte_recv);
            fullText.append(bufer, byte_recv);

            std::cout << "You: " << fullText << std::endl;
        }
        

//      std::cout << "client accept!!!!";




    }
    closesocket(server_fd);
    WSACleanup();
    return 0;
}
