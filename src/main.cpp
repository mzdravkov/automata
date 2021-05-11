#include <iostream>

#include "state.h"
#include "fsm.h"

void t1(){
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
    std::cout << "is in final state: " << machine.is_in_final_state() << std::endl;
    machine.transition(0);
    std::cout << "is in final state: " << machine.is_in_final_state() << std::endl;
    machine.transition(1);
    std::cout << "is in final state: " << machine.is_in_final_state() << std::endl;
    std::cout << "Current state: " << machine.get_current_state() << std::endl;
    std::cout << "Restarting" << std::endl;
    machine.restart();
    std::cout << "Current state: " << machine.get_current_state() << std::endl;

    fsm::State s3("s3");
    machine.add_state(s3);
    machine.add_transition_rule(s3, alphabet[0], s1);
    machine.add_transition_rule(s3, alphabet[1], s2);

    machine.set_initial_state(s3);
    machine.transition(1);
    std::cout << "Current state: " << machine.get_current_state() << std::endl;
    std::cout << "is in final state: " << machine.is_in_final_state() << std::endl;
}

void t2(){
    fsm::State s1("s1"), s2("s2"), s3("s3"), s4("s4"), s5("s5");
    std::vector<fsm::State> states1 = {s1, s2, s3};
    std::vector<fsm::State> states2 = {s4, s5};

    std::vector<int> alphabet = {0, 1};

    fsm::State &initial_state1 = s1, &initial_state2 = s4;
    fsm::State &final_state1 = s3, &final_state2 = s5;

    std::vector<fsm::State> final_states1 = {final_state1};
    std::vector<fsm::State> final_states2 = {final_state2};

    std::vector<std::vector<fsm::State>> transition_table1 = {
            {states1[2], states1[1]},
            {states1[2], states1[0]},
            {states1[1], states1[2]},
    };
    std::vector<std::vector<fsm::State>> transition_table2 = {
            {states2[0], states2[1]},
            {states2[1], states2[0]}
    };

    fsm::FSM machine1(states1, alphabet, initial_state1, final_states1, transition_table1);
    fsm::FSM machine2(states2, alphabet, initial_state2, final_states2, transition_table2);

    std::cout << (machine1 & machine2) << std::endl;
}

void t3() {
    fsm::State s1("s1"), s2("s2"), s3("s3"), s4("s4");
    std::vector<fsm::State> states1 = {s1, s2};
    std::vector<fsm::State> states2 = {s3, s4};

    std::vector<int> alphabet = {0, 1, 2};

    fsm::State &initial_state1 = s1, &initial_state2 = s3;
    fsm::State &final_state1 = s2, &final_state2 = s4;

    std::vector<fsm::State> final_states1 = {final_state1};
    std::vector<fsm::State> final_states2 = {final_state2};

    std::vector<std::vector<fsm::State>> transition_table1 = {
            {states1[0], states1[1], states1[1]},
            {states1[0], states1[0], states1[1]}
    };
    std::vector<std::vector<fsm::State>> transition_table2 = {
            {states2[0], states2[0], states2[1]},
            {states2[0], states2[1], states2[0]}
    };

    fsm::FSM machine1(states1, alphabet, initial_state1, final_states1, transition_table1);
    fsm::FSM machine2(states2, alphabet, initial_state2, final_states2, transition_table2);

    std::cout << (machine1 & machine2) << std::endl;
}

void t4(){
    fsm::State s1("s1"), s2("s2"), s3("s3"), s4("s4"), s5("s5"), s6("s6");
    std::vector<fsm::State> states1 = {s1, s2, s3};
    std::vector<fsm::State> states2 = {s4, s5, s6};

    std::vector<int> alphabet = {0, 1};

    fsm::State &initial_state1 = s1, &initial_state2 = s4;
    fsm::State &final_state1 = s3, &final_state2 = s6;

    std::vector<fsm::State> final_states1 = {final_state1};
    std::vector<fsm::State> final_states2 = {final_state2};

    std::vector<std::vector<fsm::State>> transition_table1 = {
            {states1[1], states1[0]},
            {states1[2], states1[0]},
            {states1[2], states1[2]}
    };
    std::vector<std::vector<fsm::State>> transition_table2 = {
            {states2[0], states2[1]},
            {states2[0], states2[2]},
            {states2[2], states2[2]}
    };

    fsm::FSM machine1(states1, alphabet, initial_state1, final_states1, transition_table1);
    fsm::FSM machine2(states2, alphabet, initial_state2, final_states2, transition_table2);

    std::cout << machine1.evaluate("01001") << std::endl;  // Recognises words containing "00".
    std::cout << machine2.evaluate("010011") << std::endl;  // Recognises words containing "11".
    std::cout << !machine2.evaluate("010011") << std::endl;  // Recognises words NOT containing "11".

    // Recognises words containing "00" OR "11".
    std::cout << (machine1 & machine2).evaluate("0101010") << std::endl;
    std::cout << (machine1 & machine2).evaluate("11010") << std::endl;

    // Recognises words containing "00" AND NOT "11".
    std::cout << (machine1 | !machine2).evaluate("100110") << std::endl;
    std::cout << (machine1 | !machine2).evaluate("010010") << std::endl;
}

int main() {

    //t1();
    //t2();
    //t3();
    t4();

    return 0;
}
