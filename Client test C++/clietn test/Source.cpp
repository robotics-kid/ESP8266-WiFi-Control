#include <iostream>
#include <string>
#pragma comment(lib,"ws2_32.lib")
#include <winsock2.h>
#include <cmath> 
#include <mutex> 
#include<thread>

#pragma warning(disable: 4996)


std::mutex mtx;
SOCKET Connection;

int main() {
	char rec[100] = { 0 };
	//Socket connection
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("192.168.4.1");
	addr.sin_port = htons(80);
	addr.sin_family = AF_INET;

	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeofaddr) != 0) {
		std::cout << "Error: Failed connect to server.\n";
		exit(1);
	}
	std::cout << "Connected!\n";
	//////////////////////
	////////////
	int i = 0;
	char send1[] = "FoViBalTLight;EFF:1;HUE:255;SAT:255;VAL:0!";
	char send2[] = "FoViBalTLight;EFF:1;HUE:0;SAT:255;VAL:0!";
	int recvByt = 1;
	while (true) {
		Sleep(3000);
		int bytesSend = send(Connection, send1, sizeof(send1), NULL	);
		std::cout << "Send: " << bytesSend << std::endl;
		Sleep(3000);
		bytesSend = send(Connection, send2, sizeof(send2), NULL);
		std::cout << "Send: " << bytesSend << std::endl;
		Sleep(3000);
	}
		//send(Connection, "FoViBalTLight;EFF:1;HUE:0;SAT:255;VAL:0\n", sizeof("FoViBalTLight;EFF:1;HUE:0;SAT:255;VAL:0\n"), NULL);
		//Sleep(1000);
		//Sleep(20);


	
	//////

	

}


