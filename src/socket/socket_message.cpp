#include "../../include/socket/socket_message.hpp"
#include "../../include/utils/constants.hpp"
#include <asio.hpp>
#include <vector>
#include <iostream>

namespace ShareMe
{
    std::string SocketMessage::serialize() const
    {
        /*std::vector<uint8_t> buffer(sizeof(uint32_t) * 2 + header.bodySize);

        uint32_t netType = asio::detail::socket_ops::host_to_network_long(header.type);
        uint32_t netBodySize = asio::detail::socket_ops::host_to_network_long(header.bodySize);
        
        std::memcpy(buffer.data(), &netType, sizeof(netType));
        std::memcpy(buffer.data() + sizeof(netType), &netBodySize, sizeof(netBodySize));
        std::memcpy(buffer.data() + sizeof(netType) + sizeof(netBodySize), body.data(), header.bodySize);

        return std::string(buffer.begin(), buffer.end());*/
        return "";
    }

    SocketMessage SocketMessage::deserialize(const std::string& data)
    {
        /*SocketMessage message;

        uint32_t netType;
        uint32_t netBodySize;
        const char* buffer = data.data();

        std::memcpy(&netType, buffer, sizeof(netType));
        std::memcpy(&netBodySize, buffer + sizeof(netType), sizeof(netBodySize));

        message.header.type = asio::detail::socket_ops::network_to_host_long(netType);
        message.header.bodySize = asio::detail::socket_ops::network_to_host_long(netBodySize);

        message.body.resize(message.header.bodySize);
        std::memcpy(message.body.data(), buffer + sizeof(netType) + sizeof(netBodySize), message.header.bodySize);

        return message;*/

        return SocketMessage();
    }
}