#ifndef STATE_VALIDATOR_H
#define STATE_VALIDATOR_H

#include <string>
#include <vector>

class StateValidator{
public:
    StateValidator() = default;
    StateValidator(const StateValidator&) = delete;
    StateValidator& operator=(const StateValidator&) = delete;
    ~StateValidator() = default;
    virtual std::string CorrectState(std::vector<std::string> &values) const = 0;
};

#endif