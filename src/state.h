#ifndef AUTOMATA_STATE_H
#define AUTOMATA_STATE_H

#include <ostream>

#include "custom_string.h"

namespace fsm {
    class State {
    private:
        fsm::String name_;
    public:
        /**
         * Creates an empty State.
         */
        State();

        /**
         * Creates a State with the given name.
         */
        State(const fsm::String& name);

        /**
         * Copy constructor for the State class.
         * Will return a new copy of the provided State.
         * @param State &rhs: state to be copied.
         */
        State(const State& rhs);

        /**
         * A destructor for the State class.
         */
        ~State();

        /**
         * An assignment operator for the State class.
         * Will assign to **this** the value of the given State.
         * @param State &rhs: A state that will be assigned to **this**.
         */
        State& operator=(const State& rhs);

        /**
         * Returns the name of the State.
         */
        fsm::String get_name() const;

        /**
         * Sets the name of the State to the given String.
         * @param String &name: The new name for the State.
         */
        void set_name(const fsm::String& name);

        /**
         * An equality operator for State.
         * Will return true if the given State is the same as **this**.
         * @param State &rhs: A State to compare to **this**.
         */
        bool operator==(const State &rhs) const;

        /**
         * An inequality operator for State.
         * Will return true if the given State is different from **this**.
         * @param State &rhs: A State to compare to **this**.
         */
        bool operator!=(const State &rhs) const;

        /**
         * An addition operator for State.
         * Will return a new State with the concatenated values from **this** and the given State.
         * @param State &rhs: A State that will be concatenated to **this**.
         */
        State operator+(const State &rhs) const;

        /**
         * An insertion operator that will write the State to an output stream.
         * @param ostream &os: An output stream to write to.
         * @param State &state: The State to be written to the output stream.
         */
        friend std::ostream &operator<<(std::ostream &os, const State &state);
    };
}

#endif //AUTOMATA_STATE_H
