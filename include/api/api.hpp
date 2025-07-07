#ifndef API_HPP
#define API_HPP

#include <string>
#include <future>
#include <nlohmann/json.hpp>
#include "api_result.hpp"
#include "../widgets/messenger.hpp"

namespace ShareMe
{
    class Api
    {
    public:
        static std::future<LoginResult> Login(const std::string& email, const std::string& sha256);
        static std::future<ApiResult> Register(const std::string& email, const std::string& username, const std::string& sha256, const std::string& salt);
        static std::future<ApiResult> Verify(const std::string& code);
        static std::future<GetSaltResult> GetSalt(const std::string& email);
        static ApiResult GetResult(const nlohmann::json& json);
    };

    class ApiResultHandler
    {
    public:
        struct MessageParams
        {
            std::string invalidCredentialsMessage = "Invalid credentials!";
            std::string userVerificationErrorMessage = "User verification error!";
            std::string validationErrorMessage = "Validation error!";
            std::string userNotActiveMessage = "User not active!";
            std::string userNotFoundMessage = "User not found!";
            std::string userExistsMessage = "User exists!";
            std::string invalidMailMessage = "Invalid mail!";
            std::string serverErrorMessage = "Server error!";
        };
    public:
        static void Handle(ApiResult result, Messenger& messenger, MessageParams& params, const std::function<void()>& onSuccess, const std::function<void()>& onFailure = []() {});
    };
}

#endif