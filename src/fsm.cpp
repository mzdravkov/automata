#include <set>
#include <algorithm>
#include <fstream>

#include "fsm.h"
#include "automation_exception.h"

fsm::FSM::FSM() {

}

fsm::FSM::FSM(const std::vector<fsm::State> &states, 
    const std::vector<int> &alphabet, 
    const fsm::State &initial_state,
    const std::vector<fsm::State> &final_states, 
    const std::vector<std::vector<fsm::State>> &transition_table)
        : states_(states),
    alphabet_(alphabet), 
    initial_state_(initial_state),
    final_states_(final_states),
    transition_table_(transition_table)
{
    current_state_ = &initial_state_;
    validate_states();
    validate_initial_state();
    validate_final_states();
}

// fsm::FSM::FSM(const fsm::String& destPath)
fsm::FSM::FSM(const char* destPath)
{
    std::ifstream f(destPath);
    f >> *this;
}

fsm::FSM::FSM(const fsm::FSM& rhs)
    : states_(rhs.states_), 
    alphabet_(rhs.alphabet_), 
    initial_state_(rhs.initial_state_),
    final_states_(rhs.final_states_), 
    transition_table_(rhs.transition_table_)
{
    current_state_ = &states_[indexOfState(*rhs.current_state_)];
}

