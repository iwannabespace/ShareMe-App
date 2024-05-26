#include "../../include/api/api.hpp"
#include "../../include/utils/constants.hpp"
#include "../../include/utils/body_parser.hpp"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>

namespace ShareMe
{
    std::future<LoginResult> Api::Login(const std::string& email, const std::string& password)
    {  
        return std::async(std::launch::async, [=]() {
            std::string endpoint = Constants::apiBaseUrl + "/login";
            cpr::Url url = cpr::Url{endpoint};
            cpr::Payload parameters = {
                { "email", email },
                { "password", password }
            };

            cpr::Session session;
            session.SetUrl(url);
            session.SetPayload(parameters);

            cpr::Response response = session.Post();

            if (response.status_code == 0) {
                return LoginResult({ "", ApiResult::Unreachable });
            } else {
                auto json = BodyParser::Parse(response.text);
                auto apiResult = Api::GetResult(json);
                std::string userId = json["userId"].get<std::string>();
                return LoginResult({ userId, apiResult });
            }
        });
    }

    std::future<ApiResult> Api::Register(const std::string& email, const std::string& username, const std::string& password)
    {
        return std::async(std::launch::async, [=]() {
            std::string endpoint = Constants::apiBaseUrl + "/register";
            cpr::Url url = cpr::Url{endpoint};
            cpr::Payload parameters = {
                { "email", email },
                { "username", username },
                { "password", password }
            };

            cpr::Session session;
            session.SetUrl(url);
            session.SetPayload(parameters);

            cpr::Response response = session.Post();

            if (response.status_code == 0) {
                return ApiResult::Unreachable;
            } else {
                auto json = BodyParser::Parse(response.text);
                return Api::GetResult(json);
            }
        });
    }

    std::future<ApiResult> Api::Verify(const std::string& code)
    {
        return std::async(std::launch::async, [=]() {
            std::string endpoint = Constants::apiBaseUrl + "/verify";
            cpr::Url url = cpr::Url{endpoint};
            cpr::Payload parameters = {{ "code", code }};

            cpr::Session session;
            session.SetUrl(url);
            session.SetPayload(parameters);

            cpr::Response response = session.Post();

            if (response.status_code == 0) {
                return ApiResult::Unreachable;
            } else {
                auto json = BodyParser::Parse(response.text);
                return Api::GetResult(json);
            }
        });
    }

    ApiResult Api::GetResult(const nlohmann::json& json)
    {
        if (!json.contains("error")) {
            return ApiResult::Success;
        } else {
            const std::string errorString = json["error"].get<std::string>();
            if (errorString == "invalid_credentials") {
                return ApiResult::InvalidCredentials;
            } else if (errorString == "verification_error") {
                return ApiResult::VerificationError;
            } else if (errorString == "user_not_active") {
                return ApiResult::UserNotActive;
            } else if (errorString == "user_not_found") {
                return ApiResult::UserNotFound;
            } else if (errorString == "user_exists") {
                return ApiResult::UserExists;
            } else if (errorString == "validation_error") {
                return ApiResult::ValidationError;
            } else if (errorString == "invalid_mail") {
                return ApiResult::InvalidMail;
            } else if (errorString == "server_error") {
                return ApiResult::ServerError;
            } else {
                return ApiResult::None;
            }
        }
    }
}