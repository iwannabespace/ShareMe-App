#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>

namespace ShareMe
{
    struct SocketHeader
    {
        uint32_t type;
        uint32_t bodySize;
    };

    struct SocketMessage
    {
        SocketHeader header;
        std::string body;

        std::string serialize() const;
        static SocketMessage deserialize(const std::string& data);
    };
}

#endif