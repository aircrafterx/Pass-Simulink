#pragma once

namespace backend{
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