#include <file_reader.h>

std::string ParseFile::getString(const std::string &str)
{
    std::string current_string;
    while (getline(_file, current_string))
    {
        if (current_string.find(str) != std::string::npos)
        {
            return current_string;
        }
    }
    return "";
}

std::vector<std::string> ParseFile::splitFile()
{
    std::vector<std::string> result;

    std::string line;
    while (getline(_file, line))
    {
        size_t pos = 0;
        std::string token;
        while ((pos = line.find(' ')) != std::string::npos)
        {
            token = line.substr(0, pos);
            result.push_back(token);
            line.erase(0, pos + 1);
        }
        result.push_back(line);
    }

    return result;
}