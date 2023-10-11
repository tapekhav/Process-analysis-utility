#ifndef EXTRA_TASK_OPTION_H
#define EXTRA_TASK_OPTION_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <getopt.h>
#include <cstring>
#include <vector>

class Info;

class Option
{
public:
    Option(int argc, char* argv[]);
    ~Option();

    void start();
private:
    void checkConditions();

    bool _flag;
    int _argc;
    char** _argv;
    Info* _proc;
};


#endif