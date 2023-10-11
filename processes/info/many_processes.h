#ifndef EXTRA_TASK_MANY_PROCESSES_H
#define EXTRA_TASK_MANY_PROCESSES_H

#include <functional>

class ManyProcesses
{
public:
    static void printAll() { printProcesses("all"); }
    static void printAllSystem() { printProcesses("system"); }
    static void printAllDaemons() { printProcesses("daemon"); }

    static void printHelp();
private:
    static void printProcesses(const std::string& str);
};


#endif //EXTRA_TASK_MANY_PROCESSES_H
