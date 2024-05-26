#ifndef LOGIN_RESULT_HPP
#define LOGIN_RESULT_HPP

#include "api_result.hpp"
#include "api.hpp"
#include <string>

namespace ShareMe
{
    struct LoginResult
    {
        std::string userId;
        ApiResult result;
    };
}

#endif