#include <set>
#include <algorithm>

#include "fsm.h"
#include "automation_exception.h"

fsm::FSM::FSM(const std::vector<fsm::State> &states, const std::vector<int> &alphabet, const fsm::State &initial_state,
              const std::vector<fsm::State> &final_states, const std::vector<std::vector<fsm::State>> &transition_table)
        : states_(states),  alphabet_(alphabet), initial_state_(initial_state),
          final_states_(final_states), transition_table_(transition_table) {
    current_state_ = &initial_state_;
    validate_states();
    validate_initial_state();
    validate_final_states();
}

fsm::FSM::~FSM() = default;
//    delete [] current_state_;
//};

int fsm::FSM::get_states_count() const {
    return states_.size();
}

const std::vector<fsm::State> &fsm::FSM::get_states() const {
    return states_;
}

void fsm::FSM::set_states(const std::vector<fsm::State> &states) {
    states_ = states;
}

int fsm::FSM::get_alphabet_count() const {
    return alphabet_.size();
}

const std::vector<int> &fsm::FSM::get_alphabet() const {
    return alphabet_;
}

void fsm::FSM::set_alphabet(const std::vector<int> &alphabet) {
    alphabet_ = alphabet;
}

const fsm::State &fsm::FSM::get_initial_state() const {
    return initial_state_;
}

void fsm::FSM::set_initial_state(const fsm::State &initialState) {
    initial_state_ = initialState;
}

int fsm::FSM::get_final_states_count() const {
    return final_states_.size();
}

const std::vector<fsm::State> &fsm::FSM::get_final_states() const {
    return final_states_;
}

void fsm::FSM::set_final_states(const std::vector<fsm::State> &final_states) {
    final_states_ = final_states;
}

const std::vector<std::vector<fsm::State>> &fsm::FSM::get_transition_table() const {
    return transition_table_;
}

void fsm::FSM::set_transition_table(const std::vector<std::vector<fsm::State>> &transition_table) {
    transition_table_ = transition_table;
}

fsm::State fsm::FSM::get_current_state() const {
    return *current_state_;
}

void fsm::FSM::add_state(const fsm::State &state) {
    states_.push_back(state);
    transition_table_.emplace_back(alphabet_.size());
}

void fsm::FSM::add_symbol(int symbol) {
    alphabet_.push_back(symbol);
    for (std::vector<fsm::State> row : transition_table_) {
        row.resize(row.size() + 1);
    }
}

void fsm::FSM::add_transition_rule(const fsm::State &state, int symbol, const fsm::State &next_state) {
    int row = 0, column = 0;
    for (; row < states_.size(); row++) {
        if (states_[row] == state) {
            break;
        }
    }
    for (; column < alphabet_.size(); column++) {
        if (alphabet_[column] == symbol) {
            break;
        }
    }

    if (column >= alphabet_.size()) {
        throw AutomationException("Input is not in alphabet", __FILE__, __LINE__);
    }

    transition_table_[row][column] = next_state;
}

void fsm::FSM::transition(int input) {
    int row = 0, column = 0;
    for (; row < states_.size(); row++) {
        if (states_[row] == *current_state_) {
            break;
        }
    }
    for (; column < alphabet_.size(); column++) {
        if (alphabet_[column] == input) {
            break;
        }
    }

    if (column >= alphabet_.size()) {
        throw "input is not in alphabet (TODO exception)";
    }

    current_state_ = &transition_table_[row][column];
}

bool fsm::FSM::is_in_final_state() const {
    if (std::find(final_states_.begin(), final_states_.end(), *current_state_) != final_states_.end()) {
       return true;
    }
    return false;
}

void fsm::FSM::restart() {
    current_state_ = &initial_state_;
}

void fsm::FSM::validate_states() const {
    std::set<fsm::String> uniq_states;
    for (const State& state : states_) {
        uniq_states.insert(state.get_name());
    }
    if (uniq_states.size() > states_.size()) {
        throw AutomationException("Duplicated states", __FILE__, __LINE__);
    }
}

void fsm::FSM::validate_initial_state() const {
    for (const State& state : states_) {
        if (state == initial_state_) {
            return;
        }
    }
    throw AutomationException("Initial state is not a valid state", __FILE__, __LINE__);
}

void fsm::FSM::validate_final_states() const {
    for (const State& final_state : final_states_) {
        bool missing = true;
        for (const State &state : states_) {
            if (state == final_state) {
                missing = false;
                break;
            }
        }
        if (missing) {
            throw AutomationException("At least one final state is not a valid state", __FILE__, __LINE__);
        }
    }
}

bool fsm::FSM::evaluate(const char* input) {
    bool flag = false;
    fsm::String word(input);
    int wordLen = word.size();

    for(int i = 0; i < wordLen; i++){
        FSM::transition(word[i] - '0'); // convert char to int
    }

    if(FSM::is_in_final_state()) flag = true;

    FSM::restart();

    return flag;
}

