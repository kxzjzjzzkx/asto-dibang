#pragma once
#include "stdafx.h"

/*
	��ȡ�ܼ��Լ����㾻��

	gw			ë��
	tare		Ƥ��
	nw			����
	price		����(����)
	totalPrice	�ܼ�(���� �� ����)
*/
void getTotalPrice(char* gw, char* tare,char* nw,char* price,char* totalPrice)
{
	double total = atof(gw);
	double lost = atof(tare);
	double last = total - lost;
	sprintf(nw, "%f", last);
	sprintf(tare, "%f", lost);
	double priceMoney = atof(price);
	sprintf(price, "%f", priceMoney);
	double totalMoney = last * priceMoney;
	totalMoney = round(totalMoney * 100) / 100;
	sprintf(totalPrice, "%f", totalMoney);
}

void bulidNewIccode(char* iccode) {
	time_t tt = time(NULL);//��䷵�ص�ֻ��һ��ʱ���
	tm* t = localtime(&tt);
	int randInt = (rand() % 90) + 10;
	sprintf(iccode, "%d%02d%02d%02d%02d%02d%d",
		t->tm_year + 1900,
		t->tm_mon + 1,
		t->tm_mday,
		t->tm_hour,
		t->tm_min,
		t->tm_sec, randInt);
}
//
///*
//	��ʼ�� com�˿����ݵĶ�ȡ׼��
//
//*/
//void initPort(CSerialPort mySerialPort, CSerialPort mySerialPort2) {
//	//
//	/*��ʼ���߳�ʵʱͬ��������Ϣ*/
//	string sqlString = SQL_EQSET_SELECT_ALL;
//	char sql[200];
//	DBUtils db;
//	strcpy(sql, sqlString.c_str());
//	db.getRecordRet(sql);
//	while (!db.HX_pRecordset->adoEOF)
//	{
//		_variant_t var = db.HX_pRecordset->GetCollect("eq_type");
//		if (var.vt == VT_NULL) {
//			continue;
//		}
//		string strType = _com_util::ConvertBSTRToString((_bstr_t)var);
//		var = db.HX_pRecordset->GetCollect("eq_com");
//		string strCom = "";
//		if (var.vt != VT_NULL) {
//			strCom = _com_util::ConvertBSTRToString((_bstr_t)var);
//		}
//		var = db.HX_pRecordset->GetCollect("eq_btl");
//		string strBtl = "";
//		if (var.vt != VT_NULL) {
//			strBtl = _com_util::ConvertBSTRToString((_bstr_t)var);
//		}
//		char message[200];
//		if (strType == "1") {
//			strCom = strCom.replace(strCom.find("COM"), 3, "");
//			int selcom = atoi(strCom.c_str());
//			int btl = atoi(strBtl.c_str());
//			if (!mySerialPort.InitPort(selcom, btl, 'N', 8, 1, NULL) || selcom < 1 || btl< 1)
//			{
//				/*sprintf(message, "��1(com%d��)�쳣����������ԣ�", selcom);
//				MessageBoxA(NULL, message, "��Ϣ", 0);*/
//			}
//			else
//			{
//				mySerialPort.isClose = false;
//				/*sprintf(message, "��1(com%d��)����������", selcom);
//				MessageBoxA(NULL, message, "��Ϣ", 0);*/
//			}
//		}
//		else if (strType == "2") {
//			strCom = strCom.replace(strCom.find("COM"), 3, "");
//			int selcom = atoi(strCom.c_str());
//			int btl = atoi(strBtl.c_str());
//			if (!mySerialPort2.InitPort(selcom, btl, 'N', 8, 1, EV_RXCHAR) || selcom < 1 || btl< 1)
//			{
//				/*sprintf(message, "��2(com%d��)�쳣����������ԣ�", selcom);
//				MessageBox(NULL, message, TEXT("��Ϣ"), 0);*/
//			}
//			else
//			{
//				mySerialPort2.isClose = false;
//				/*sprintf(message, "��2(com%d��)����������", selcom);
//				MessageBox(NULL, message, TEXT("��Ϣ"), 0);*/
//			}
//		}
//		db.HX_pRecordset->MoveNext();
//	}
//	db.ExitConnect();
//	//
//}
//
