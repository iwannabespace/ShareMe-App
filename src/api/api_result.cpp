#include "../../include/api/api_result.hpp"

namespace ShareMe
{
    std::ostream& operator<<(std::ostream& os, const ApiResult& result)
    {
        switch (result) {
            case ApiResult::None: os << "None"; break;
            case ApiResult::Success: os << "Success"; break;
            case ApiResult::InvalidCredentials: os << "InvalidCredentials"; break;
            case ApiResult::VerificationError: os << "VerificationError"; break;
            case ApiResult::ValidationError: os << "ValidationError"; break;
            case ApiResult::UserNotActive: os << "UserNotActive"; break;
            case ApiResult::UserNotFound: os << "UserNotFound"; break;
            case ApiResult::UserExists: os << "UsersExists"; break;
            case ApiResult::InvalidMail: os << "InvalidMail"; break;
            case ApiResult::ServerError: os << "ServerError"; break;
            case ApiResult::Unreachable : os << "Unreachable"; break;
        }
        return os;
    }
}