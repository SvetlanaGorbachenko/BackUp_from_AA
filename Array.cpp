#include "stdafx.h"
#include "Array.h"
#include "BackUp.h"

Array::Array(int nSize) : m_nSize(nSize), m_iCurInd(0), m_pAr(0), m_pBackUp(0)
{
	if (nSize <= 0)
		m_nSize = 0;
	else {
		m_pAr = new int[m_nSize];
	}
	cout << "Array (int)" << this << ' ' << m_nSize << endl;
}

Array::Array(const int* pAr, int nSize) : m_nSize(nSize), m_iCurInd(0), m_pAr(0), m_pBackUp(0)
{
	if (nSize <= 0)
		m_nSize = 0;
	else
	{
		m_pAr = new int[m_nSize];
		for (int i = 0; i < m_nSize; ++i)
		{
			m_pAr[i] = pAr[i];
			m_iCurInd = i;
		}
	}
	cout << "Array(const int* pAr, int nSize)" << this << ' ' << m_nSize << ' ' << m_pAr << endl;
}

Array::Array(const Array & R) : m_nSize(R.m_nSize), m_iCurInd(R.m_iCurInd), m_pAr(0), m_pBackUp(0)
{
	if (R.m_pAr != 0) 
	{
		m_pAr = new int[m_nSize];
		memcpy(m_pAr, R.m_pAr, sizeof(int) * m_iCurInd);
	}
	cout << "Array (const Array &R) " << this << "from " << &R << ' ' << m_nSize << endl;
 }

Array ::~Array()
{
	cout << "befdelete " << this << ' ' << m_nSize << endl;
	if (m_pAr != 0)
		delete[] m_pAr;
	cout << "af delete " << this << ' ' << m_nSize << endl;
}

Array & Array::operator = (const Array & R)
{
	if (this != &R)
	{
		//delete previous resource
		//allocate new one
		//copy all data from R
		char sBuff[sizeof(Array)];
		Array Temp(R);
		memcpy(sBuff, this, sizeof(Array));
		memcpy(this, &Temp, sizeof(Array));
		memcpy(&Temp, sBuff, sizeof(Array));
	}
	return *this;
}

void Array::push_back(int a) 
{
	if (m_iCurInd == m_nSize)
		addMemory();
	m_pAr[m_iCurInd++] = a;
}

void Array::addMemory() 
{
	cout << "Array::addMemory()begin " << this << ' ' << m_nSize << ' ' << m_pAr << endl;
	if (0 == m_nSize)
	{
		m_nSize = 2;
		m_pAr = new int[m_nSize];
	}
	else if (m_nSize == 1)
	{
		m_nSize = 2;
		int* pTemp = new int[m_nSize];
		pTemp[0] = m_pAr[0];
		delete[] m_pAr;
		m_pAr = pTemp;
	}
	else
	{
		int nNewSize = m_nSize * 2;
		int* pTemp = new int[nNewSize];
		memcpy(pTemp, m_pAr, sizeof(int)*m_nSize);
		delete[] m_pAr;
		m_pAr = pTemp;
		m_nSize = nNewSize;
	}
	cout << "Array::addMemory()end " << this << ' ' << m_nSize << ' ' << m_pAr << endl;
}

void Array::Show ()
{
	//cout << m_pAr << endl;
	for (int i = 0; i < m_iCurInd; ++i)
		cout << m_pAr[i]<<' ';
	cout << endl;
}
void Array::showAsSymbols()
{
	for (int i = 0; i < m_iCurInd; ++i)
		cout <<(char) m_pAr[i] << ' ';
	cout << endl;
}

void Array::setBackUp(BackUp * pBackUp)
{
	m_pBackUp = pBackUp;
}

int Array::save()
{
	int iRet = FILE_OK;
	if (0 == m_pBackUp)
	{
		iRet = ERR_BACK_UP_ISNT_INITIALIZED;
	}
	else
	{
		//:td if there are no data to save
		int nBytes = sizeof(int) * m_iCurInd;
		iRet = m_pBackUp->Write(m_pAr, nBytes);
	}

	return iRet;
}
int Array::initFromFile()
{
	int iRet = FILE_OK;
	if (0 == m_pBackUp)
	{
		iRet = ERR_BACK_UP_ISNT_INITIALIZED;
	}
	else
	{
		int nReaded = 0;
		int iErrCode = ERR_EMPTY_FILE;
		void * pVChunk = m_pBackUp->Read(&nReaded, &iErrCode);
		if (pVChunk != 0)
		{
			m_pAr = (int *)pVChunk;
			m_iCurInd = m_nSize = nReaded / sizeof(int);
			//iRet = iErrCode;
		}
		iRet = iErrCode;
	}
	
	return iRet;
}