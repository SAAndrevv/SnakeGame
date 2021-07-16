#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <iostream>
#include <thread>
#include <vector>
#include "Snake.h"


#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)


void getPacket();
void sendPacket(Direction);
void initSocket();
int startNet();

