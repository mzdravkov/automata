#ifndef AUTOMATA_CUSTOM_STRING_H
#define AUTOMATA_CUSTOM_STRING_H

#include <iostream>

namespace fsm {
    /**
     * A custom implementation of a String.
     */
    class String {
        char* str_;
    public:
        /**
         * Returns an empty string.
         */
        String();

        /**
         * Creates a new String with the content of the char array.
         * @param char *str: Content for the new string instance.
         */
        String(const char* str);

        /**
         * Creates a new String representing the provided integer number.
         * @param int n: An integer that will be set as the content of the new String.
         */
        String(int n);

        /**
         * A copy contstructor.
         * @param String& other: A string that will be copied.
         */
        String(const fsm::String& other);

        /**
         * A destructor for the String class.
         */
        ~String();

        /**
         * Returns a char array with the content of the String.
         */
        const char* to_char_array() const;

        /**
         * Returns the size of the String. That is, the number of characters in it.
         */
        int size() const;

        /**
         * An equality operator. Will return true if the other String has the same content.
         * @param String &rhs: Another String instance that will be compared to **this**.
         */
        bool operator==(const String &rhs) const;

        /**
         * An inequality operator. Will return true if the other String has a different content.
         * @param String &rhs: Another String instance that will be compared to **this**.
         */
        bool operator!=(const String &rhs) const;

        /**
         * An insertion operator for adding the content of a String to an output stream.
         * @param ostream &os: Output stream where the String will be written.
         * @param String &string: String to write to the output stream.
         */
        friend std::ostream &operator<<(std::ostream &os, const String &string);

        /**
         * An addition operator for Strings. Concatenates the content of two strings.
         * @param String &rhs: A second String that will be concatenated to **this**.
         */
        fsm::String operator+(const String &rhs) const;

        /**
         * A comparison operator.
         * Compares **this** and the provided String lexicographically.
         * Will return true if **this** is smaller than **rhs**.
         * @param String &rhs: Another String to compare **this** with.
         */
        bool operator<(const String &rhs) const;

        /**
         * Subscript operator for String.
         * Will return the character at the provided position.
         * @param unsigned i: index of the character that will be returned.
         */
        char operator[](unsigned i) const;

        /**
         * Sets the value of the String to the content of the
         * provided input stream.
         * @param istream &in: Input stream from which the content for the String will be read.
         */
        std::istream& ext(std::istream& in);
    };

    /**
     * An extraction operator. Will write the content of the String to the provided output stream.
     * @param istream &in: Input stream from which the content for the String will be read.

     * @param String &s: The String to be written to the output stream.
     */
    std::istream& operator>>(std::istream& in, String& s);

}

#endif //AUTOMATA_CUSTOM_STRING_H
