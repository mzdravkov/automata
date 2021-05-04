#include <cstdio>
#include <iostream>
#include "automation_exception.h"

fsm::AutomationException::AutomationException(char* msg, char* file, int line)
        : std::exception(),
          msg_(msg),
          file_(file),
          line_(line) {}

fsm::String fsm::AutomationException::get_msg() const { return msg_; }

fsm::String fsm::AutomationException::get_file() const { return file_; }

int fsm::AutomationException::get_line() const { return line_; }

const char* fsm::AutomationException::what() const noexcept {
    return (file_ + fsm::String(" line ") + fsm::String(line_) + fsm::String(": ") + msg_).to_char_array();
}