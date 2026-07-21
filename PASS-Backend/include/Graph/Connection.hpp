#pragma once

#include <string>

namespace pass::simulink{
    struct Connection{
        std::string from;
        std::string to;
        int fromPort = 0;
        int toPort   = 0;
    };
}