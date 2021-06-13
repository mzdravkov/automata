#ifndef AUTOMATA_FSM_H
#define AUTOMATA_FSM_H

#include <iostream>
#include <vector>

#include "state.h"

namespace fsm {
    /**
     * FSM is a class that implments a finite state machine.
     * An FSM instance can be in an exactly one state at a time
     * from a finite number of possible states.
     * Changes from state to state happen by reading an input
     * symbol from the alphabet of the FSM and follow the transiton
     * rules defined by the transition_table of the FSM.
     */
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
        /**
         * No arguments constructor for the FSM.
         */
        FSM();

        /**
         * All-arguments constructor for the FSM.
         * @param vector<State> &states: Defines the possible states for the FSM.
         * @param vector<T> &alphabet: Defines the alphabet (input symbols) that the FSM can operate with.
         * @param State &initialState: The State at which the FSM will be set upon creation.
         * @param vector<State> finalStates: States which are acceptable final states for the FSM.
         * @param vector<vector<State>> &transitionTable: The rules that the FSM will follow to move from state to state. Each row represents possbile next states for a given **current state**. Each column represents possible next states for a given **input symbol**.
         */
        FSM(const std::vector<fsm::State> &states, const std::vector<T> &alphabet,
            const State &initialState, const std::vector<fsm::State> &finalStates,
            const std::vector<std::vector<fsm::State>> &transitionTable);

        /**
         * Constructs an FSM from a text file.
         * @param char *destPath: The path to a file with an FSM definition.
         */
        FSM(const char* destPath);

        /**
         * A copy constructor for FSM. Will use the provided FSM to create a new FSM.
         * @param FSM<T> &rhs: An FSM to be copied.
         */
        FSM(const fsm::FSM<T>& rhs);

        /**
         * A destructor for the FSM.
         */
        ~FSM();

        /**
         * An assignment operator for FSM.
         * Sets all parameters of the FSM on the left side to equal those of the FSM on the right side.
         * @param FSM<T> &rhs: An FSM that we wish ot assign to the one on the left side of the operator.
         */
        fsm::FSM<T>& operator=(const fsm::FSM<T>& rhs);

        /**
         * Returns the number of states for the FSM.
         */
        int get_states_count() const;

        /**
         * Returns a vector with all states for the FSM.
         */
        const std::vector<fsm::State> &get_states() const;

        /**
         * Sets the states of the FSM to those in the provided vector.
         * @param vector<State> &states: States that will be set as the FSM's states.
         */
        void set_states(const std::vector<fsm::State> &states);

        /**
         * Returns the number of symbols in the FSM's alphabet.
         */
        int get_alphabet_count() const;

        /**
         * Returns a vector with all symbols in the FSM's alphabet.
         */
        const std::vector<T> &get_alphabet() const;

        /**
         * Sets the alphabet of the FSM to those in the provided vector.
         * @param vector<T> &alhpbet: A vector with symbols that will be set as the FSM's alphabet.
         */
        void set_alphabet(const std::vector<T> &alphabet);

        /**
         * Returns the initial State for the FSM.
         */
        const State &get_initial_state() const;

        /**
         * Sets a new initial state for the FSM.
         * @param State &initial_state: A State that will serve as the FSM's initial state.
         */
        void set_initial_state(const State &initial_state);

        /**
         * Returns the number of final states for the FSM.
         */
        int get_final_states_count() const;

        /**
         * Returns a vector with all final states for the FSM.
         */
        const std::vector<fsm::State> &get_final_states() const;

        /**
         * Sets a new set of valid final states for the FSM.
         * @param vector<State> &final_states: A vector with states that will be set as the new set of final states for the FSM.
         */
        void set_final_states(const std::vector<fsm::State> &final_states);

        /**
         * Returns the transition table for the FSM.
         */
        const std::vector<std::vector<fsm::State>> &get_transition_table() const;

        /**
         * Sets a new transition table for the FSM.
         * @param vector<vector>State>> &transition_table: A new transition table that will be assigned to the FSM.
         */
        void set_transition_table(const std::vector<std::vector<fsm::State>> &transition_table);

        /**
         * Returns the current state of the FSM.
         */
        State get_current_state() const;

