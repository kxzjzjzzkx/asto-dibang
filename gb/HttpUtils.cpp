// CppConsole.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"

#pragma comment(lib, "json1.lib")

#include "HttpUtils.h"
#include <fstream>
#include <cassert>
#include "json/json.h"
#include <atlconv.h>




#define X "\r\n"
#define URL "http://www.zz91.com/doStatusLogin.htm"  //�����ַ
#define _COM "www.zz91.com" //��վ��ַ
#define _COM_URL "/doStatusLogin.htm"      //����ҳ��
#define PORT 0x50   //�˿ں�80
#define _POST "username=kongsj&password=123456" //POST��������
#define MAXSIZE 4096

//ÿ�ζ�ȡ���ֽ���
#define READ_BUFFER_SIZE        4096

HttpUtils::~HttpUtils(void)
{
    
}

string HttpUtils::httpGet(_TCHAR* url){
	string result;
	HINTERNET hSession = InternetOpen(_T("UrlTest"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	wchar_t *pwText = NULL;
	if(hSession != NULL){
		HINTERNET hHttp = InternetOpenUrl(hSession, url, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
        if (hHttp != NULL)
        {
            //wprintf_s(_T("%s\n"), _T("http://www.zz91.com"));
			BYTE Temp[MAXSIZE] ={0};
			char szBuffer[READ_BUFFER_SIZE + 1] = {0};
            ULONG Number = 1;
            while (Number > 0)
            {
                InternetReadFile(hHttp, szBuffer, MAXSIZE - 1, &Number);
                szBuffer[Number] = '\0';

				//
				DWORD dwNum = MultiByteToWideChar(CP_ACP, 0, szBuffer, -1, NULL, 0);    //����ԭʼASCII����ַ���Ŀ
				pwText = new wchar_t[dwNum];                                                //����ASCII����ַ�������UTF8�Ŀռ�
				MultiByteToWideChar(CP_UTF8, 0, szBuffer, -1, pwText, dwNum);           //��ASCII��ת����UTF8
				//
                //printf("%s", szBuffer);
				//result = Temp;
				//string temp;
				USES_CONVERSION;
				char *psText = W2A(pwText);
				//sprintf(psText, "%s", pwText);
				//psText = new char[dwNum];
				//WideCharToMultiByte(CP_OEMCP,NULL,pwText,-1,psText,dwNum,NULL,FALSE);
				result.append(psText);
            }
			InternetCloseHandle(hHttp);
            hHttp = NULL;
        }
        InternetCloseHandle(hSession);
        hSession = NULL;
	}
	return result;
}

string HttpUtils::string_To_UTF8(const string & str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//һ��Ҫ��1����Ȼ�����β��
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}

int HttpUtils::httpPost(_TCHAR* domain,_TCHAR* url,_TCHAR* data){
	//ԭʼЭ��ͷ
    char _HTTP_ARAC[] = "Accept: */*\r\n"\
                        "Referer: "\
                        "URL"\
                        "X"\
                        "Accept-Language: zh-cn\r\n"\
                        "Content-Type: application/x-www-form-urlencoded\r\n\r\n";
    char _HTTP_POST[] = _POST;
    char _HTTP_File[1024] ={0};
    //cout << "�ύHTTPЭ��ͷ��" << _HTTP_ARAC << endl;
    //cout << "�ύPOST���ݣ�" << _POST << endl;
    HINTERNET Inte = InternetOpenA ("Mozilla/4.0 (compatible; MSIE 9.0; Windows NT 6.1)", 1, "" ,"" ,0);    //��ʼ��Wininet������һ��HTTP����
    if(0 == Inte){
        InternetCloseHandle(Inte);
        //cout << "error InternetOpen" << endl;
    }
    HINTERNET Connect = InternetConnectA (Inte, domain,PORT, "","" , 3, 0, 0);    //��������վ����
      if(0 == Connect){
        InternetCloseHandle(Inte);
        InternetCloseHandle(Connect);
        //cout << "error InternetConnect" << endl;
    }
	HINTERNET HttpOpen = HttpOpenRequestA (Connect, "POST", url, "HTTP/1.1", NULL,NULL,1, 0);  //����վ��������������ҳ��
      if(0 == HttpOpen){
        InternetCloseHandle(Inte);
        InternetCloseHandle(Connect);
        InternetCloseHandle(HttpOpen);
        //cout << "error HttpOpenRequest" << endl;
    }

    BOOL bo = HttpSendRequestA(HttpOpen, _HTTP_ARAC, strlen(_HTTP_ARAC), data, strlen (data));  //����վ��������������HTTPЭ���POST��������
    if(bo == false){
        InternetCloseHandle(Inte);
        InternetCloseHandle(Connect);
        InternetCloseHandle(HttpOpen);
		char error[200];
		sprintf(error, "%s", GetLastError());
        //cout << "error HttpSendRequest" << endl;
    }
    DWORD y = 0;
     if(!InternetReadFile (HttpOpen, _HTTP_File, 1024, &y)){    //��ȡHTTP��Ӧ��Ϣ
        InternetCloseHandle(Inte);
        InternetCloseHandle(Connect);
        InternetCloseHandle(HttpOpen);
        //cout << "error InternetReadFile" << endl;
    }else{
        //printf("%s",_HTTP_File);    //��ӡ�õ�����Ӧ��Ϣ
    }
	return 0;
}

// ����Json���� [11/8/2016/shike]
//DBInfo HttpUtils::ParseJsonInfo(const string &strJsonInfo)
//{
//    Json::Reader reader;                                    //����json��Json::Reader
//    Json::Value value;
//	DBInfo dbInfo;
//	//���Դ�����������
//    if (!reader.parse(strJsonInfo, value))  
//    {  
//        //CVLog.LogMessage(LOG_LEVEL_ERROR,"[CXLDbDataMgr::GetVideoGisData] Video Gis parse data error...");
//    }
//	//dbInfo.setLang(value["city"].asString());
//	dbInfo.setId(value["flag"].asInt());
//	int ipt = value["flag"].asInt();
//    if (!value["list"].isNull())        
//    {
//        int nSize = value["result"].size();
//        for(int nPos = 0; nPos < nSize; ++nPos)                //������������б���
//        {
//            //PGCARDDEVDATA stru ;
//            //stru.strCardName        = value["result"][nPos]["tollgateName"].asString();
//            //stru.strCardCode        = value["result"][nPos]["tollgateCode"].asString();
//            //std::string strCDNum    = value["result"][nPos]["laneNumber"].asString();    //����:��������
//            //stru.nLaneNum            = atoi(strCDNum.c_str());
//            //std::string strLaneDir    = value["result"][nPos]["laneDir"].asString();        //����:��������,���й���ת��
//            //stru.strLaneDir            = TransformLaneDir(strLaneDir);
//            //stru.dWgs84_x            = value["result"][nPos]["wgs84_x"].asDouble();
//            //stru.dWgs84_y            = value["result"][nPos]["wgs84_y"].asDouble();
//            //stru.dMars_x            = value["result"][nPos]["mars_x"].asDouble();
//            //stru.dMars_y            = value["result"][nPos]["mars_y"].asDouble();
//            //lstCardDevData.emplace_back(stru);
//        }
//    }
//	return dbInfo;
//}
//
//// ����Json���� ��list
//queue<DBInfo> HttpUtils::ParseJsonInfoForList(const string &strJsonInfo)
//{
//    Json::Reader reader;                                    //����json��Json::Reader
//    Json::Value value;
//	queue<DBInfo> result;
//	list<DBInfo> result1;
//	//���Դ�����������
//    if (!reader.parse(strJsonInfo, value))  
//    {
//		// �����������Ϊ��
//		//return result;
//    }
//    if (!value["list"].isNull())        
//    {
//        int nSize = value["list"].size();
//        for(int nPos = 0; nPos < nSize; ++nPos)                //������������б���
//        {
//			DBInfo obj;
//			//obj.setGmtCreated(value["list"][nPos]["postTime"]["time"].asString());
//			obj.setCId(value["list"][nPos]["id"].asInt());
//            //PGCARDDEVDATA stru ;
//            //stru.strCardName        = value["result"][nPos]["tollgateName"].asString();
//            //stru.strCardCode        = value["result"][nPos]["tollgateCode"].asString();
//            //std::string strCDNum    = value["result"][nPos]["laneNumber"].asString();    //����:��������
//            //stru.nLaneNum            = atoi(strCDNum.c_str());
//            //std::string strLaneDir    = value["result"][nPos]["laneDir"].asString();        //����:��������,���й���ת��
//            //stru.strLaneDir            = TransformLaneDir(strLaneDir);
//            //stru.dWgs84_x            = value["result"][nPos]["wgs84_x"].asDouble();
//            //stru.dWgs84_y            = value["result"][nPos]["wgs84_y"].asDouble();
//            //stru.dMars_x            = value["result"][nPos]["mars_x"].asDouble();
//            //stru.dMars_y            = value["result"][nPos]["mars_y"].asDouble();
//            //lstCardDevData.emplace_back(stru);
//			//result.push_back(obj);
//			result.push(obj);
//        }
//    }
//	return result;
//}