#include "../../include/utils/constants.hpp"

namespace ShareMe
{
    const std::string Constants::messageConcatString = "?<|>?";
    const std::string Constants::apiBaseUrl = "http://localhost:4000/share-me/api";
    const std::string Constants::socketServerUrl = "127.0.0.1";
    const asio::ip::port_type Constants::socketServerPort = 4001;
}