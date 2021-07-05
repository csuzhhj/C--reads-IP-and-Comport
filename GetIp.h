#pragma once
#ifndef CMDEXC_H
#define CMDEXC_H

#include<string>
#include<windows.h>
#include<iostream>
using namespace std;
#pragma comment(lib,"ws2_32.lib")

string getip() {
	string m_LocalIP1;//IP地址临时变量 
	string m_LocalIP2;
	LPCSTR psz;
	//获得本地计算机名 
	char PCnameBuffer[128];
	string m_PCname;
	//初始化:如果不初始化，以下代码将无法执行 
	WSAData data;
	if (WSAStartup(MAKEWORD(1, 1), &data) != 0)
	{
		/*cout << "初始化错误,无法获取主机信息..." << endl;*/
	}
	else
		if (0 == gethostname(PCnameBuffer, 128))
		{
			m_PCname = PCnameBuffer;
			//获得本地IP地址 
			struct hostent* pHost;
			int i;
			pHost = gethostbyname(PCnameBuffer);//pHost返回的是指向主机的列表 
			for (i = 0; pHost != NULL && pHost->h_addr_list[i] != NULL; i++)
			{
				if (i == 1)
				{
					psz = inet_ntoa(*(struct in_addr*)pHost->h_addr_list[1]);//得到指向ip的psz变量
					m_LocalIP2 = psz;
				}
				else
				{
					psz = inet_ntoa(*(struct in_addr*)pHost->h_addr_list[0]);//得到指向ip的psz变量 
					m_LocalIP1 = psz;
				}
			}
		}
	return m_LocalIP1;
}

#endif // CMDEXC_H