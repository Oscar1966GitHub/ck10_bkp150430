REM **************************************************
REM *
REM *  clean_fls.bat
REM *  140611_2053
REM *
REM * Moet te runnen zijn vanuit de naasthogere directory (project-hoofddirectory)
REM * en moet te runnen zijn vanuit de Debug sub-directory
REM *
REM **************************************************

del *.sdf
del *.opensdf

del *.tlog
del *.sdf
del *.idb
del *.obj
del *.pch
del *.pdb
del *.bsc
del *.sbr
del *.CppClean.log
del *.lastbuildstate
del *.res


del \Debug\*.tlog
del \Debug\*.sdf
del \Debug\*.idb
del \Debug\*.obj
del \Debug\*.pch
del \Debug\*.pdb
del \Debug\*.bsc
del \Debug\*.sbr
del \Debug\*.CppClean.log
del \Debug\*.lastbuildstate
del \Debug\*.res
