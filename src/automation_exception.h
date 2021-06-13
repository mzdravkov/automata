#ifndef AUTOMATA_AUTOMATION_EXCEPTION_H
#define AUTOMATA_AUTOMATION_EXCEPTION_H

#include <exception>
#include "custom_string.h"

namespace fsm {
    /**
     * AutomationException is a general exception used when an error
     * with the finite state machine occurs.
     */
    class AutomationException : public std::exception {
        fsm::String msg_;
        fsm::String file_;
        int line_;

    public:
        /**
         * AutomationException constructor.
         * @param char *msg: Message that explains the error.
         * @param char *file: Name of the source file where the exception occured.
         * @param int line: Line in the source file where the exception occured.
         */
        AutomationException(char *msg, char *file, int line);

        /**
         * Returns the message associated with the exception.
         */
        fsm::String get_msg() const;

        /**
         * Returns the name of the source file in which the exception occured.
         */
        fsm::String get_file() const;

        /**
         * Returns the line of the source file where the exception occured.
         */
        int get_line() const;

        /**
         * Returns a string representation of the exception (including file, line and error message).
         */
        const char* what() const noexcept override;
    };
}

#endif //AUTOMATA_AUTOMATION_EXCEPTION_H
