#ifndef API_RESULT_HPP
#define API_RESULT_HPP

#include <ostream>

namespace ShareMe
{
    enum class ApiResult
    {
        None = 0,
        Success,
        InvalidCredentials,
        VerificationError,
        ValidationError,
        UserNotActive,
        UserNotFound,
        UserExists,
        InvalidMail,
        ServerError,
        Unreachable,
    };

    std::ostream& operator<<(std::ostream& os, const ApiResult& result);
}

#endif