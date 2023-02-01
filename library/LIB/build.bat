REM ######################################
REM ### Build BSP & SYS
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
REM ### Create the BSP library
REM ######################################
echo Building BSP
ecc-pic24-cli -library libbuild.cfg

cd /d "%~dp0"
echo.
echo BSP and SYS building completed.
echo.
TIMEOUT 10
