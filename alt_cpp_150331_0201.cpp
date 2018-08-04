// Todo: zie prj_log.txt
// 
//      - haal de lege regels hieronder weg
//		- maak een main-functie en diverse functies op basis van onderstaande
//		- hernoem deze file naar ck10.cpp en archiveer de vorige ck10.cpp file.
//		- build het geheel
//		- verwijder het nieuw toegevoegde ConsoleApplication1_new etc.

void PrintFindData(WIN32_FIND_DATA *findData)

{

      // If it's a directory, print the name

      if( findData->dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY )

      {

            CString strMessage;

            strMessage.Format("Directory: %s",findData->cFileName);

            AfxMessageBox(strMessage);

      }

      // else if it's a file, print name and size

      else

      {

            CString strMessage;

            strMessage.Format("This Is a File\n%s \n Size is:%d",findData->cFileName,findData->nFileSizeLow);

            AfxMessageBox(strMessage);

      }

} 

///////////////////////////////

void ListDirectoryContents(char *fileMask) 


{

      HANDLE fileHandle;

      WIN32_FIND_DATA findData;

 

      // get first file

      fileHandle = FindFirstFile( fileMask,&findData );

      if( fileHandle != INVALID_HANDLE_VALUE )

      {

            PrintFindData( &findData );

 

            // loop on all remeaining entries in dir

            while( FindNextFile( fileHandle,&findData ) )

            {

                  PrintFindData( &findData );

            }

      }

 

      FindClose( fileHandle );

}
//////////////////////////////////
ListDirectoryContents( "*.*" );
//////////////////////////////////
HANDLE FindFirstFile(LPTSTR searchFile,LPWIN32_FIND_DATA findData); 
//////////////////////////////////
typedef struct _WIN32_FIND_DATA {

    DWORD dwFileAttributes;

    FILETIME ftCreationTime;

    FILETIME ftLastAccessTime;

    FILETIME ftLastWriteTime;

    DWORD    nFileSizeHigh;

    DWORD    nFileSizeLow;

    DWORD    dwReserved0;

    DWORD    dwReserved1;

    TCHAR    cFileName[ MAX_PATH ];

    TCHAR    cAlternateFileName[ 14 ];

} WIN32_FIND_DATA; 
//////////////////////////////////
BOOL FindNextFile(HANDLE findFile,LPWIN32_FIND_DATA finData); 

//////////////////////////////////
BOOL FindClose(HANDLE findFile);

//////////////////////////////////
void PrintFindData1(WIN32_FIND_DATA *findData)

{

      /*cout << "\t";

      cout << findData->cFileName;

      cout << "\t(" << findData->nFileSizeLow << ")";

      cout << endl;*/

      CString strMessage;

      strMessage.Format("%s\nFile size: %d",findData->cFileName,

                   findData->nFileSizeLow);

      AfxMessageBox(strMessage);

} 

//////////////////////////////////
void ListDirectoryContents1(char *dirName,char *fileMask)

{

      char *fileName;

      char curDir[ 256 ];

      char fullName[ 256 ];

      HANDLE fileHandle;

      WIN32_FIND_DATA findData;

 

      // save current dir so it can restore it

      if( !GetCurrentDirectory( 256, curDir) )

            return;

 

      // if the directory name is neither . or .. then

      // change to it, otherwise ignore it

      if( strcmp( dirName, "." ) &&

            strcmp( dirName, ".." ) )

      {

            if( !SetCurrentDirectory( dirName ) )

                  return;

      }

      else

            return;

 

      // print out the current directory name

      if( !GetFullPathName( fileMask, 256, fullName,&fileName ) )

            return;

      CString strInfo;

      strInfo.Format("Directory - %s",fullName);

      AfxMessageBox(strInfo);

 

      // Loop through all files in the directory

      fileHandle = FindFirstFile( fileMask,

            &findData );

      while ( fileHandle != INVALID_HANDLE_VALUE )

      {

            // If the name is a directory,

            // recursively walk it. Otherwise

            // print the file's data

            if( findData.dwFileAttributes &

                  FILE_ATTRIBUTE_DIRECTORY )

            {

                  ListDirectoryContents1( findData.cFileName,

                        fileMask );

            }

            else

                  PrintFindData1( &findData );

 

            // loop thru remaining entries in the dir

            if (!FindNextFile( fileHandle, &findData ))

                  break;

      }

 

      // clean up and restore directory

      FindClose( fileHandle );

      SetCurrentDirectory( curDir );

} 

//////////////////////////////////
char curDir[ 256 ]; 


 

      if( !GetCurrentDirectory( 256, curDir ) )

      {

            AfxMessageBox("Could not Get the Current Directory");

            return;

      }

 

      // List all files, starting with the

      // current directory

      ListDirectoryContents1( curDir, "*.*" );


//////////////////////////////////

//////////////////////////////////


//////////////////////////////////


//////////////////////////////////

