#ifndef SOCKET_CLIENT_HPP
#define SOCKET_CLIENT_HPP

#include "socket_message.hpp"
#include "../notification_data/notification_data.hpp"
#include <asio.hpp>
#include <deque>

namespace ShareMe
{
    class SocketClient
    {
    public:
        SocketClient(const std::string& host, asio::ip::port_type port);
        bool connect();
        bool send(const SocketHeader& message);
        void receive();
        asio::error_code error() const;
    private:
        void receive_header();
        void receive_body();
    private:
        asio::error_code ec;
        asio::io_context context;
        asio::ip::tcp::endpoint endpoint;
        asio::ip::tcp::socket socket;
        std::deque<SocketMessage> messages;
        std::deque<NotificationData> notifications;
        SocketMessage buffer;
    };
}

#endif