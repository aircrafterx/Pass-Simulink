#pragma once

#include <string>

namespace pass::simulink{
    struct Block{
        std::string id;
        std::string type;

        float x;
        float y;
    };

}