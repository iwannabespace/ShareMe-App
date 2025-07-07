#include "../../include/api/api_result.hpp"

namespace ShareMe
{
    std::ostream& operator<<(std::ostream& os, const ApiResultType& result)
    {
        switch (result) {
            case ApiResultType::None: os << "None"; break;
            case ApiResultType::Success: os << "Success"; break;
            case ApiResultType::InvalidCredentials: os << "InvalidCredentials"; break;
            case ApiResultType::UserVerificationError: os << "UserVerificationError"; break;
            case ApiResultType::ValidationError: os << "ValidationError"; break;
            case ApiResultType::UserNotActive: os << "UserNotActive"; break;
            case ApiResultType::UserNotFound: os << "UserNotFound"; break;
            case ApiResultType::UserExists: os << "UsersExists"; break;
            case ApiResultType::InvalidMail: os << "InvalidMail"; break;
            case ApiResultType::ServerError: os << "ServerError"; break;
            case ApiResultType::Unreachable : os << "Unreachable"; break;
        }
        return os;
    }
}