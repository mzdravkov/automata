#include <set>
#include <algorithm>
#include <fstream>

#include "fsm.h"
#include "automation_exception.h"

template <typename T>
fsm::FSM<T>::FSM() {

}

template <typename T>
fsm::FSM<T>::FSM(const std::vector<fsm::State> &states,
    const std::vector<T> &alphabet,
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

template <typename T>
fsm::FSM<T>::FSM(const char* destPath)
{
    std::ifstream f(destPath);
    f >> *this;
}

template <typename T>
fsm::FSM<T>::FSM(const fsm::FSM<T>& rhs)
    : states_(rhs.states_),
    alphabet_(rhs.alphabet_),
    initial_state_(rhs.initial_state_),
    final_states_(rhs.final_states_),
    transition_table_(rhs.transition_table_)
{
    current_state_ = &states_[indexOfState(*rhs.current_state_)];
}

template <typename T>
fsm::FSM<T>& fsm::FSM<T>::operator=(const fsm::FSM<T>& rhs)
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

template <typename T>
fsm::FSM<T>::~FSM() = default;
//    delete [] current_state_;
//};

template <typename T>
int fsm::FSM<T>::get_states_count() const {
    return states_.size();
}

template <typename T>
const std::vector<fsm::State> &fsm::FSM<T>::get_states() const {
    return states_;
}

template <typename T>
void fsm::FSM<T>::set_states(const std::vector<fsm::State> &states) {
    states_ = states;
}

template <typename T>
int fsm::FSM<T>::get_alphabet_count() const {
    return alphabet_.size();
}

template <typename T>
const std::vector<T> &fsm::FSM<T>::get_alphabet() const {
    return alphabet_;
}

template <typename T>
void fsm::FSM<T>::set_alphabet(const std::vector<T> &alphabet) {
    alphabet_ = alphabet;
}

template <typename T>
const fsm::State &fsm::FSM<T>::get_initial_state() const {
    return initial_state_;
}

template <typename T>
void fsm::FSM<T>::set_initial_state(const fsm::State &initialState) {
    initial_state_ = initialState;
}

template <typename T>
int fsm::FSM<T>::get_final_states_count() const {
    return final_states_.size();
}

template <typename T>
const std::vector<fsm::State> &fsm::FSM<T>::get_final_states() const {
    return final_states_;
}

template <typename T>
void fsm::FSM<T>::set_final_states(const std::vector<fsm::State> &final_states) {
    final_states_ = final_states;
}

template <typename T>
const std::vector<std::vector<fsm::State>> &fsm::FSM<T>::get_transition_table() const {
    return transition_table_;
}

template <typename T>
void fsm::FSM<T>::set_transition_table(const std::vector<std::vector<fsm::State>> &transition_table) {
    transition_table_ = transition_table;
}

template <typename T>
fsm::State fsm::FSM<T>::get_current_state() const {
    return *current_state_;
}

template <typename T>
void fsm::FSM<T>::add_state(const fsm::State &state) {
    states_.push_back(state);
    transition_table_.emplace_back(alphabet_.size());
}

template <typename T>
void fsm::FSM<T>::add_symbol(T symbol) {
    alphabet_.push_back(symbol);
    for (std::vector<fsm::State> row : transition_table_) {
        row.resize(row.size() + 1);
    }
}

template <typename T>
void fsm::FSM<T>::add_final_state(const fsm::State &state) {
    final_states_.push_back(state);
}

template <typename T>
void fsm::FSM<T>::add_transition_rule(const fsm::State &state, T symbol, const fsm::State &next_state) {
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

template <typename T>
void fsm::FSM<T>::transition(T input) {
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

template <typename T>
unsigned fsm::FSM<T>::indexOfState(const fsm::State& st) const {
    unsigned i = 0;

    while (i < states_.size() - 1 && !(states_[i] == st)) {
        i++;
    }

    return i;
}

template <typename T>
bool fsm::FSM<T>::is_in_final_state() const {
    if (std::find(final_states_.begin(), final_states_.end(), *current_state_) != final_states_.end()) {
       return true;
    }
    return false;
}

template <typename T>
fsm::FSM<T> fsm::FSM<T>::fromTXT(const char* sourcePath)
{
    std::ifstream inF(sourcePath);
    inF >> *this;
    inF.close();

    return *this;
}

template <typename T>
void fsm::FSM<T>::toTXT(const char* dest) const
{
    std::ofstream outF(dest);
    outF << *this;
    outF.close();
}

template <typename T>
void fsm::FSM<T>::restart() {
    current_state_ = &initial_state_;
}

template <typename T>
void fsm::FSM<T>::validate_states() const {
    std::set<fsm::String> uniq_states;
    for (const State& state : states_) {
        uniq_states.insert(state.get_name());
    }
    if (uniq_states.size() > states_.size()) {
        throw AutomationException("Duplicated states", __FILE__, __LINE__);
    }
}

template <typename T>
void fsm::FSM<T>::validate_initial_state() const {
    for (const State& state : states_) {
        if (state == initial_state_) {
            return;
        }
    }
    throw AutomationException("Initial state is not a valid state", __FILE__, __LINE__);
}

template <typename T>
void fsm::FSM<T>::validate_final_states() const {
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

template <typename T>
bool fsm::FSM<T>::evaluate(const char* input) {
    fsm::String word(input);

    for(int i = 0, l = word.size(); i < l; i++){
        FSM::transition(word[i] - '0'); // convert char to int
    }

    bool flag = FSM::is_in_final_state();
    FSM::restart();

    return flag;
}

template <typename T>
fsm::FSM<T> fsm::FSM<T>::operator!() const {
    std::vector<fsm::State> newFinalStates;
    fsm::FSM<T> complementMachine = *this;

    for(int i = 0, sz = get_states_count(); i < sz; i++){
        if(std::find(final_states_.begin(),final_states_.end(),states_[i]) == final_states_.end()){
            newFinalStates.push_back(states_[i]);
        }
    }

    complementMachine.set_final_states(newFinalStates);

    return complementMachine;
}

template <typename T>
fsm::FSM<T> fsm::FSM<T>::operator|(const fsm::FSM<T> &rhs) const {
    fsm::FSM<T> unionMachine, thisMachine = *this, otherMachine = rhs;
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

template <typename T>
void fsm::fill(fsm::FSM<T> m1, fsm::FSM<T> m2, fsm::FSM<T> &m3, fsm::State prevState) {
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

template <typename T>
fsm::FSM<T> fsm::FSM<T>::operator&(const fsm::FSM<T> &rhs) const {
    std::vector<fsm::State> newEndStates;
    fsm::FSM<T> unionMachine = *this | rhs;
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

    fsm::FSM<T> intersectionMachine = unionMachine;
    intersectionMachine.set_final_states(newEndStates);

    return intersectionMachine;
}

template <typename T>
std::ostream &fsm::FSM<T>::ins(std::ostream &out) const {
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

template <typename T>
std::ostream& fsm::FSM<T>::fins(std::ostream& out) const {
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

template <typename T>
std::istream& fsm::FSM<T>::ext(std::istream& in) {
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

template <typename T>
std::ostream &fsm::operator<<(std::ostream &out, const fsm::FSM<T> &rhs) {
    if (typeid(out) == typeid(std::ofstream)) {
        return rhs.fins(out);
    }

    return rhs.ins(out);
}

template <typename T>
std::istream& fsm::operator>>(std::istream& in, fsm::FSM<T>& rhs) {
    return rhs.ext(in);
}


template class fsm::FSM<int>;
template class fsm::FSM<char>;
template std::ostream &fsm::operator<<(std::ostream &out, const fsm::FSM<int> &rhs);
template std::ostream &fsm::operator<<(std::ostream &out, const fsm::FSM<char> &rhs);
