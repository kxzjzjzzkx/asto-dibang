// CppConsole.cpp : �������̨Ӧ�ó������ڵ㡣
//

//#include "stdafx.h"
//#include <winhttp.h>
//#pragma comment(lib, "winhttp")

// ale.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>

#pragma comment(lib,"wininet.lib")

#include <iostream>
#include <cstdio>
#include <WinInet.h>
#include <string>
#include <list>
#include <queue> 
#include "DBInfo.h"

using namespace std;

class HttpUtils{
	public:
		
		~HttpUtils(void);
		
		string httpGet(_TCHAR* url);
		
		int httpPost(_TCHAR* domain,_TCHAR* url);
		
		// ��������Json���� [3/14/2017/shike]
		//DBInfo ParseJsonInfo(const string &strJsonInfo);
		// ��ȡlist ����
		//list<DBInfo> HttpUtils::ParseJsonInfoForList(const string &strJsonInfo);
		queue<DBInfo> HttpUtils::ParseJsonInfoForList(const string &strJsonInfo);
	protected:
		

		// �رվ�� [3/14/2017/shike]
		void Release();

		// �ͷž�� [3/14/2017/shike]
		//void ReleaseHandle( HINTERNET& hInternet );

		// ����URL��ַ [3/14/2017/shike]
		//void ParseURLWeb( std::string strUrl, std::string& strHostName, std::string& strPageName, WORD& sPort);

		// UTF-8תΪGBK2312 [3/14/2017/shike]
		//char* UtfToGbk(const char* utf8);
	private:
		/*HINTERNET            m_hSession;
		HINTERNET            m_hConnect;
		HINTERNET            m_hRequest;
		HttpInterfaceError    m_error;*/
};
