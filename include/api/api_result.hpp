#ifndef API_RESULT_HPP
#define API_RESULT_HPP

#include "authorization_data.hpp"
#include <ostream>

namespace ShareMe
{
    enum class ApiResultType
    {
        None,
        Success,
        InvalidCredentials,
        UserVerificationError,
        ValidationError,
        UserNotActive,
        UserNotFound,
        UserExists,
        InvalidMail,
        ServerError,
        Unreachable,
    };

    struct ApiResult
    {
        ApiResultType type;
        std::string message;
    };

    struct LoginResult
    {
        AuthorizationData authData;
        ApiResult result;
    };

    struct GetSaltResult
    {
        std::string salt;
        ApiResult result;
    };

    std::ostream& operator<<(std::ostream& os, const ApiResultType& result);
}

#endif