        /**
         * Adds a new state to the machine.
         * Note: it automatically grows the transition table by adding a new row at the end.
         * @param State &state: A new state that will be added to the set of possible states of the FSM.
         */
        void add_state(const State& state);

        /**
         * Adds a new final state to the FSM.
         * @param State &state: A state that will be added to the set of valid final states for the FSM.
         */
        void add_final_state(const State& state);

        /**
         * Adds a new symbol to the machine's alphabet.
         * Note: it automatically grows the transition table by adding a new column at the end.
         * @param T symbol: A symbol to be added to the FSM's alphabet.
         */
        void add_symbol(T symbol);

        /**
         * Sets a value at a specific cell in the transition table.
         * @param State &current_state: Row in the transition table.
         * @param T symbol: Column in the transition table.
         * @param State &next_state: The state that will be set in the cell defined by other two parameters.
         */
        void add_transition_rule(const State& current_state, T symbol, const State& next_state);

        /**
         * Takes an input and transitions the state of the machine
         * to the next state according to the to the transition table.
         * @param T input: A symbol from the FSM's alphabet.
         */
        void transition(T input);

        /**
         * Returns true if the current state is a final state.
         */
        bool is_in_final_state() const;

        /**
         * Returns true if the word is recognised by the machine.
         */
        bool evaluate(const char* word);

        /**
         * Returns the compliment machine.
         */
        fsm::FSM<T> operator!() const;

        /**
         * Returns a machine which is the intersection of the operands.
         * @param FSM<T> &rhs: Another FSM that will be intersected with **this**.
         */
        fsm::FSM<T> operator&(const fsm::FSM<T> &rhs) const;

        /**
         * Returns a machine which is the union of the operands.
         * @param FSM<T> &rhs: Another FSM that will be unified with **this**.
         */
        fsm::FSM<T> operator|(const fsm::FSM<T> &rhs) const;

        /**
         * Writes the FSM's transition table to an output stream.
         * @param ostream &out: An output stream to write to.
         */
        std::ostream& ins(std::ostream &out) const;

        /**
         * Writes the FSM's information to an output stream.
         * @param ostream &out: An output stream to write to.
         */
        std::ostream& fins(std::ostream& out) const;

        /**
         * Creates a CLI interface in which the user can provide
         * the parameters of the FSM.
         * @param istream &in: An input stream from which the information will be read.
         */
        std::istream& ext(std::istream& in);

        /**
         * Builds an FSM from a text file.
         * @param char *sourcePath: The path to a file that contains the definition of an FSM.
         */
        fsm::FSM<T> fromTXT(const char* sourcePath);

        /**
         * Exports the information of the FSM to a file.
         * @param char *dest: The path to a file to which the FSM will be exported.
         */
        void toTXT(const char* dest) const;

        /**
         * Returns the machine back to the initial state.
         */
        void restart();
    private:

        /**
         * Returns the index at which a given state resides.
         * @param State &st: The state for which the FSM is queried.
         */
        unsigned indexOfState(const fsm::State& st) const;

        /**
         * Validates that there are no duplicated states.
         */
        void validate_states() const;

        /**
         * Validates that the initial state is one of the machine's states.
         */
        void validate_initial_state() const;

        /**
         * Validates that all final states are valid states in this machine.
         */
        void validate_final_states() const;
    };

    /**
     * An insertion operator for writting an FSM to an output stream.
     * @param ostream &out: An output stream to write to.
     * @param FSM<T> &rhs: An FSM that will be written to the output stream.
     */
    template <typename T>
    std::ostream& operator<<(std::ostream &out, const fsm::FSM<T> &rhs);

    /**
     * An extraction operator for reading the definition of an FSM from an input stream.
     * @param istream &in: An input stream to read from.
     * @param FS<T> &rhs: An FSM to which the information will be written.
     */
    template <typename T>
    std::istream& operator>>(std::istream& in, fsm::FSM<T>& rhs);

    template <typename T>
    void fill(fsm::FSM<T> m1, fsm::FSM<T> m2, fsm::FSM<T> &m3, fsm::State prevState = State());
}

#endif //AUTOMATA_FSM_H
