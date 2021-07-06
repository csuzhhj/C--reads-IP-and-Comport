#pragma once
#include "string.h"
#include "stdio.h"
#include <vector>  
#include <string>  
#include <atlbase.h>
#include<iostream>
using namespace std;
char* wideCharToMultiByte(wchar_t* pWCStrKey)
{
    //��һ�ε���ȷ��ת�����ֽ��ַ����ĳ��ȣ����ڿ��ٿռ�
    int pSize = WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), NULL, 0, NULL, NULL);
    char* pCStrKey = new char[pSize + 1];
    //�ڶ��ε��ý�˫�ֽ��ַ���ת���ɵ��ֽ��ַ���
    WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), pCStrKey, pSize, NULL, NULL);
    pCStrKey[pSize] = '\0';
    return pCStrKey;

    //�����Ҫת����string��ֱ�Ӹ�ֵ����
    //string pKey = pCStrKey;
}

std::vector<std::string> getComPort()
{
    HKEY hKey;
    wchar_t portName[256], w_commName[256];
    std::vector<std::string> comName;
    //�򿪴���ע����Ӧ�ļ�ֵ  
    if (ERROR_SUCCESS == ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("Hardware\\DeviceMap\\SerialComm"), NULL, KEY_READ, &hKey))
    {
        int i = 0;
        int mm = 0;
        DWORD  dwLong, dwSize;
        while (TRUE)
        {
            dwLong = dwSize = sizeof(portName);
            //ö�ٴ���
            if (ERROR_NO_MORE_ITEMS == ::RegEnumValue(hKey, i, portName, &dwLong, NULL, NULL, (PUCHAR)w_commName, &dwSize))
            {
                break;
            }
            char* commName = wideCharToMultiByte(w_commName);
            comName.push_back(commName);
            delete[] commName;
            i++;
        }
        //�ر�ע���
        RegCloseKey(hKey);
    }
    else
    {
        //MessageBox(NULL, "���ļ������ע�����û��HKEY_LOCAL_MACHINE:Hardware\\DeviceMap\\SerialComm��", "����", MB_OK);
    }
    //���ش��ں�
    return comName;
}