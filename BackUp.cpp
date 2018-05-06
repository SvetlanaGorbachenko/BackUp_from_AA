#include "stdafx.h"
#include "BackUp.h"


BackUp::BackUp(const char * sFileName)
{
	int nLength = strlen(sFileName) + 1;
	if (nLength > _MAX_PATH)   //:td 2 handle this situation
		return;
	memcpy(m_sFileName, sFileName, nLength);
}


//BackUp::~BackUp()
//{
//}

int BackUp::Write(const void * pData, int nBytes)
{
	int iRet = ERR_ACCESS;  // error code

	FILE * f;
	errno_t err = fopen_s(&f, m_sFileName, "wb");
	if (NULL == f)
	{
		//:td  find out real cause of error
	}
	else
	{
		int nWritten = fwrite(pData, 1, nBytes, f);
		// assure, that all bytes was written
		// if not, do it in cycle
		fclose(f);
		iRet = FILE_OK;
	}
	//cout << "int BackUp::Write(const void * pData, int nBytes) "<<m_sFileName << endl;
	//cout << "int BackUp::Write(const void * pData, int nBytes) " << endl;


	return iRet;
}
/*
pnReadedBytes [out] de facto size of file
pErrCode [out]   returns to the caller error of file operation
@return pointer to readed block of any data  == array of readed bytes
*/
void * BackUp::Read(int * pnReadedBytes, int * pErrCode)
{
	void * pRet = 0;
	FILE * f;
	*pErrCode = ERR_FILE_NOT_EXISTS;
	errno_t err = fopen_s(&f, m_sFileName, "rb");
	if (NULL == f)
	{
		//:td  find out real cause of error
		*pErrCode = ERR_FILE_NOT_EXISTS;
	}
	else
	{
		fseek(f, 0, SEEK_END);
		int nBytes = ftell(f);
		fseek(f, 0, SEEK_SET);
		if (0 == nBytes)
		{
			*pErrCode = ERR_EMPTY_FILE;
			fclose(f);
		}
		else
		{
			pRet = new char[nBytes]; //:td 2 here can be exception - there is not enough memory
			int nReaded = fread(pRet, 1, nBytes, f);
			//:td check - if all data was readed
			*pnReadedBytes = nReaded;
			*pErrCode = FILE_OK;
			fclose(f);
		}
	}
	

	return pRet;
}
