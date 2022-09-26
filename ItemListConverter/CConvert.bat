@ECHO OFF
CLS
ECHO 1.itemlist_bin2csv
ECHO 2.itemlist_csv2bin
ECHO 3.mountdata_bin2csv
ECHO 4.mountdata_csv2bin
ECHO.

CHOICE /C 1234 /M "Entre com a opt:"

:: Note - list ERRORLEVELS in decreasing order
IF ERRORLEVEL 4 GOTO mountdata_csv2bin
IF ERRORLEVEL 3 GOTO mountdata_bin2csv
IF ERRORLEVEL 2 GOTO itemlist_csv2bin
IF ERRORLEVEL 1 GOTO itemlist_bin2csv

:itemlist_bin2csv
ItemListConverter.exe itemlist_bin2csv
GOTO End

:itemlist_csv2bin
ItemListConverter.exe itemlist_csv2bin
GOTO End

:mountdata_bin2csv
ItemListConverter.exe mountdata_bin2csv
GOTO End

:mountdata_csv2bin
ItemListConverter.exe mountdata_csv2bin
GOTO End

:End