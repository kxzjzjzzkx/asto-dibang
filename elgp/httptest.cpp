#include <stdafx.h>
#include <WinInet.h>

#pragma comment(lib,"wininet.lib")

int main()
{
	//��һ��������12306��վ������
	LPCTSTR lpszAgent = L"WinInetGet/0.1";
	HINTERNET hInternet = InternetOpen( lpszAgent,
		INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	LPCTSTR lpszServerName = L"kyfw.12306.cn";
	INTERNET_PORT nServerPort = INTERNET_DEFAULT_HTTPS_PORT; // HTTPS�˿�443
	LPCTSTR lpszUserName = NULL; //�޵�¼�û���
	LPCTSTR lpszPassword = NULL; //�޵�¼����
	DWORD dwConnectFlags = 0;
	DWORD dwConnectContext = 0;
	HINTERNET hConnect = InternetConnect(hInternet,
		lpszServerName, nServerPort,
		lpszUserName, lpszPassword,
		INTERNET_SERVICE_HTTP,
		dwConnectFlags, dwConnectContext);
	if(hConnect == NULL)
	{
		return false;
	}

	//�ڶ���������12306��վ��¼��֤��ӿ�
	LPCTSTR lpszVerb = L"GET";
	LPCTSTR lpszObjectName = L"/otn/passcodeNew/getPassCodeNew.do?module=login&rand=sjrand";//L"/urchin.js";
	LPCTSTR lpszVersion = NULL;    // Ĭ��.
	LPCTSTR lpszReferrer = L"";   // û������ҳ
	LPCTSTR *lplpszAcceptTypes = NULL; // Accpet��������.
	DWORD dwOpenRequestFlags =  INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP |
		INTERNET_FLAG_KEEP_CONNECTION |
		INTERNET_FLAG_NO_AUTH |
		INTERNET_FLAG_NO_COOKIES |
		INTERNET_FLAG_NO_UI | 
		INTERNET_FLAG_SECURE | //��������HTTPS
		INTERNET_FLAG_RELOAD;
	DWORD dwOpenRequestContext = 0;
	//��ʼ��Request
	HINTERNET hRequest = HttpOpenRequest(hConnect, lpszVerb, lpszObjectName, lpszVersion,
		lpszReferrer, lplpszAcceptTypes,
		dwOpenRequestFlags, dwOpenRequestContext);

	//����Request
	BOOL bResult = HttpSendRequest(hRequest, NULL, 0, NULL, 0);
	//ʧ��
	if (!bResult) 
	{
		fprintf(stderr, "HttpSendRequest failed, error = %d (0x%x)\n",
			GetLastError(), GetLastError());
		return -2;
	}

	//����������ȡ���ؽ��
	//���HTTP Response Header��Ϣ
	DWORD dwInfoLevel = HTTP_QUERY_RAW_HEADERS_CRLF;
	DWORD dwInfoBufferLength = 2048;
	BYTE *pInfoBuffer = (BYTE *)malloc(dwInfoBufferLength+2);
	while (!HttpQueryInfo(hRequest, dwInfoLevel, pInfoBuffer, &dwInfoBufferLength, NULL))
	{
		DWORD dwError = GetLastError();
		if (dwError == ERROR_INSUFFICIENT_BUFFER)
		{
			free(pInfoBuffer);
			pInfoBuffer = (BYTE *)malloc(dwInfoBufferLength + 2);
		}
		else
		{
			fprintf(stderr, "HttpQueryInfo failed, error = %d (0x%x)\n",
				GetLastError(), GetLastError());
			break;
		}
	}
	pInfoBuffer[dwInfoBufferLength] = '\0';
	pInfoBuffer[dwInfoBufferLength + 1] = '\0';
	printf("%s", pInfoBuffer); //�����HttpQueryInfo����ĸ�ʽ��wchar_t �������InternetReadFile��һ��
	free(pInfoBuffer);

	//���HTTP Response �� Body, ������pngͼƬ������������
	DeleteFile(L"verifycode.png");
	DWORD dwBytesAvailable;
	while (InternetQueryDataAvailable(hRequest, &dwBytesAvailable, 0, 0))
	{
		BYTE *pMessageBody = (BYTE *)malloc(dwBytesAvailable+1);
		DWORD dwBytesRead;
		BOOL bResult = InternetReadFile(hRequest, pMessageBody,
			dwBytesAvailable, &dwBytesRead);
		if (!bResult)
		{
			fprintf(stderr, "InternetReadFile failed, error = %d (0x%x)\n",
				GetLastError(), GetLastError());
			break;
		}
		if (dwBytesRead == 0)
			break; // End of File.
		pMessageBody[dwBytesRead] = '\0';
		printf("%s", pMessageBody); //InternetReadFile������������ͨ��char. InternetReadFileEx �ƺ����п��ֽڰ汾��
		//MessageBox((LPCTSTR)(char*)pMessageBody);
		write_file("verifycode.png",(char*)pMessageBody,dwBytesRead);
		free(pMessageBody);
	}
	return 0;
}