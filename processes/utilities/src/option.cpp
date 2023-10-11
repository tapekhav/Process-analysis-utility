#include <option.h>
#include <many_processes.h>
#include <information_about_process.h>

const char *opts = "SsAdPtqfnpghaDw";
const struct option longOpts[] =
{
        {"help", no_argument, nullptr, 'h'},
        {"name", no_argument, nullptr, 'n'},
        {"All", no_argument, nullptr, 'A'},
        {"all-system", no_argument, nullptr, 'w'},
        {"all", no_argument, nullptr, 'a'},
        {"demon", no_argument, nullptr, 'd'},
        {"system", no_argument, nullptr, 's'},
        {"parent", no_argument, nullptr, 'p'},
        {"pid", no_argument, nullptr, 'P'},
        {"sched-policy", no_argument, nullptr, 'S'},
        {"queue-prio", no_argument, nullptr, 'q'},
        {"threads", no_argument, nullptr, 't'},
        {"state", no_argument, nullptr, 'g'},
        {"flags", no_argument, nullptr, 'f'},
        {"Daemons-all", no_argument, nullptr, 'D'},
        {nullptr, no_argument, nullptr, 0}
};


Option::Option(int argc, char **argv) : _argc(argc), _proc(nullptr), _flag(false)
{
    _argv = static_cast<char**>(malloc(argc * sizeof(char*)));
    for (int i = 0; i < argc; ++i)
    {
        _argv[i] = argv[i];
    }
}

Option::~Option()
{
    free(_argv);

    delete _proc;
}

void Option::start()
{
    std::cout << "\n\n---------НАЧАЛО----------------\n";

    checkConditions();
    std::unordered_map<int, std::function<void()>> key_button =
    {
            {'h', []() { ManyProcesses::printHelp(); }},
            {'A', []() { ManyProcesses::printAll(); }},
            {'w', []() { ManyProcesses::printAllSystem(); }},
            {'D', []() { ManyProcesses::printAllDaemons(); }},
            {'a', [this]() { _proc->printAllAboutProcess(); }},
            {'p', [this]() { _proc->printPpid(); }},
            {'d', [this]() { _proc->printIsDaemon(); }},
            {'n', [this]() { _proc->printName(); }},
            {'q', [this]() { _proc->printPriority(); }},
            {'s', [this]() { _proc->printIsSystem(); }},
            {'S', [this]() { _proc->printPolicy(); }},
            {'g', [this]() { _proc->printState(); }},
            {'P', [this]() { _proc->printPid(); }},
            {'t', [this]() { _proc->printThreads(); }},
            {'f', [this]() { _proc->printFlags(); }},
    };

    if (!_flag)
    {

        int pid = atoi(_argv[1]);
        _proc = new Info(pid);

        int opt;
        int longIndex;
        opt = getopt_long(_argc, _argv, opts, longOpts, &longIndex);

        while (opt != -1)
        {
            key_button[opt]();
            opt = getopt_long(_argc, _argv, opts, longOpts, &longIndex);
        }
    }

    std::cout << "------------КОНЕЦ--------------\n\n";
}

void Option::checkConditions()
{
    if(_argc < 2)
    {
        std::cout << "Напишите -h(--help)\n";
        _flag = true;
        return;
    }

    if (!strcmp(_argv[1], "-h") || !strcmp(_argv[1], "--help"))
    {
        ManyProcesses::printHelp();
        _flag = true;
    }

    if (!strcmp(_argv[1], "-w") || !strcmp(_argv[1], "--all-system"))
    {
        ManyProcesses::printAllSystem();
        _flag = true;
    }

    if (!strcmp(_argv[1], "-D") || !strcmp(_argv[1], "--Daemons-all"))
    {
        ManyProcesses::printAllDaemons();
        _flag = true;
    }

    if (!strcmp(_argv[1], "-A") || !strcmp(_argv[1], "--All"))
    {
        ManyProcesses::printAll();
        _flag = true;
    }
}
