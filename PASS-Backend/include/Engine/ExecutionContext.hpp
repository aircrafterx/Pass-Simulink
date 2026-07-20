#pragma once

#include "Engine/SignalRouter.hpp"

namespace pass::simulink{
    struct ExecutionContext{
        SignalRouter router;
    };
}