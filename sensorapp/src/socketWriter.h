#ifndef SOCKETWRITER_H
#define SOCKETWRITER_H

#include <string>

class SocketWriter
{
public:
    SocketWriter();
    SocketWriter(int cl);
    void writeToSocket(std::string msg);
private:
    int cl;
};

#endif