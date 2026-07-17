#pragma once

#include <vector>

namespace pass::simulink{
    struct ScopeSample{
        double time;
        double sine;
        double cosine;
    };

    class ScopeBlock{
        private:
            std::vector<ScopeSample> samples;
        public:
            void addSample(double time, double sine, double cosine);
            const std::vector<ScopeSample>& getSamples() const;
    };
}