#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <information_about_process.h>

void Info::setFile(const std::string &file_name)
{
    delete _file;
    _file = new ParseFile(file_name);
}

void Info::printName()
{
    setFile("/proc/" + std::to_string(_pid) + "/status");
    std::cout << _file->getString("Name") << "\n";
}

void Info::printIsDaemon() const
{
    std::cout << "Демон: ";
    std::cout << (isDaemon() ? "Да\n" : "Нет\n");
}

bool Info::isDaemon() const
{
    std::ifstream statFile("/proc/" + std::to_string(_pid) + "/stat");
    std::string stat;
    std::getline(statFile, stat);

    int ppid = 0;
    sscanf(stat.c_str(), "%*d %*s %*c %d", &ppid);

    statFile.close();

    return ppid == 1;
}

bool Info::isSystem() const
{
    ParseFile file("/proc/" + std::to_string(_pid) + "/cmdline");
    return file.getString("/").empty() || _pid == 1;
}

void Info::printIsSystem() const
{
    std::cout << "Системный процесс: ";
    std::cout << (isSystem() ? "Да\n" : "Нет\n");
}

void Info::printPpid()
{
    setFile("/proc/" + std::to_string(_pid) + "/status");
    std::cout << _file->getString("PPid") << '\n';
}


void Info::printPolicy()
{
    std::unordered_map<int, std::string> policy =
    {
            {SCHED_FIFO, "SCHED_FIFO"},
            {SCHED_RR, "SCHED_RR"},
            {SCHED_OTHER, "SCHED_OTHER"},
            {SCHED_BATCH, "SCHED_BATCH"},
            {SCHED_IDLE, "SCHED_IDLE"},
            {SCHED_ISO, "SCHED_ISO"},
            {SCHED_DEADLINE, "SCHED_DEADLINE"}
    };

    setFile("/proc/" + std::to_string(_pid) + "/sched");
    int p = _file->getString("policy").back() - '0';
    std::cout << "Policy:\t" << policy[p] << "\n";
}

void Info::printPriority()
{
    setFile("/proc/" + std::to_string(_pid) + "/sched");
    std::string s = _file->getString("prio");
    size_t i = s.size();
    std::cout << "Priority: " << s[i - 3] << s[i - 2] << s[i - 1] << "\n";
}

void Info::printState()
{
    setFile("/proc/" + std::to_string(_pid) + "/status");
    std::cout << _file->getString("State") << '\n';
}

void Info::printThreads()
{
    setFile("/proc/" + std::to_string(_pid) + "/status");
    std::cout << _file->getString("Threads") << '\n';
}

void Info::printFlags()
{
    std::unordered_map<int, std::string> flag_converter =
    {
            {0x00000001, "Виртуальный процессор"},
            {0x00000002, "Пустой поток"},
            {0x00000004, "Выключение"},
            {0x00000008, "Coredumps должен игнорировать эту задачу"},
            {0x00000010, "Задача - рабочий процесс ввода-вывода"},
            {0x00000020, "Рабочий процесс очереди работ"},
            {0x00000040, "Forked, но не exec"},
            {0x00000080, "Политика процесса при ошибках mce"},
            {0x00000100, "Использованы привилегии суперпользователя"},
            {0x00000200, "Сохранено ядро"},
            {0x00000400, "Уничтожен сигналом"},
            {0x00000800, "Выделение памяти"},
            {0x00001000, "set_user() обнаружил превышение RLIMIT_NPROC"},
            {0x00002000, "Если не установлено, fpu должен быть инициализирован перед использованием"},
            {0x00004000, "Ядро склонировано из пользовательского пространства"},
            {0x00008000, "Этот поток не должен быть заморожен"},
            {0x00020000, "kswapd"},
            {0x00040000, "Все запросы на выделение будут наследовать GFP_NOFS"},
            {0x00080000, "Все запросы на выделение будут наследовать GFP_NOIO"},
            {0x00100000, "Ограничивать записи только на bdi, в которую я записываю, я очищаю грязные страницы из другого bdi."},
            {0x00200000, "Поток ядра"},
            {0x00400000, "Случайное распределение виртуального адресного пространства"},
            {0x04000000, "Пользовательское пространство не может вмешиваться в cpus_mask"},
            {0x08000000, "Раннее завершение для политики процесса mce"},
            {0x10000000, "Контекст выделения ограничен зонами, позволяющими долгосрочное закрепление."},
            {0x80000000, "Этот поток вызвал freeze_processes() и не должен быть заморожен"}
    };

    setFile("/proc/" + std::to_string(_pid) + "/stat");

    int flags = std::stoi((_file->splitFile().at(8)));
    std::vector<std::string> ans;

    for (int i = 1; i < 0x80000000; i *= 2)
    {
        if (flags & i)
        {
            ans.push_back(flag_converter[i]);
        }
    }

    if (flags & 0x80000000)
    {
        ans.push_back(flag_converter[0x80000000]);
    }

    std::cout << "Флаги: \n";
    for (const std::string& i : ans)
    {
        if (!i.empty())
        {
            std::cout << "\t" << i << "\n";
        }
    }
}

void Info::printAllAboutProcess()
{
    printName();
    printPpid();
    printPid();
    printState();
    printPolicy();
    printThreads();
    printPriority();
    printIsDaemon();
    printIsSystem();
    printFlags();
}

void Info::printPid()
{
    setFile("/proc/" + std::to_string(_pid) + "/status");
    std::cout << _file->getString("Pid") << '\n';
}
