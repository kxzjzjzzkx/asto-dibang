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
	double priceMoney = atof(price);
	double totalMoney = last * priceMoney;
	totalMoney = round(totalMoney * 100) / 100;
	sprintf(totalPrice, "%f", totalMoney);
}
