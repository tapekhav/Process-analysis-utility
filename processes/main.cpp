#include "utilities/option.h"

int main(int argc, char* argv[])
{
    auto* object = new Option(argc, argv);
    object->start();

    delete object;

    return 0;
}
