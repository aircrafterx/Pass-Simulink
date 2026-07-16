#pragma once

namespace pass::simulink{
    class CosineBlock{
        public:
            double process(double time) const;
    };
}