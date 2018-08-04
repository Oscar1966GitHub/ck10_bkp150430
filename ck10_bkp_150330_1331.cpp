//	ck10.cpp : Defines the entry point for the console application.
//
//
//	ck: wizard:	console app with MFC support
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


/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;


/// start
void EnumerateFiles ()
{
		WIN32_FIND_DATA fd4;
		HANDLE hFind4 = ::FindFirstFile (_T ("*.*"), &fd4);

		if (hFind4 != INVALID_HANDLE_VALUE) {
			do {
				if (!(fd4.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
					TRACE (_T ("%s\n"), fd4.cFileName);
					cout << fd4.cFileName ;
					printf("\n");
				}

			} while (::FindNextFile (hFind4, &fd4));
			::FindClose (hFind4);
		}
		printf("End of showing files\n");
		printf("\n");

}

void EnumerateFolders ()
{
	WIN32_FIND_DATA fd3;
	HANDLE hFind3 = ::FindFirstFile (_T ("*.*"), &fd3);

	if (hFind3 != INVALID_HANDLE_VALUE) {
		do {
			// for showing the directories
			if (fd3.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				CString name3 = fd3.cFileName;
				if (name3 != _T(".") && name3 != _T("..")) {
					TRACE (_T ("%s\n"), fd3.cFileName);
					cout << fd3.cFileName;
					printf("\t");
					printf("\n");
					::SetCurrentDirectory (fd3.cFileName);
					EnumerateFiles ();
					EnumerateFolders();
					::SetCurrentDirectory (_T (".."));			
				}
			}							
		} while (::FindNextFile (hFind3, &fd3));
		::FindClose (hFind3);
	}
}


/// end

//=======================================================================


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
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
		// the part for showing files
		WIN32_FIND_DATA fd;
		HANDLE hFind = ::FindFirstFile (_T ("*.*"), &fd);

		if (hFind != INVALID_HANDLE_VALUE) {
			do {
				if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
					TRACE (_T ("%s\n"), fd.cFileName);
					cout << fd.cFileName ;
					printf("\n");
				}

			} while (::FindNextFile (hFind, &fd));
			::FindClose (hFind);
		}
		printf("End of showing files\n");
		printf("\n");


		// the part for showing directories
		WIN32_FIND_DATA fd2;
		HANDLE hFind2 = ::FindFirstFile (_T ("*.*"), &fd2);

		if (hFind2 != INVALID_HANDLE_VALUE) {
			do {
				if ((fd2.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
					TRACE (_T ("%s\n"), fd2.cFileName);
					cout << fd2.cFileName ;
					printf("\n");
				}

			} while (::FindNextFile (hFind2, &fd2));
			::FindClose (hFind2);
		}
		printf("End of showing directories\n");
		printf("\n");

		// GENERAL 
		::SetCurrentDirectory (_T ("C:\\Data"));
		EnumerateFolders();
	}

	return nRetCode;
}


