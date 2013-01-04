// (C) Copyright Steven Hurd 2013

#ifndef FILELOGGER_H
#define FILELOGGER_H

#include <string>
#include <fstream>

class FileLogger
{
public:
    virtual ~FileLogger();

    void log(std::string msg);

    static FileLogger* getInst(std::string filename);
    static FileLogger* getInst(void);

private:
    FileLogger(std::string filename);

    std::ofstream file;


    static std::string s_defaultFile;
    static FileLogger* s_inst;

};

#endif // FILELOGGER_H
