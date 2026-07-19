#pragma once

#include <string>
#include <unordered_map>

namespace pass::simulink{
    class SignalRouter{
        private:
            std::unordered_map<std::string, double> signals;

        public:
            void setSignal(const std::string& blockId, double value);
            bool hasSignal(const std::string& blockId) const;
            double getSignal(const std::string& blockId) const;
    };
}