#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

class InputOutput
{
public:
    InputOutput();

    bool YesNoChoice();
    bool ABChoices(std::string AChoice, std::string BChoice);
    void PressEnter();
    void Refresh();
    
};

#endif // INPUTOUTPUT_H