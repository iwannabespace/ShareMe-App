#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include <string>

namespace ShareMe
{
    class Validator
    {
    public:
        enum class Result
        {
            Success = 0,
            InvalidEmail,
            InvalidUsernameLength,
            InvalidPasswordLength,
            NoUpperInPassword,
            NoNumberInPassword,
            NoPunctInPassword,
        };
    public:
        static Result ValidateEmail(const std::string& email);
        static Result ValidateUsername(const std::string& username);
        static Result ValidatePassword(const std::string& password);
        static std::string GetErrorMessage(Result result);
    };
}

#endif