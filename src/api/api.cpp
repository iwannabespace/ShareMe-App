#include "../../include/api/api.hpp"
#include "../../include/utils/constants.hpp"
#include "../../include/utils/body_parser.hpp"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>

namespace ShareMe
{
    std::future<LoginResult> Api::Login(const std::string& email, const std::string& sha256)
    {  
        return std::async(std::launch::async, [=]() {
            std::string endpoint = Constants::apiBaseUrl + "/login";
            cpr::Url url(endpoint);
            cpr::Payload parameters = {
                { "email", email },
                { "sha256", sha256 }
            };

            cpr::Session session;
            session.SetUrl(url);
            session.SetPayload(parameters);

            cpr::Response response = session.Post();

            // Unreachable durumunu da GetResult fonksiyonunda kontrol etmeyi bir düşün
            if (response.status_code == 0) {
                return LoginResult({ {}, { ApiResultType::Unreachable, "Remote server is unreachable" } });
            } else {
                auto json = BodyParser::Parse(response.text);
                auto apiResult = Api::GetResult(json);

                if (apiResult.type == ApiResultType::Success) {
                    std::string accessToken = json["accessToken"].get<std::string>();
                    std::string refreshToken = json["refreshToken"].get<std::string>();
                    return LoginResult({ { accessToken, refreshToken }, apiResult });
                } else {
                    return LoginResult({ {}, apiResult });
                }
            }
        });
    }

    std::future<ApiResult> Api::Register(const std::string& email, const std::string& username, const std::string& sha256, const std::string& salt)
    {
        return std::async(std::launch::async, [=]() {
            std::string endpoint = Constants::apiBaseUrl + "/register";
            cpr::Url url(endpoint);
            cpr::Payload parameters = {
                { "email", email },
                { "username", username },
                { "sha256", sha256 },
                { "salt", salt }
            };

            cpr::Session session;
            session.SetUrl(url);
            session.SetPayload(parameters);

            cpr::Response response = session.Post();

            if (response.status_code == 0) {
                return ApiResult({ ApiResultType::Unreachable, "Remote server is unreachable" });
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
            cpr::Url url(endpoint);
            cpr::Payload parameters = {{ "code", code }};

            cpr::Session session;
            session.SetUrl(url);
            session.SetPayload(parameters);

            cpr::Response response = session.Post();

            if (response.status_code == 0) {
                return ApiResult({ ApiResultType::Unreachable, "Remote server is unreachable" });
            } else {
                auto json = BodyParser::Parse(response.text);
                return Api::GetResult(json);
            }
        });
    }

    std::future<GetSaltResult> Api::GetSalt(const std::string& email)
    {  
        return std::async(std::launch::async, [=]() {
            std::string endpoint = Constants::apiBaseUrl + "/get-salt";
            cpr::Url url(endpoint);
            cpr::Payload parameters = {
                { "email", email },
            };

            cpr::Session session;
            session.SetUrl(url);
            session.SetPayload(parameters);

            cpr::Response response = session.Post();

            if (response.status_code == 0) {
                return GetSaltResult({ "", { ApiResultType::Unreachable, "Remote server is unreachable" } });
            } else {
                auto json = BodyParser::Parse(response.text);
                auto apiResult = Api::GetResult(json);

                if (apiResult.type == ApiResultType::Success) {
                    const std::string salt = json["salt"].get<std::string>();
                    return GetSaltResult({ salt, apiResult });
                } else {
                    return GetSaltResult({ "", apiResult });
                }
            }
        });
    }

    ApiResult Api::GetResult(const nlohmann::json& json)
    {   
        const std::string message = json["message"].get<std::string>();

        if (!json.contains("error")) {
            return { ApiResultType::Success, message };
        } else {
            const std::string error = json["error"].get<std::string>();
            if (error == "invalid_credentials") {
                return { ApiResultType::InvalidCredentials, message };
            } else if (error == "user_verification_error") {
                return { ApiResultType::UserVerificationError, message };
            } else if (error == "user_not_active") {
                return { ApiResultType::UserNotActive, message };
            } else if (error == "user_not_found") {
                return { ApiResultType::UserNotFound, message };
            } else if (error == "user_exists") {
                return { ApiResultType::UserExists, message };
            } else if (error == "validation_error") {
                return { ApiResultType::ValidationError, message };
            } else if (error == "invalid_mail") {
                return { ApiResultType::InvalidMail, message };
            } else if (error == "server_error") {
                return { ApiResultType::ServerError, message };
            } else {
                return { ApiResultType::None, message };
            }
        }
    }

    void ApiResultHandler::Handle(ApiResult result, Messenger& messenger, MessageParams& params, const std::function<void()>& onSuccess, const std::function<void()>& onFailure)
    {
        if (result.type == ApiResultType::Success) {
            onSuccess();
        } else {
            onFailure();
            if (result.type == ApiResultType::InvalidCredentials) {
                messenger.addMessage(params.invalidCredentialsMessage);
            } else if (result.type == ApiResultType::UserVerificationError) {
                messenger.addMessage(params.userVerificationErrorMessage);
            } else if (result.type == ApiResultType::ValidationError) {
                messenger.addMessage(params.validationErrorMessage);
            } else if (result.type == ApiResultType::UserNotActive) {
                messenger.addMessage(params.userNotActiveMessage);
            } else if (result.type == ApiResultType::UserNotFound) {
                messenger.addMessage(params.userNotFoundMessage);
            } else if (result.type == ApiResultType::UserExists) {
                messenger.addMessage(params.userExistsMessage);
            } else if (result.type == ApiResultType::InvalidMail) {
                messenger.addMessage(params.invalidMailMessage);
            } else if (result.type == ApiResultType::ServerError) {
                messenger.addMessage(params.serverErrorMessage);
            }
        }
    }
}