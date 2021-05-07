#include "state.h"

fsm::State::State() {
    this->name_ = "";
}

fsm::State::State(const fsm::String& name) : name_(name) {}

fsm::State::~State() = default;

fsm::String fsm::State::get_name() const {
    return name_;
}

void fsm::State::set_name(const fsm::String& name) {
    this->name_ = name;
}

bool fsm::State::operator==(const fsm::State &rhs) const {
    return name_ == rhs.name_;
}

bool fsm::State::operator!=(const fsm::State &rhs) const {
    return !(rhs == *this);
}

std::ostream &fsm::operator<<(std::ostream &os, const fsm::State &state) {
    os << "State(" << state.name_ << ")";
    return os;
}

fsm::State fsm::State::operator+(const fsm::State &rhs) const{
    return fsm::State(name_ + rhs.name_);
}

