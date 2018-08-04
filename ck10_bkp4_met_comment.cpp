//	ck10.cpp : Defines the entry point for the console application.
//		
//	ck: managed to show directories, their subdirectories and
//		finally their respective files
//
//

#include "stdafx.h"
#include "ck10.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// for fopen(), etc.
#include <stdio.h>


// temporary
#include <time.h>

CWinApp theApp;

using namespace std;

//=======================================================================
// functies
//=======================================================================

double key=10;
double parent=10;
int depth=0;
int level[70];

//---
void level_mem(int par)
{	// 
	// par=0	initialisatie van level_mem, volledig
	// par=1	nieuw dieper level; sla key op in volgende variabele
	// par=2	terug naar naast hogere level
	// 
	

	if (par==0){
		// initialisatie array
		for(int n=0;n<=70;n++)
		{	
			level[n]=0;
		};

		int n0=0;
		level[n0]=key;
		printf("Level[%d]: %d \n",n0,level[n0]);
	};

	if (par==1){
		int n1=0;
		depth=depth + 1;
		n1=depth;
		level[n1]=key;
		printf("Level[%d]: %d \n",n1,level[n1]);
	};

	if (par==2){
		int n2=0;
		depth=depth - 1;
		n2=depth;
		//parent=level[depth+1];
		printf("Level[%d]: %d \n",n2,level[n2]);
		printf("\t parent=%d \n", parent);
	};

}		// end mem_level()

//---
void EnumerateFiles ()
{	
		WIN32_FIND_DATA efls;
		HANDLE hFind_efls = ::FindFirstFile (_T ("*.*"), &efls);
		//parent=key;

		if (hFind_efls != INVALID_HANDLE_VALUE) {
			do {
				if (!(efls.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
					key = key + 1;
					cout<<key<<"\t"<<parent<<"\t"<<efls.cFileName<<"\t"<<"file"<<"\t \n";
				}

			} while (::FindNextFile (hFind_efls, &efls));
			::FindClose (hFind_efls);
		}
		// printf("End of showing file(s).\n");
}

//---
void EnumerateFolders ()
{
	WIN32_FIND_DATA efld;
	HANDLE hFind_efld = ::FindFirstFile (_T ("*.*"), &efld);
	parent = key;

	if (hFind_efld != INVALID_HANDLE_VALUE) {
		do {
			// for showing the directories
			if (efld.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				CString name_efld = efld.cFileName;
				if (name_efld != _T(".") && name_efld != _T("..")) {
				
					key = key + 1;
					cout <<key<<"\t"<<parent<<"\t"<< efld.cFileName <<"\t"<<"dir"<<"\n";
					::SetCurrentDirectory (efld.cFileName);
					// parent wissel zeker
					// de diepere directory wordt ingestapt
					level_mem(1);
					// ck debug
					printf("Nu diepere directory; wissel parent.\n");
					
					EnumerateFolders();
					EnumerateFiles ();
					::SetCurrentDirectory (_T (".."));	
					// parent wissel zeker
					// wellicht nog in hogere lus aan het uitvoeren
					// ofwel waren er nog zuster directories op het naast hogere level
					printf("Nu terug naar hogere directory; wissel parent.\n");
					level_mem(2);

					// cout << " Enumerate Folders gaat in volgende lus met SetCurrentDir \"..\" ";
					printf("\n");					
				}
			}							
		} while (::FindNextFile (hFind_efld, &efld));
		::FindClose (hFind_efld);
	}
}



//=======================================================================
// main-programma
//=======================================================================

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	// initialisatie 
	level_mem(0);
	

	int nRetCode = 0;
	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		// the part for showing directories and files
		// GENERAL 
		::SetCurrentDirectory (_T ("C:\\DATA\\TESTEN"));
		parent=10;
		EnumerateFolders();
		parent=10;
		EnumerateFiles();	
	}

	// extra debug info
	printf("**Level[0]: %d \n",level[0]);
	printf("**Level[1]: %d \n",level[1]);
	printf("**Level[2]: %d \n",level[2]);
	printf("**Level[3]: %d \n",level[3]);
	printf("**Level[4]: %d \n",level[4]);

	return nRetCode;
}


