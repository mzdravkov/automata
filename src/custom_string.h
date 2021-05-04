#ifndef AUTOMATA_CUSTOM_STRING_H
#define AUTOMATA_CUSTOM_STRING_H

#include <ostream>

namespace fsm {
    // An inferior implementation of a String class
    class String {
        char* str_;
    public:
        String();

        String(char* str);

        String(int n);

        String(const fsm::String& other);

        ~String();

        const char* to_char_array() const;

        int size() const;

        bool operator==(const String &rhs) const;

        bool operator!=(const String &rhs) const;

        friend std::ostream &operator<<(std::ostream &os, const String &string);

        fsm::String operator+(const String &rhs) const;

        bool operator<(const String &rhs) const;
    };
}

#endif //AUTOMATA_CUSTOM_STRING_H