fsm::FSM& fsm::FSM::operator=(const fsm::FSM& rhs)
{
    if (this != &rhs) {
        states_ = rhs.states_;
        alphabet_ = rhs.alphabet_;
        initial_state_ = rhs.initial_state_;
        final_states_ = rhs.final_states_;
        transition_table_ = rhs.transition_table_;

        current_state_ = &states_[indexOfState(*rhs.current_state_)];
    }

    return *this;
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

void fsm::FSM::add_final_state(const fsm::State &state) {
    final_states_.push_back(state);
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

unsigned fsm::FSM::indexOfState(const fsm::State& st) const
{
    unsigned i = 0;

    while (i < states_.size() - 1 && !(states_[i] == st)) {
        i++;
    }
    
    return i;
}

bool fsm::FSM::is_in_final_state() const {
    if (std::find(final_states_.begin(), final_states_.end(), *current_state_) != final_states_.end()) {
       return true;
    }
    return false;
}

fsm::FSM fsm::FSM::fromTXT(const char* sourcePath)
{
    std::ifstream inF(sourcePath);
    inF >> *this;
    inF.close();

    return *this;
}

void fsm::FSM::toTXT(const char* dest) const
{
    std::ofstream outF(dest);
    outF << *this;
    outF.close();
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
    fsm::String word(input);

    for(int i = 0, l = word.size(); i < l; i++){
        FSM::transition(word[i] - '0'); // convert char to int
    }

    bool flag = FSM::is_in_final_state();
    FSM::restart();

    return flag;
}

fsm::FSM fsm::FSM::operator!() const {
    std::vector<fsm::State> newFinalStates;
    fsm::FSM complementMachine = *this;

    for(int i = 0, sz = get_states_count(); i < sz; i++){
        if(std::find(final_states_.begin(),final_states_.end(),states_[i]) == final_states_.end()){
            newFinalStates.push_back(states_[i]);
        }
    }

    complementMachine.set_final_states(newFinalStates);

    return complementMachine;
}

fsm::FSM fsm::FSM::operator|(const fsm::FSM &rhs) const {
    fsm::FSM unionMachine, thisMachine = *this, otherMachine = rhs;
    thisMachine.restart();
    otherMachine.restart();

    fsm::State comboState = thisMachine.get_initial_state() + otherMachine.get_initial_state();  // Get the initial state.

    auto alphabet = get_alphabet();
    for(int i = 0, sz = get_alphabet_count(); i < sz; i++) { unionMachine.add_symbol(alphabet[i]); }  // Add the alphabet.
    unionMachine.add_state(comboState);

    fsm::fill(thisMachine, otherMachine, unionMachine, comboState);

    unionMachine.set_initial_state(comboState);
    unionMachine.restart();

    return unionMachine;
}

void fsm::fill(fsm::FSM m1, fsm::FSM m2, fsm::FSM &m3, fsm::State prevState) {
    for(int i = 0, sz = m1.get_alphabet_count(); i < sz; i++){
        auto m1old = m1, m2old = m2;
        auto m3States = m3.get_states();
        char currLetter = m3.get_alphabet()[i];

        m1.transition(currLetter);
        m2.transition(currLetter);

        fsm::State comboState = m1.get_current_state() + m2.get_current_state();

        if(std::find(m3States.begin(), m3States.end(), comboState) == m3States.end()){
            m3.add_state(comboState);
            if(m1.is_in_final_state() || m2.is_in_final_state()) { 
                m3.add_final_state(comboState); 
            }
            fsm::fill(m1, m2, m3, comboState);
        }
        m3.add_transition_rule(prevState, currLetter, comboState);
        m1 = m1old;
        m2 = m2old;
    }
}

fsm::FSM fsm::FSM::operator&(const fsm::FSM &rhs) const {
    std::vector<fsm::State> newEndStates;
    fsm::FSM unionMachine = *this | rhs;
    auto thisFinalStates = get_final_states();  // get sub-final states
    auto otherFinalStates = rhs.get_final_states(); // get sub-final states
    auto unionEndStates = unionMachine.get_final_states();

    for(int i = 0, sz1 = get_final_states_count(); i < sz1; i++){
        for(int j = 0, sz2 = rhs.get_final_states_count(); j < sz2; j++){
            fsm::State doubleEndState = thisFinalStates[i] + otherFinalStates[j];  // construct final state of two sub-final states
            if(std::find(unionEndStates.begin(), unionEndStates.end(), doubleEndState) != unionEndStates.end()){  // check if such final state exists
                newEndStates.push_back(doubleEndState);
            }
        }
    }

    fsm::FSM intersectionMachine = unionMachine;
    intersectionMachine.set_final_states(newEndStates);

    return intersectionMachine;
}

std::ostream &fsm::FSM::ins(std::ostream &out) const {
    int stateC = get_states_count(), alphaC = get_alphabet_count();
    auto table = get_transition_table();
    fsm::State st;

    for(int i = 0; i < stateC; i++){
        out << states_[i] << " | ";
        for(int j = 0; j < alphaC; j++){
            st = table[i][j];
            out << st << "\t";
        }
        out << "\n";
    }

    return out;
}

std::ostream& fsm::FSM::fins(std::ostream& out) const
{   
    int stateC = get_states_count(), alphaC = get_alphabet_count(), endSC = get_final_states_count();
    fsm::State st;

    out << alphaC;

    for (int i = 0; i < alphaC; i++) {
        out << " " << alphabet_[i] - '0';
    }

    out << "\n" << stateC;

    for (int i = 0; i < stateC; i++) {
        out << " " << states_[i].get_name();
    }

    out << "\n";
    for (int i = 0; i < stateC; i++) {
        for (int j = 0; j < alphaC; j++) {
            out << transition_table_[i][j].get_name() << " ";
            //if (j < alphaC - 1) { out << " "; }
        }
        out << "\n";
    }

    out << initial_state_.get_name() << "\n";
    out << endSC;

    for (int i = 0; i < endSC; i++) {
        out << " " << final_states_[i].get_name();
    }

    return out;
}

std::istream& fsm::FSM::ext(std::istream& in)
{
    unsigned int stateCount, alphaCount, endStateCount;
    fsm::String stateName;
    char letter;

    if (typeid(in) == typeid(std::ifstream)) {
        std::cout.setstate(std::ios_base::failbit);
    }

    // Bug: If states are added before symbols, the
    // transition table does not resize.

    std::cout << "Enter the number of letters: ";
    in >> alphaCount;

    for (int i = 0; i < alphaCount; i++) {
        std::cout << "\nEnter letter " << i << " : ";
        in >> letter;
        add_symbol(letter);
    }

    std::cout << "\nEnter the number of states: ";
    in >> stateCount;

    for (int i = 0; i < stateCount; i++) {
        std::cout << "\nEnter the name of state " << i << " : ";
        in >> stateName;
        add_state(fsm::State(stateName)); // tuk moje da ima problemi s anon object :(
    }

    for (int i = 0; i < stateCount; i++) {
        for (int j = 0; j < alphaCount; j++) {
            std::cout << "\nWhere does " << states_[i] << " go with letter \"" << char(alphabet_[j]) << "\" ?: ";
            in >> stateName;
            add_transition_rule(states_[i], alphabet_[j], states_[indexOfState(fsm::State(stateName))]);
        }
    }

    std::cout << "\nEnter the starting state: ";
    in >> stateName;
    initial_state_ = states_[indexOfState(fsm::State(stateName))];
    
    std::cout << "\nEnter the number of end-states: ";
    in >> endStateCount;

    for (int i = 0; i < endStateCount; i++) {
        std::cout << "\nEnter name of end-state " << i << " : ";
        in >> stateName;
        add_final_state(states_[indexOfState(fsm::State(stateName))]);
    }

    current_state_ = &initial_state_;

    validate_states();
    validate_initial_state();
    validate_final_states();

    std::cout.clear();
    return in;
}

std::ostream &fsm::operator<<(std::ostream &out, const fsm::FSM &rhs) {
    if (typeid(out) == typeid(std::ofstream)) {
        return rhs.fins(out);
    }

    return rhs.ins(out);
}

std::istream& fsm::operator>>(std::istream& in, fsm::FSM& rhs)
{
    return rhs.ext(in);
}
