#include "Client.h"

bool isHost = false;
SOCKET Connection;

Direction getPack;


void getPacket() {
	while (true) {
		recv(Connection, (char*)&getPack, sizeof(getPack), NULL);
	}

}

void sendPacket(Direction pack) {
	
	send(Connection, (char*)&pack, sizeof(pack), NULL);
	//Sleep(500);
		
}


void initSocket() {
	isHost = true;

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);
	

	Connection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
	

	std::thread thr1(getPacket);
	thr1.detach();

}


int startNet() {

	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server.\n";
		std::cout << "Initialization Socket...\n";

		initSocket();;

		std::cout << "Client Connected!\n";
		return 1;
	}
	else {
		std::cout << "Connected!\n";

		std::thread thr1(getPacket);
		thr1.detach();

		return 0;
	}

}