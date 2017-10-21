#pragma once
#pragma once
#include "stdafx.h"
#include <string>
using namespace std;
//�����ֶ���
#define BLOCK0_EN  0x01
#define BLOCK1_EN  0x02
#define BLOCK2_EN  0x04
#define NEEDSERIAL 0x08
#define EXTERNKEY  0x10
#define NEEDHALT   0x20
#pragma hdrstop
#include <Mergemod.h>


/*
ic�����ݻ�ȡ
*/
void getIC(char* str, char* tempStr) {
	int j = 0;
	;	for (size_t i = 0; i < strlen(tempStr); i++)
	{
		if (j >= 16)
		{
			break;
		}
		if (i % 2 == 0) {
			continue;
		}
		str[j] = tempStr[i];
		j++;
	}
	str[j] = '\0';
}

void convertUnCharToStr(char* str, unsigned char* UnChar, int ucLen)
{
	int i = 0;
	char tempStr[100];
	for (i = 0; i < ucLen; i++)
	{
		//��ʽ����str,ÿunsigned char ת���ַ�ռ��λ��%xд��%Xд��  
		sprintf(tempStr + i * 2, "%02x", UnChar[i]);
	}
	getIC(str, tempStr);
}

void convertStrToUnChar(char* str, unsigned char* UnChar)
{
	int i = strlen(str), j = 0, counter = 0;
	char c[2];
	unsigned int bytes[2];

	for (j = 0; j < i; j += 2)
	{
		if (0 == j % 2)
		{
			c[0] = str[j];
			c[1] = str[j + 1];
			sscanf(c, "%02x", &bytes[0]);
			UnChar[counter] = bytes[0];
			counter++;
		}
	}
	return;
}

void ReadICCard(char* result,bool* hasRead,char* errorMsg) {
	unsigned char status;//��ŷ���ֵ
	unsigned char myareano;//����
	unsigned char authmode;//�������ͣ���A�����B����
	unsigned char myctrlword;//������
	unsigned char mypicckey[6];//����
	unsigned char mypiccserial[4];//�����к�
	unsigned char mypiccdata[48]; //�����ݻ���
	unsigned char(__stdcall *piccreadex)(unsigned char ctrlword, unsigned char *serial, unsigned char area, unsigned char keyA1B0, unsigned char *picckey, unsigned char *piccdata0_2);
	//�ж϶�̬���Ƿ����
	char filePath[200];
	GetModuleFileName(NULL, filePath, 200);
	string FileName = filePath;
	FileName = FileName.replace(FileName.find("gb.exe"), 6, "");
	FileName += "OUR_MIFARE.dll";
	WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile(FileName.c_str(), &wfd);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		sprintf(errorMsg,"%s","OUR_MIFARE.dll�ļ���ʧ");
		//MessageBox(NULL, TEXT("OUR_MIFARE.dll�ļ���ʧ"), TEXT("����"), NULL);
		return ;
	}
	FindClose(hFind);
	//CloseHandle(hFind);
	//��ȡ����
	HINSTANCE hDll;
	hDll = LoadLibrary(FileName.c_str());
	piccreadex = (unsigned char(__stdcall *)(unsigned char, unsigned char *, unsigned char, unsigned char, unsigned char *, unsigned char *))GetProcAddress(hDll, "piccreadex");
	//������ָ��,�����ֵĺ�����鿴����˾��վ�ṩ�Ķ�̬��˵��
	myctrlword = BLOCK0_EN + BLOCK1_EN + BLOCK2_EN + EXTERNKEY;
	//ָ������
	myareano = 8;//ָ��Ϊ��8��
				 //��������ģʽ
	authmode = 1;//����0��ʾ��A������֤���Ƽ���A������֤
				 //ָ������
	mypicckey[0] = 0xff;
	mypicckey[1] = 0xff;
	mypicckey[2] = 0xff;
	mypicckey[3] = 0xff;
	mypicckey[4] = 0xff;
	mypicckey[5] = 0xff;
	status = piccreadex(myctrlword, mypiccserial, myareano, authmode, mypicckey, mypiccdata);
	FreeLibrary(hDll);
	hasRead[0] = false;
	//�������趨�ϵ㣬Ȼ��鿴mypiccserial��mypiccdata��
	//������ piccreadex�����ɶ��������кŵ� mypiccserial�����������ݵ�mypiccdata��
	//������Ա�����Լ�����Ҫ����mypiccserial��mypiccdata �е������ˡ�
	//�����غ���
	switch (status)
	{
	case 0:
		hasRead[0] = true;
		convertUnCharToStr(result, mypiccdata, 48);
		break;
	case 8:
		sprintf(errorMsg, "%s", "�뽫�����ڸ�Ӧ��");
	//	MessageBox(hDlg, TEXT("�뽫�����ڸ�Ӧ��"), TEXT("��ʾ"), NULL);
		break;
	case 23:
		sprintf(errorMsg, "%s", "�쳣��û�з���IC���豸");
		//MessageBox(hDlg, TEXT("�쳣��û�з���IC���豸"), TEXT("��ʾ"), NULL);
		break;
	}
	//���ؽ���
	/*
	#define ERR_REQUEST 8//Ѱ������
	#define ERR_READSERIAL 9//�����������
	#define ERR_SELECTCARD 10//ѡ������
	#define ERR_LOADKEY 11//װ���������
	#define ERR_AUTHKEY 12//������֤����
	#define ERR_READ 13//��������
	#define ERR_WRITE 14//д������
	#define ERR_NONEDLL 21//û�ж�̬��
	#define ERR_DRIVERORDLL 22//��̬������������쳣
	#define ERR_DRIVERNULL 23//��������������δ��װ
	#define ERR_TIMEOUT 24//������ʱ��һ���Ƕ�̬��û�з�ӳ
	#define ERR_TXSIZE 25//������������
	#define ERR_TXCRC 26//���͵�CRC��
	#define ERR_RXSIZE 27//���յ���������
	#define ERR_RXCRC 28//���յ�CRC��
	*/
}