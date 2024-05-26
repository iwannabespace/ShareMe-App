#include "../../include/utils/body_parser.hpp"

namespace ShareMe
{
    nlohmann::json BodyParser::Parse(const std::string& body)
    {
        return nlohmann::json::parse(body);
    }
}