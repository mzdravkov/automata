#ifndef AUTOMATA_AUTOMATION_EXCEPTION_H
#define AUTOMATA_AUTOMATION_EXCEPTION_H

#include <exception>
#include "custom_string.h"

namespace fsm {
    class AutomationException : public std::exception {
        fsm::String msg_;
        fsm::String file_;
        int line_;

    public:
        AutomationException(char *msg, char *file, int line);

        fsm::String get_msg() const;

        fsm::String get_file() const;

        int get_line() const;

        const char* what() const noexcept override;
    };
}

#endif //AUTOMATA_AUTOMATION_EXCEPTION_H
