#include "../../include/socket/socket_client.hpp"
#include <iostream>

namespace ShareMe
{
    SocketClient::SocketClient(const std::string& host, asio::ip::port_type port)
        : socket(context)
    {
        endpoint = asio::ip::tcp::endpoint(asio::ip::make_address(host), port);
    }

    bool SocketClient::connect()
    {
        socket.connect(endpoint, ec);
        return !ec;
    }

    bool SocketClient::send(const SocketHeader& message)
    {
        // auto serialized = message.serialize();

        // asio::async_write(socket, asio::buffer(serialized.data(), serialized.size()), 
        //     [&ec = ec](const asio::error_code& error, size_t bytes) {
        //         if (error)
        //             ec = error;
        //     }
        // );

        return !ec;
    }

    void SocketClient::receive()
    {
    }

    void SocketClient::receive_header()
    {
        asio::async_read(socket, asio::buffer(&buffer.header, sizeof(buffer.header)), 
            [&](asio::error_code error, size_t length) {
                if (!error) {
                    receive_body();
                }
            }
        );
    }

    void SocketClient::receive_body()
    {
        asio::async_read(socket, asio::buffer(buffer.body.data(), 10), 
            [&](asio::error_code error, size_t length) {
                if (!error && length == 10) {
                    receive_header();
                }
            }
        );
    }

    asio::error_code SocketClient::error() const
    {
        return ec;
    }
}