#ifndef STATUS_H
#define STATUS_H

#include <string>

class Status
{
public:
    Status(std::string iName, int iDuration);
    Status();

    std::string GetName();
    int GetDuration();
    void DecrementDuration(int iDecrementValue = 1);
    void IncrementDuration(int iIncrementValue = 1);

private:
    std::string _Name;
    int _Duration;
};

#endif // STATUS_H