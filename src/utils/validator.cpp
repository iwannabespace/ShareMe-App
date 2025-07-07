#include "../../include/utils/validator.hpp"
#include <regex>
#include <algorithm>

namespace ShareMe
{
    Validator::Result Validator::ValidateEmail(const std::string& email)
    {
        const std::regex emailRegex
            = std::regex(
                "[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?", 
                std::regex_constants::icase);

        return std::regex_match(email, emailRegex) ? 
            Result::Success : 
            Result::InvalidEmail;
    }

    Validator::Result Validator::ValidateUsername(const std::string& username)
    {
        return (username.length() >= 4 && username.length() <= 16) ?
            Result::Success : 
            Result::InvalidUsernameLength;
    }

    Validator::Result Validator::ValidatePassword(const std::string& password)
    {
        bool lengthCheck = password.length() >= 8 && password.length() <= 24;
        bool hasNumber = std::any_of(password.begin(), password.end(), ::isdigit);
        bool hasUpper = std::any_of(password.begin(), password.end(), ::isupper);
        bool hasPunct = std::any_of(password.begin(), password.end(), ::ispunct);

        if (!lengthCheck) { return Result::InvalidPasswordLength; }
        if (!hasNumber)   { return Result::NoNumberInPassword; }
        if (!hasUpper)    { return Result::NoUpperInPassword; }
        if (!hasPunct)    { return Result::NoPunctInPassword; }

        return Result::Success;
    }

    std::string Validator::GetErrorMessage(Result result)
    {
        switch (result)
        {
        case Result::InvalidEmail:
            return "Invalid email";
        case Result::InvalidUsernameLength:
            return "Username must be between 4 and 16 characters";
        case Result::InvalidPasswordLength:
            return "Password must be between 8 and 24 characters";
        case Result::NoUpperInPassword:
            return "Password must contain at least one uppercase letter";
        case Result::NoNumberInPassword:
            return "Password must contain at least one number";
        case Result::NoPunctInPassword:
            return "Password must contain at least one punctuation character";
        default:
            return "No Error";
        }
    }
}