#include <iostream>

#include "state.h"
#include "fsm.h"

int main() {
    fsm::State s1("s1"), s2("s2");
    std::vector<fsm::State> states = {s1, s2};
    std::vector<int> alphabet = {0, 1};
    fsm::State &final_state = s2;
    std::vector<fsm::State> final_states = {final_state};
    fsm::State &initial_state = s1;
    std::vector<std::vector<fsm::State>> transition_table = {
            {states[0], states[1]},
            {states[1], states[1]},
    };
    fsm::FSM machine(states, alphabet, initial_state, final_states, transition_table);
    std::cout << "is in final state: " << machine.is_in_final_state() << "\n";
    machine.transition(0);
    std::cout << "is in final state: " << machine.is_in_final_state() << "\n";
    machine.transition(1);
    std::cout << "is in final state: " << machine.is_in_final_state() << "\n";
    std::cout << "Current state: " << machine.get_current_state() << "\n";
    std::cout << "Restarting" << "\n";
    machine.restart();
    std::cout << "Current state: " << machine.get_current_state() << "\n";

    fsm::State s3("s3");
    machine.add_state(s3);
    machine.add_transition_rule(s3, alphabet[0], s1);
    machine.add_transition_rule(s3, alphabet[1], s2);

    machine.set_initial_state(s3);
    machine.transition(1);
    std::cout << "Current state: " << machine.get_current_state() << "\n";
    std::cout << "is in final state: " << machine.is_in_final_state() << "\n";

    return 0;
}
