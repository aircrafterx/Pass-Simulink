#include "Engine/SignalRouter.hpp"

namespace pass::simulink{
    void SignalRouter::setSignal(const std::string &blockId, double value){
        signals[blockId] = value;
    }

    bool SignalRouter::hasSignal(const std::string &blockId) const{
        return signals.contains(blockId);
    }

    double SignalRouter::getSignal(const std::string &blockId) const{
        return signals.at(blockId);
    }
}