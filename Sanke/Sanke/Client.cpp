#include "Client.h"

bool isHost = false;
SOCKET Connection;

Packet getPack;


void getPacket() {
	while (true) {
		size_t t;
		
		recv(Connection, (char*)&t, sizeof(t), NULL);
		getPack.posX.resize(t);
		recv(Connection, (char*)getPack.posX.data(), t * sizeof(short int), NULL);

		recv(Connection, (char*)&t, sizeof(t), NULL);
		getPack.posY.resize(t);
		recv(Connection, (char*)getPack.posY.data(), t * sizeof(short int), NULL);
		
		recv(Connection, (char*)&t, sizeof(t), NULL);
		recv(Connection, (char*)getPack.apple.data(), t * sizeof(short int), NULL);
		
		recv(Connection, (char*)&getPack.id, sizeof(int), NULL);

		recv(Connection, (char*)&getPack.dots, sizeof(int), NULL);

		recv(Connection, (char*)&t, sizeof(t), NULL);
		getPack.bonus.resize(t);
		for (int i = 0; i < t; ++i) {
			size_t tTmp;
			recv(Connection, (char*)&tTmp, sizeof(tTmp), NULL);
			recv(Connection, (char*)getPack.bonus[i].data(), tTmp * sizeof(short int), NULL);

		}
		
	}

}

void sendPacket(Packet pack) {
	
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

	send(Connection, (char*)&pack.dots, sizeof(int), NULL);

	int sizeBonus = pack.bonus.size();
	send(Connection, (char*)&sizeBonus, sizeof(sizeBonus), NULL);
	for (auto& bonus : pack.bonus) {
		int sizeArrayBonus = bonus.size();
		send(Connection, (char*)&sizeArrayBonus, sizeof(sizeArrayBonus), NULL);
		send(Connection, (char*)&bonus, sizeArrayBonus * sizeof(short int), NULL);

	}
		
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