#pragma once

#include <string>

namespace pass::simulink{
    struct Connection{
        std::string from;
        std::string to;
        int fromPort = 0;   // output port of the source block (0 = first/only output)
        int toPort   = 0;   // input port of the destination block (determines input order)
    };
}