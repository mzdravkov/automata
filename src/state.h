#ifndef AUTOMATA_STATE_H
#define AUTOMATA_STATE_H

#include <ostream>

#include "custom_string.h"

namespace fsm {
    class State {
    private:
        fsm::String name_;
    public:
        State();

        State(const fsm::String& name);

        ~State();

        fsm::String get_name() const;

        void set_name(const fsm::String& name);

        bool operator==(const State &rhs) const;

        bool operator!=(const State &rhs) const;

        friend std::ostream &operator<<(std::ostream &os, const State &state);
    };
}

#endif //AUTOMATA_STATE_H
