#include <cstring>

#include "custom_string.h"

fsm::String::String() : str_("") {}

fsm::String::String(const char *str) : str_(new char[strlen(str)+1]) {
    std::strcpy(str_, str);
}

fsm::String::String(int n) {
    int length = snprintf(nullptr, 0,"%d",42);
    str_ = new char[length + 1];
    sprintf(str_, "%d", n);
}

fsm::String::String(const fsm::String &other) : str_(new char[strlen(other.str_)+1]) {
    std::strcpy(str_, other.str_);
}

fsm::String::~String() {
//    delete [] str_;
}

const char* fsm::String::to_char_array() const {
    char* str_cpy = new char[strlen(str_)];
    std::strcpy(str_cpy, str_);
    return str_cpy;
}

int fsm::String::size() const {
    return std::strlen(str_);
}

bool fsm::String::operator==(const fsm::String &rhs) const {
    return std::strcmp(str_, rhs.str_) == 0;
}

bool fsm::String::operator!=(const fsm::String &rhs) const {
    return !(rhs == *this);
}

std::ostream &fsm::operator<<(std::ostream &os, const fsm::String &string) {
    os << string.str_;
    return os;
}

fsm::String fsm::String::operator+(const fsm::String &rhs) const {
    int total_size = this->size() + rhs.size() + 1;
    char* concatenation = new char[total_size];

    std::strcpy(concatenation, str_);
    strcat(concatenation, rhs.str_);

    fsm::String res(concatenation);

    return res;
}

bool fsm::String::operator<(const fsm::String &rhs) const {
    int lhs_size = this->size();
    int rhs_size = rhs.size();
    for (int i = 0; i < std::min(lhs_size, rhs_size); i++) {
        if (str_[i] > rhs.str_[i]) {
            return false;
        } else if (str_[i] < rhs.str_[i]) {
            return true;
        }
    }

    if (lhs_size >= rhs_size) {
        return false;
    }
    return true;
}

char fsm::String::operator[](unsigned int i) const {
    return str_[i];
}



