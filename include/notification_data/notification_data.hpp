#ifndef NOTIFICATION_DATA_HPP
#define NOTIFICATION_DATA_HPP

#include <string>

namespace ShareMe
{
    struct NotificationData
    {
        std::string title;
        std::string message;
        uint16_t duration;
    };
}

#endif