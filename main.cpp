#include "include/app.hpp"
#include "include/socket/socket_message.hpp"
#include <iostream>

int main()
{
    ShareMe::App app;

    return app.run();
}