#ifndef AUTHORIZATION_HPP
#define AUTHORIZATION_HPP

#include <string>

namespace ShareMe
{
    struct AuthorizationData
    {
        std::string accessToken;
        std::string refreshToken;
    };
}

#endif