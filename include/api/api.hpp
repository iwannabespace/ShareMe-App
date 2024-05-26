#ifndef API_HPP
#define API_HPP

#include <string>
#include <future>
#include <nlohmann/json.hpp>
#include "login_result.hpp"
#include "api_result.hpp"

namespace ShareMe
{
    class Api
    {
    public:
        static std::future<LoginResult> Login(const std::string& email, const std::string& password);
        static std::future<ApiResult> Register(const std::string& email, const std::string& username, const std::string& password);
        static std::future<ApiResult> Verify(const std::string& code);
        static ApiResult GetResult(const nlohmann::json& json);
    };
}

#endif