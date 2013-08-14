#include "file.h"
#include "archivator_manager.h"
#include <QTime>

int main (int argc, char** argv)
{
    QTime start = QTime::currentTime();

    archivator_manager m;

    m.encode_file(std::string("/data/distrib/qt-linux-opensource-5.1.0-x86_64-offline.run"), std::string("/data/out"));

    qDebug() << "Time:" << start.elapsed();
    return 0;
}
