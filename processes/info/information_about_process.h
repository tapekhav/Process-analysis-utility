#ifndef EXTRA_TASK_INFORMATION_ABOUT_PROCESS_H
#define EXTRA_TASK_INFORMATION_ABOUT_PROCESS_H

#include <string>
#include <file_reader.h>

class Info
{
public:
    explicit Info(int pid) : _pid(pid), _file(nullptr) {}
    ~Info() { delete _file; }

    [[nodiscard]] bool isDaemon() const;
    [[nodiscard]] bool isSystem() const;

    void printPid();
    void printName();
    void printPpid();
    void printState();
    void printFlags();
    void printPolicy();
    void printThreads();
    void printPriority();
    void printIsDaemon() const;
    void printIsSystem() const;

    void printAllAboutProcess();

    void setFile(const std::string& file_name);
private:
    int _pid;
    ParseFile* _file;
};


#endif //EXTRA_TASK_INFORMATION_ABOUT_PROCESS_H
