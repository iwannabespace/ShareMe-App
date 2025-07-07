#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
#include <asio.hpp>

namespace ShareMe
{
    class Constants
    {
    public:
        static const std::string messageConcatString;
        static const std::string apiBaseUrl;
        static const std::string socketServerUrl;
        static const asio::ip::port_type socketServerPort;
    };
}

#endif