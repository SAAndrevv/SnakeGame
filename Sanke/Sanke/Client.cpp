#include "Client.h"

bool isHost = false;
SOCKET Connection;

Packet getPack;


void getPacket() {
	int bit;
	while (true) {
		size_t t;
		size_t t1;
		
		//recv(Connection, (char*)&t, sizeof(t), NULL);
		
		//if()
		
			//recv(Connection, (char*)&getPack.posXApple, sizeof(int), NULL);
			//recv(Connection, (char*)&getPack.posYApple, sizeof(int), NULL);
		

		//recv(Connection, (char*)&t, sizeof(t), NULL);
		//recv(Connection, (char*)getPack.apple, t, NULL);
		
		
		recv(Connection, (char*)&t, sizeof(t), NULL);
		getPack.posX.resize(t);
		recv(Connection, (char*)getPack.posX.data(), t * sizeof(short int), NULL);

		recv(Connection, (char*)&t, sizeof(t), NULL);
		getPack.posY.resize(t);
		recv(Connection, (char*)getPack.posY.data(), t * sizeof(short int), NULL);
		//recv(Connection, (char*)&id, sizeof(int), NULL);
		
		recv(Connection, (char*)&t1, sizeof(t), NULL);
		recv(Connection, (char*)getPack.apple.data(), t1 * sizeof(short int), NULL);
		//recv(Connection, (char*)&getPack, sizeof(getPack), NULL);
		recv(Connection, (char*)&getPack.id, sizeof(int), NULL);

		

		//recv(Connection, (char*)&bit, sizeof(int), NULL);
		//std::cout << getPack.apple[1] <<  " get" << std::endl;
		
	}

}

void sendPacket(Packet pack) {
	//int bit = 1;
	//send(Connection, (char*)&s, sizeof(s), NULL);
	//
	//if (pack.id == 1) {
		
		//send(Connection, (char*)&pack.posXApple, sizeof(int), NULL);
		//send(Connection, (char*)&pack.posYApple, sizeof(int), NULL);
	//}
	//

	int sizeX = pack.posX.size();
	send(Connection, (char*)&sizeX, sizeof(sizeX), NULL);
	send(Connection, (char*)pack.posX.data(), sizeX * sizeof(short int), NULL);

	int sizeY = pack.posY.size();
	send(Connection, (char*)&sizeY, sizeof(sizeY), NULL);
	send(Connection, (char*)pack.posY.data(), sizeY * sizeof(short int), NULL);

	int sizeApple = pack.apple.size();
	send(Connection, (char*)&sizeApple, sizeof(sizeApple), NULL);
	send(Connection, (char*)pack.apple.data(), sizeApple * sizeof(short int), NULL);

	send(Connection, (char*)&pack.id, sizeof(int), NULL);
	
	

	//send(Connection, (char*)&bit, sizeof(int), NULL);


	//std::cout << pack.apple[1] << " send" << std::endl;


	//send(Connection, (char*)&pack, sizeof(pack), NULL);
	//Sleep(500);
	//
		
}

//short int* convertMas(std::vector<short int> mas) {
	//short int* tmp = new short int[mas.size() + 1];

//}


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
	//getPack.posXApple = 0;
	//getPack.posYApple = 0;

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