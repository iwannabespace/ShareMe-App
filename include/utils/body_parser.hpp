#ifndef BODY_PARSER_HPP
#define BODY_PARSER_HPP

#include <nlohmann/json.hpp>
#include <string>

namespace ShareMe
{
    class BodyParser
    {
    public:
        static nlohmann::json Parse(const std::string& body);
    };
}

#endif