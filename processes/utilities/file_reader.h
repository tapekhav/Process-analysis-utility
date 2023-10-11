#ifndef EXTRA_TASK_FILE_READER_H
#define EXTRA_TASK_FILE_READER_H

#include <vector>
#include <fstream>

class ParseFile
{
public:
    explicit ParseFile(const std::string& file_name) : _file(file_name) {}
    ~ParseFile() { _file.close(); }

    std::string getString(const std::string& str);
    std::vector<std::string> splitFile();
private:
    std::ifstream _file;
};



#endif //EXTRA_TASK_FILE_READER_H
