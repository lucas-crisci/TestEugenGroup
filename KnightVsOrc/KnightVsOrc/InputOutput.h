#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

#include "InputOutput.h"

#include <string>

class InputOutput
{
public:
    InputOutput() {};

    bool YesNoChoice();
    bool ABChoices(std::string AChoice, std::string BChoice);
    void PressEnter();
    void Refresh();
};

#endif // INPUTOUTPUT_H