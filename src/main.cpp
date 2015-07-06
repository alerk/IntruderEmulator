#include <iostream>

#include "Socket/ServerSocket.h"
#include "Socket/SocketException.h"

#define PORT 112233

using namespace std;


int main(void)
{
	char buffer[5];
	int counter = 0;
	buffer[0] = 0xAA;
	buffer[1] = 0x55;
	buffer[2] = 0x00;
	try
	{
		ServerSocket listenServer(PORT);
		while(true)
		{
			ServerSocket sendToSocket;
			cout << "Waiting for client!" << endl;
			listenServer.accept(sendToSocket);
			cout << "Client connected!" << endl;
			while(true)
			{
				try
				{
					buffer[2] = (unsigned char)(counter>>8);
					buffer[3] = (unsigned char)(counter & 0x00FF);
					buffer[4] = 0x01;
					sendToSocket.send(buffer, 5);
				}
				catch(SocketException &e)
				{
					cout << "Error at sending data: " << e.description() << endl;
				}
				sleep(1);//between every sending message
			}
			sleep(1);//for client reconnecting
		}
	}
	catch(SocketException &e)
	{
		cout << "Error at creating server: " << e.description() << endl;
//		sleep(1);
	}
	return 0;
}
