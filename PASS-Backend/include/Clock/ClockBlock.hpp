#pragma once

namespace pass::simulink{
    class ClockBlock{
        private:
            double CurrentTime;
            double deltaTime;
        public:
            ClockBlock();
            void tick();
            double getTime() const;
    };
}