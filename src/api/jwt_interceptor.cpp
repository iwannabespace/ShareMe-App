#include "../../include/api/jwt_interceptor.hpp"
#include "../../include/utils/constants.hpp"

namespace ShareMe
{
    // Fill this in
    cpr::Response JwtInterceptor::intercept(cpr::Session& session)
    {
        const std::string url = Constants::apiBaseUrl + session.GetFullRequestUrl();      

        session.SetUrl(url);
    }
}