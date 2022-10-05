

#include <windows.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <time.h>
#include <iostream>
#include <string>
#include <wininet.h>
#include <stdio.h>
#include <Iphlpapi.h>
#include <Assert.h>
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib,"wininet.lib")
#pragma warning(disable: 4018)

using namespace std;

#include "Connect HDSN.h"

inline std::string trim_right(const std::string &source, const std::string& t = " ")
{
	std::string str = source;
	return str.erase(str.find_last_not_of(t) + 1);
}

inline std::string trim_left(const std::string& source, const std::string& t = " ")
{
	std::string str = source;
	return str.erase(0, source.find_first_not_of(t));
}

inline std::string trim(const std::string& source, const std::string& t = " ")
{
	std::string str = source;
	return trim_left(trim_right(str, t), t);
}

std::string IntToStr(int n)
{
	std::ostringstream result;
	result << n;
	return result.str();
}
string MyRandomString(void)
{
	string Agent;
	SYSTEMTIME st;
	GetLocalTime(&st);
	if (st.wHour<10)Agent = "0" + IntToStr(st.wHour);
	else Agent = IntToStr(st.wHour);

	if (st.wMinute<10)Agent = Agent + "0" + IntToStr(st.wMinute);
	else Agent = Agent + IntToStr(st.wMinute);

	if (st.wSecond<10) Agent = Agent + "0" + IntToStr(st.wSecond);
	else Agent = Agent + IntToStr(st.wSecond);

	if (st.wDayOfWeek<10)Agent = Agent + "0" + IntToStr(st.wDayOfWeek);
	else Agent = Agent + IntToStr(st.wDayOfWeek);
	return Agent;
}

char* GetMAC()
{
	PIP_ADAPTER_INFO AdapterInfo;
	DWORD dwBufLen = sizeof(AdapterInfo);
	char *mac_addr = (char*)malloc(17);

	AdapterInfo = (IP_ADAPTER_INFO *) malloc(sizeof(IP_ADAPTER_INFO));
	if (AdapterInfo == NULL)
	{
		printf("Error allocating memory needed to call GetAdaptersinfo\n");
	}
	if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == ERROR_BUFFER_OVERFLOW)
	{
		AdapterInfo = (IP_ADAPTER_INFO *) malloc(dwBufLen);
		if (AdapterInfo == NULL)
		{
			printf("Error allocating memory needed to call GetAdaptersinfo\n");
		}
	}
	if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == NO_ERROR)
	{
		PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;// Contains pointer to current adapter info
		do {
			sprintf(mac_addr, "%02X:%02X:%02X:%02X:%02X:%02X",
			pAdapterInfo->Address[0], pAdapterInfo->Address[1],
			pAdapterInfo->Address[2], pAdapterInfo->Address[3],
			pAdapterInfo->Address[4], pAdapterInfo->Address[5]);
			printf("Address: %s, mac: %s\n", pAdapterInfo->IpAddressList.IpAddress.String, mac_addr);
			return mac_addr;

			printf("\n");
			pAdapterInfo = pAdapterInfo->Next;        
		} while(pAdapterInfo);                        
	}
	free(AdapterInfo);
}

HINTERNET hInternet, hFile1, hFile2, hFile3;
DWORD ReadSize;
char output[6];
char output2[10];
char outputt[10];
string strSerial1;
string strSerial2;
string strSerialMAC;
string HostServer;
string HostServer2;
string HostServer3;

int OpenServer()
{
	struct tm * current_tm;
	time_t current_time;
	time(&current_time);
	current_tm = localtime(&current_time);
	DiskInfo *di;
	di = new DiskInfo(0);
	di->LoadDiskInfo();
	strSerial1 = di->SerialNumber();
	strSerialMAC = GetMAC();
	strSerial2 = trim(strSerial1);
	HostServer  = "http://ssn-team.usa.cc/Page/PointBlank/data-expired.php?e=" /*XorStr<0xEE,90,0xE9F6A680>("\86\9B\84\81\C8\DC\DB\83\9F\87\80\D4\90\9A\88\94\9C\90\67\6E\70\2D\71\76\67\29\6B\6A\25\6F\69\68\3F\6A\72\72\76\22\24\20\72\24\7C\2D\2D\7A\78\7B\2A\2C\41\43\43\15\42\41\10\10\1C\4C\12\1B\48\1C\4A\4C\03\04\54\1C\50\54\42\56\15\5C\42\4B\55\4F\5B\5B\6E\31\2A\33\7B\20\7B"+0xE9F6A680).s*/+ strSerialMAC;
	HostServer2  = "http://ssn-team.usa.cc/Page/PointBlank/data-exp.php?e=" + strSerialMAC;

	hInternet = InternetOpenA("Some USER-AGENT", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL);
	hFile1 = InternetOpenUrlA(hInternet, HostServer.c_str(), NULL, NULL, INTERNET_FLAG_RELOAD, NULL);
	hFile2 = InternetOpenUrlA(hInternet, HostServer2.c_str(), NULL, NULL, INTERNET_FLAG_RELOAD, NULL);
	return 0;
}

char* hdsn()
{
DiskInfo *di;
di = new DiskInfo(0);
di->LoadDiskInfo();
strSerial1 = di->SerialNumber();
strSerial2 = trim(strSerial1);
char *logbuf = new char[ 256 ];
 sprintf(logbuf,XorStr<0x32,3,0x60834143>("\x17\x40"+0x60834143).s,di->SerialNumber());
return logbuf;
}
