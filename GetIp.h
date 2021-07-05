#pragma once
#ifndef CMDEXC_H
#define CMDEXC_H

#include<string>
#include<windows.h>
#include<iostream>
using namespace std;
#pragma comment(lib,"ws2_32.lib")

string getip() {
	string m_LocalIP1;//IP��ַ��ʱ���� 
	string m_LocalIP2;
	LPCSTR psz;
	//��ñ��ؼ������ 
	char PCnameBuffer[128];
	string m_PCname;
	//��ʼ��:�������ʼ�������´��뽫�޷�ִ�� 
	WSAData data;
	if (WSAStartup(MAKEWORD(1, 1), &data) != 0)
	{
		/*cout << "��ʼ������,�޷���ȡ������Ϣ..." << endl;*/
	}
	else
		if (0 == gethostname(PCnameBuffer, 128))
		{
			m_PCname = PCnameBuffer;
			//��ñ���IP��ַ 
			struct hostent* pHost;
			int i;
			pHost = gethostbyname(PCnameBuffer);//pHost���ص���ָ���������б� 
			for (i = 0; pHost != NULL && pHost->h_addr_list[i] != NULL; i++)
			{
				if (i == 1)
				{
					psz = inet_ntoa(*(struct in_addr*)pHost->h_addr_list[1]);//�õ�ָ��ip��psz����
					m_LocalIP2 = psz;
				}
				else
				{
					psz = inet_ntoa(*(struct in_addr*)pHost->h_addr_list[0]);//�õ�ָ��ip��psz���� 
					m_LocalIP1 = psz;
				}
			}
		}
	return m_LocalIP1;
}

#endif // CMDEXC_H