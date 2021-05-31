#ifndef AUTOMATA_FSM_H
#define AUTOMATA_FSM_H

#include <iostream>
#include <vector>

#include "state.h"

namespace fsm {
    template <typename T>
    class FSM {
    private:
        std::vector<fsm::State> states_;
        std::vector<T> alphabet_;
        fsm::State initial_state_;
        std::vector<fsm::State> final_states_;
        std::vector<std::vector<fsm::State>> transition_table_;
        fsm::State *current_state_;
    public:
        FSM();

        FSM(const std::vector<fsm::State> &states, const std::vector<T> &alphabet,
            const State &initialState, const std::vector<fsm::State> &finalStates,
            const std::vector<std::vector<fsm::State>> &transitionTable);

        // Construct machine from .txt file.
        //FSM(const fsm::String& destPath);
        FSM(const char* destPath);

        FSM(const fsm::FSM<T>& rhs);

        ~FSM();

        fsm::FSM<T>& operator=(const fsm::FSM<T>& rhs);

        int get_states_count() const;

        const std::vector<fsm::State> &get_states() const;

        void set_states(const std::vector<fsm::State> &states);

        int get_alphabet_count() const;

        const std::vector<T> &get_alphabet() const;

        void set_alphabet(const std::vector<T> &alphabet);

        const State &get_initial_state() const;

        void set_initial_state(const State &initial_state);

        int get_final_states_count() const;

        const std::vector<fsm::State> &get_final_states() const;

        void set_final_states(const std::vector<fsm::State> &final_states);

        const std::vector<std::vector<fsm::State>> &get_transition_table() const;

        void set_transition_table(const std::vector<std::vector<fsm::State>> &transition_table);

        State get_current_state() const;

        // Adds a new state to the machine.
        // Note: it automatically grows the transition table by adding a new row at the end.
        void add_state(const State& state);

        // Adds a new final state.
        void add_final_state(const State& state);

        // Adds a new symbol to the machine's alphabet.
        // Note: it automatically grows the transition table by adding a new column at the end.
        void add_symbol(T symbol);

        // Sets a value at a specific cell in the transition table.
        // current_state: row in the transition table.
        // symbol: column in the transition table.
        // next_state: the state that will be set in the cell defined by other two parameters.
        void add_transition_rule(const State& current_state, T symbol, const State& next_state);

        // Takes an input and transitions the state of the machine
        // to the next state according to the to the transition table.
        void transition(T input);

        // Returns true if the current state is a final state.
        bool is_in_final_state() const;

        // Returns true if the word is recognised by the machine.
        bool evaluate(const char* word);

        // Returns the compliment machine.
        fsm::FSM<T> operator!() const;

        // Returns a machine which is the intersection of the operands.
        fsm::FSM<T> operator&(const fsm::FSM<T> &rhs) const;

        // Returns a machine which is the union of the operands.
        fsm::FSM<T> operator|(const fsm::FSM<T> &rhs) const;

        std::ostream& ins(std::ostream &out) const;
        std::ostream& fins(std::ostream& out) const;

        std::istream& ext(std::istream& in);

        // Build machine from .txt file.
        fsm::FSM<T> fromTXT(const char* sourcePath);

        void toTXT(const char* dest) const;

        // Returns the machine back to the initial state.
        void restart();
    private:

        unsigned indexOfState(const fsm::State& st) const;

        // Validates that there are no duplicated states.
        void validate_states() const;

        // Validates that the initial state is one of the machine's states.
        void validate_initial_state() const;

        // Validates that all final states are valid states in this machine.
        void validate_final_states() const;
    };

    template <typename T>
    std::ostream& operator<<(std::ostream &out, const fsm::FSM<T> &rhs);

    template <typename T>
    std::istream& operator>>(std::istream& in, fsm::FSM<T>& rhs);

    template <typename T>
    void fill(fsm::FSM<T> m1, fsm::FSM<T> m2, fsm::FSM<T> &m3, fsm::State prevState = State());
}

#endif //AUTOMATA_FSM_H
