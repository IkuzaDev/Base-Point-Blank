
#pragma once

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#define WIN64_LEAN_AND_MEAN
#define WIN64_EXTRA_LEAN

#include <windows.h>
#include <iostream>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <direct.h>
#include <fcntl.h>
#include <io.h>
#include <vector>
#include <rpc.h>
#include <rpcdce.h>
#include <stdio.h>
#include <iomanip>
#include <cstdlib>
#include <tlhelp32.h>
#include <process.h>
#include <shellapi.h>
#include "winsock.h"
#include <fstream>
#include <string>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <wininet.h>
#include <conio.h>
#include <tchar.h>
#include <Iphlpapi.h>
#include <Assert.h>
//#include "Microsoft.h"
#define PSAPI_VERSION 1

//EnumProcess
#include <Psapi.h>
#pragma comment(lib, "Psapi.lib")

//CreateToolHelp32Snapshot
#include <TlHelp32.h>
#pragma warning (disable:4309 4244 4996 4102 4305 4551 4715)

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment (lib, "wininet.lib")
#pragma comment(lib,"psapi.lib")
#pragma comment(lib,"Detours.lib")

//#define FebriZip AutoShot 0x1219B

#define RegardoCall(Function) CreateThread(0,0,(LPTHREAD_START_ROUTINE)Function,0,0,0);





