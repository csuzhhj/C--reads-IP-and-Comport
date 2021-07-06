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
    //第一次调用确认转换后单字节字符串的长度，用于开辟空间
    int pSize = WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), NULL, 0, NULL, NULL);
    char* pCStrKey = new char[pSize + 1];
    //第二次调用将双字节字符串转换成单字节字符串
    WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), pCStrKey, pSize, NULL, NULL);
    pCStrKey[pSize] = '\0';
    return pCStrKey;

    //如果想要转换成string，直接赋值即可
    //string pKey = pCStrKey;
}

std::vector<std::string> getComPort()
{
    HKEY hKey;
    wchar_t portName[256], w_commName[256];
    std::vector<std::string> comName;
    //打开串口注册表对应的键值  
    if (ERROR_SUCCESS == ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("Hardware\\DeviceMap\\SerialComm"), NULL, KEY_READ, &hKey))
    {
        int i = 0;
        int mm = 0;
        DWORD  dwLong, dwSize;
        while (TRUE)
        {
            dwLong = dwSize = sizeof(portName);
            //枚举串口
            if (ERROR_NO_MORE_ITEMS == ::RegEnumValue(hKey, i, portName, &dwLong, NULL, NULL, (PUCHAR)w_commName, &dwSize))
            {
                break;
            }
            char* commName = wideCharToMultiByte(w_commName);
            comName.push_back(commName);
            delete[] commName;
            i++;
        }
        //关闭注册表
        RegCloseKey(hKey);
    }
    else
    {
        //MessageBox(NULL, "您的计算机的注册表上没有HKEY_LOCAL_MACHINE:Hardware\\DeviceMap\\SerialComm项", "警告", MB_OK);
    }
    //返回串口号
    return comName;
}