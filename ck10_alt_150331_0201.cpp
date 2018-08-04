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
