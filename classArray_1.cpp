// classArray_1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdlib.h>


#include "Array.h"
#include "BackUp.h"
#include "Definitions.h"

int main()
{
	{

		/*BackUp bu("arrdata.ard");
		bu.Write(0, 0);*/

#define AssignOperTest
#ifdef AssignOperTest
		int iChoice = 0;
		cout << "if WRITE file mode = enter 1" << endl;
		cout << "if READ  file mode = enter 2" << endl;
		cin >> iChoice;

		BackUp * pBU = new BackUp("arrdata.ard");

		if (1 == iChoice)
		{
			Array ar(5);
			for (int i = 0; i < 20; ++i)
				ar.push_back(rand() % 26 + 'A');
			ar.showAsSymbols();

			
			ar.setBackUp(pBU);
			int iErrCode = ar.save();
			if (ERR_ACCESS == iErrCode)
			{
				cout << "ERROR!! Cannot create/write file" << endl;
			}
			else
			{
				cout << "All int data was saved !!!" << endl;
			}
		}
		else
		{
			Array ar(0);
			ar.setBackUp(pBU);
			int iErrCode = ar.initFromFile();
			if (FILE_OK == iErrCode)
				ar.showAsSymbols();
			else
				cout << "Some error with file... "<< iErrCode << endl;

			for (int i = 0; i < 5; ++i)
				ar.push_back('W');
			ar.showAsSymbols();
		}
		delete pBU;
		/////////////////////////////////////   BACK_UP TEST ===========================

		//pBU->Write(0, 0);
		cout << "==============" << endl;

		/*Array ar2(2);
		for (int i = 0; i < 5; ++i)
			ar2.push_back(rand() % 100);
		ar2.Show();
		cout << "========= 1111111111111111  ==========" << endl;

		ar2 = ar;
		cout << "========= 2222222222222222  ==========" << endl;
		ar2.Show();*/

		/*Array ar2(0);
		ar2 = ar;
		ar2.Show();*/

		//Array ar2(ar);
		//ar2.Show();
		cout << "=======    before end  ============" << endl;
#endif //AssignOperTest

		
	}
	if (_CrtDumpMemoryLeaks())
		cout << "Memory leak !!! \n";
	else
		cout << "Memory ok !!! \n";

    return 0;
}

