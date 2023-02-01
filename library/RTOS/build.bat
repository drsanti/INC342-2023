REM ######################################
REM ### Build RTOS
REM ######################################
REM # Asst.Prof.Dr.Santi Nuratch
REM # Embedded Computing and Control Lab.
REM # 21 February 2020
REM ######################################

@echo off


REM ######################################
REM ### Change to the current directory
REM ######################################
cd /d "%~dp0"


REM ######################################
REM ### Remove the previous files
REM ######################################
del /s /q "dist\libs"


REM ######################################
REM ### Create the RTOS library
REM ######################################
echo Building RTOS
ecc-pic24-cli -library libbuild.cfg


REM ######################################
REM ### Create the SYS library
REM ######################################
echo.
echo RTOS building completed.
echo.
TIMEOUT 10
