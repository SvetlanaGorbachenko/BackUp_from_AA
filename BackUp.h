#pragma once

#include "Definitions.h"


class BackUp
{
	char m_sFileName[_MAX_PATH];
public:
	BackUp(const char * sFileName);
	//~BackUp();
	int Write(const void * pData, int nBytes);
	/*
		pnReadedBytes [out] de facto size of file
		pErrCode [out]   returns to the caller error of file operation 
		@return array of readed bytes
	*/
	void * Read(int * pnReadedBytes, int * pErrCode);
};

