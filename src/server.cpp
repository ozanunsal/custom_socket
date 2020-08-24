#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "connection.h"

using namespace std;


class Server: public Connection
{
	private:
		int sock;
		sockaddr_in client;
		int clientLength = sizeof(client);
	public:

		Server(string addr, int port) : Connection(addr, port) 
		{ 
			this->sock = socket(AF_INET, SOCK_DGRAM, 0);
			if (this->sock < 0) {
				perror("Error, no port provided\n");
				exit(1);
			}
			sockaddr_in serverHint;
			serverHint.sin_addr.s_addr = INADDR_ANY;
			serverHint.sin_family = AF_INET;
			serverHint.sin_port = htons(port); // little -big endian conversion

			if (bind(this->sock, (struct sockaddr *) &serverHint, sizeof(serverHint)) < 0) {
				perror("Error on binding\n");
				exit(1);
			}
		}

		~Server(void)
		{
			close(this->sock);
		}

		ssize_t send(const char* msg, ssize_t size)
		{
			return sendto(this->sock, msg, size + 1, 0, (struct sockaddr *)&this->client, sizeof(this->client));
		}

		ssize_t recv(char* buf, ssize_t size)
		{
			return recvfrom(this->sock, buf, size, 0, (struct sockaddr *)&this->client, (socklen_t *)&this->clientLength);
		}
};

int main(void)
{
	cout << "Custom Socket Server Side....\n";
	Connection *p_connection = new Server("0.0.0.0", 9999);
	char buf[1024];
	while(1) {
		bzero(buf, 1024);
		int s = p_connection->recv(buf, 1024);
		if (s < 0) {
			perror("Error during receiving from client\n");
			continue;
		}
		cout << "Received msg: " << buf << endl;
	}

	return 0;
}
