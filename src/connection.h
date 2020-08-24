#include <iostream>
#include <cstdio>

using namespace std;

class Connection
{
    private:
        string addr;
        int port;
    public:
        Connection(string addr="0.0.0.0", int port=0)
        {
            this->addr = addr;
            this->port = port;
        }

        virtual ssize_t send(const char* msg, ssize_t size) = 0;
        virtual ssize_t recv(char* buf, ssize_t size) = 0;
};