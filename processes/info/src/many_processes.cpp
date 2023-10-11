#include <string>
#include <iostream>
#include <dirent.h>
#include <many_processes.h>
#include <information_about_process.h>


void ManyProcesses::printProcesses(const std::string& str)
{
    std::unordered_map<std::string, std::function<bool(const Info&)>> function_map =
    {
            {"daemon", [](const Info& proc) { return proc.isDaemon(); }},
            {"system", [](const Info& proc) { return proc.isSystem(); }},
            {"all", [](const Info& proc) { return true; }}
    };

    DIR* dir = opendir("/proc");

    dirent* entry;
    while ((entry = readdir(dir)) != nullptr)
    {
        if (entry->d_type == DT_DIR && entry->d_name[0] >= '0' && entry->d_name[0] <= '9')
        {
            int pid = std::stoi(entry->d_name);
            Info process(pid);
            auto result_func = function_map[str];

            if (result_func(process))
            {
                process.printAllAboutProcess();
            }
        }
        std::cout << "\n";
    }
}

void ManyProcesses::printHelp()
{
    std::cout << "-h(--h) - выводит справочник\n";
    std::cout << "-a(--all) - всю информацию о процессе\n";
    std::cout << "-A(--All) - выводит все процессы\n";
    std::cout << "-w(--all-system) - выводит все системные процессы\n";
    std::cout << "-d(--demon) - определяет, является ли процесс процессом-демоном\n";
    std::cout << "-s(--system) - проверяет, является ли процесс системным\n";
    std::cout << "-p(--parent) - выводит родителя процесса\n";
    std::cout << "-S(--sched-policy) - выводит политику планирования процесса\n";
    std::cout << "-q(--queue-prio) - выводит приоритет процесса\n";
    std::cout << "-t(--threads) - выводит потоки процесса\n";
    std::cout << "-g(--state) - выводит состояние процесса\n";
    std::cout << "-f(--flags) - выводит флаги процесса\n";
    std::cout << "-D(--Daemons-all) - выводит всех процессы-демоны\n";
}
