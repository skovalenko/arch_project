#include "file.h"
#include "archivator_manager.h"

int main (int argc, char** argv)
{
    archivator_manager m;

    m.process_file(std::string("/data/text"));

    return 0;
}
