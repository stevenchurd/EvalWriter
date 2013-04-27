// (C) Copyright Steven Hurd 2013

#include "filelogger.h"
#include <string>
#include <iostream>
#include <fstream>
#include <QDateTime>
#include <QStandardPaths>
#include <QDir>
#include <iostream>

FileLogger* FileLogger::s_inst = NULL;
std::string FileLogger::s_defaultFile = "errors";

FileLogger::FileLogger(std::string filename)
{
    QDir dir = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    if(!dir.exists())
    {
        dir.mkpath(dir.path());
    }

    // create and open file
    file.open(dir.path().toStdString() + "/" + filename, std::ios::app);
}


FileLogger::~FileLogger()
{
    // close file
    file.close();
}

FileLogger* FileLogger::getInst(std::string filename)
{
    if(s_inst == NULL)
        s_inst = new FileLogger(filename);

    return s_inst;
}

FileLogger* FileLogger::getInst(void)
{
    if(s_inst == NULL)
        s_inst = getInst(s_defaultFile);

    return s_inst;
}

void FileLogger::log(std::string msg)
{
    file << QDateTime::currentDateTime().toString().toStdString() << " " << msg << std::endl;
}
