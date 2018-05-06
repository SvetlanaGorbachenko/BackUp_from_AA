#pragma once

#include "Definitions.h"

class BackUp;
class Array
{
public:
	Array(int nSize);
	Array(const int* pAr, int nSize);
	Array(const Array & R);
	~Array();
	Array & operator = (const Array & R);

	void push_back(int a);
	void Show();	
	void showAsSymbols(); 
	void setBackUp(BackUp * pBackUp);
	//@ return error code
	int save();
	int initFromFile();

private:
	
	int m_nSize, m_iCurInd;
	int *m_pAr;
	BackUp * m_pBackUp;
	void addMemory();
};