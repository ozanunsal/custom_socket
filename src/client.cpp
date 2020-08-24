#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include "connection.h"

using namespace std;


class Client: public Connection
{
	private:
		int sock;
		sockaddr_in server;
		int serverLength = sizeof(server);	
		struct hostent *s_server;
	public:

		Client(string addr, int port) : Connection(addr, port) 
		{ 
			// Socket creation
			this->sock = socket(AF_INET, SOCK_DGRAM, 0);
			if (this->sock < 0) {
				perror("Client:Error, no port provided\n");
				exit(1);
			}
			this->s_server = gethostbyname((const char*)&addr);
			if (this->s_server == NULL) {
				perror("Error no such host\n");
				exit(1);
			}

			// bzero((char *)&this->server, sizeof(this->server));
			this->server.sin_family = AF_INET;
			this->server.sin_port = htons(port); // little -big endian conversion
		}

		~Client(void)
		{
			close(this->sock);
		}

		ssize_t send(const char* msg, ssize_t size)
		{
			cout << "yes\n";
			return sendto(this->sock, msg, size + 1, 0, (struct sockaddr *)&this->server, sizeof(this->server));
		}

		ssize_t recv(char* buf, ssize_t size)
		{	cout << "no\n";
			return recvfrom(this->sock, buf, size, 0, (struct sockaddr *)&this->server, (socklen_t *)&this->serverLength);
		}
};


int main(int argc, char* argv[])
{
	Connection *p_connection = new Client("0.0.0.0", 9999);
	const char *s = "hello";
	ssize_t x = p_connection->send(s, 1024);
	return 0;
}
