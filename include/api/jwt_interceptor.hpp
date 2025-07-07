#ifndef JWT_INTERCEPTOR_HPP
#define JWT_INTERCEPTOR_HPP

#include <cpr/cpr.h>

namespace ShareMe
{
    class JwtInterceptor : public cpr::Interceptor
    {
    public:
        cpr::Response intercept(cpr::Session& session) override;
    };
}

#endif