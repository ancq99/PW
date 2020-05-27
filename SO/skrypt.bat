@echo off
echo Skrypt na Systemy Operacyjne

echo ---------------------------------
echo ^> Anczok Bartlomiej 307330       ^<
echo ^> Laboratoria 3                  ^<
echo ^> Skrypt na Systemy Operacyjne   ^<
echo -----------------------------------

call :info_powloka 

rem Sprawdzamy czy uzytkownik chce pomoc jeli tak to wyswieltamy jak nie to dalej
goto :pomoc
:w_pomoc

rem Sprawdzamy poprawnosc wprowadzonych danych
goto :s_liczba_arg
:w_liczba_arg

REM Jeśli powłoka to TCC to wykonujemy skrypt, w innym przypadku pomoc
if "%nazwa_powloka%"=="TCC" goto :funkcje

echo Skrypt jest przeznaczony do dzialania w TCC
goto :wyswietl_pomoc

:info_powloka
for %%n in (%COMSPEC%) DO (
    set nazwa_powloka=%%~nn
)

rem TCC
if "%@abs[-1]"=="1" (
    set nazwa_powloka=TCC
)

rem DOS
if %nazwa_powloka% NEQ TCC (
    if %nazwa_powloka% NEQ ^cmd (
        set nazwa_powloka=COMMAND
    )
)
echo ------------------------------------------------------------- &echo:
echo Zawartosc zmiennej COMSPEC to:
echo %COMSPEC% & echo:
echo -------------------------------------------------------------- & echo:
echo Sykrypt zostal odpalony w  %nazwa_powloka%
call :wersja_powloka
echo ------------------------------------------------------------- &echo:
Exit /B 

rem ---------------------------------------------------------------

rem wyświetlenie wersji powloki
:wersja_powloka
if "%nazwa_powloka%"=="cmd" (
    echo Wersja powloki:
    ver
    echo:
)
if "%nazwa_powloka%"=="TCC" (
    echo Wersja powloki:
    ver
    echo:
)
if "%nazwa_powloka%"=="PowerShell" (
    echo Wersja powloki:
    $PSVersionTable
    echo:
)
if "%nazwa_powloka%"=="powershell" (
    echo Wersja powloki:
    $PSVersionTable
    echo:
)
if "%nazwa_powloka%"=="POWERSHELL" (
    echo Wersja powloki:
    $PSVersionTable
    echo:
)
if "%nazwa_powloka%"=="command" (
    ver
    echo:
)
if "%nazwa_powloka%"=="COMMAND" (
    ver
    echo:
)
Exit /B 

rem----------------------------------------------------------------

rem wyswietlanie pomocy
:pomoc
if "%1"=="/?" goto :wyswietl_pomoc
if "%1"=="/h" goto :wyswietl_pomoc
if "%1"=="/help" goto :wyswietl_pomoc
if "%1"=="-?" goto :wyswietl_pomoc
if "%1"=="-h" goto :wyswietl_pomoc
if "%1"=="-help" goto :wyswietl_pomoc
goto :w_pomoc

:wyswietl_pomoc
echo POMOC
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ & echo:
echo Uzycie:
echo skrypt.bat (-h ^| /h ^| -? ^| /h ^| -help ^| /help) - wyswietla pomoc
echo skrypt.bat -(e ^| exec) "komenda + flagi" - uruchamia dana komende i zwraca jej kod
echo skrypt.bat -(es ^| execstr) "komenda + flagi" n - zwraca n-ta linie uruchamianej komendy
echo skrypt.bat -(t ^| timer)  "dodatkowe opcje" - uruchamia timer, szczegoly dodaj "/?"
echo:
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
Exit /B 

:timer_help
echo POMOC TIMER
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ & echo:
echo Uzycie: 
echo (-t^|-timer) [/1 /2 /3 /4 /5 /6 /7 /8 /9 /10 /C /L /M /N /Q /S] [ON ^| OFF] [/n /C /Q /S] 
echo ON:  Restartuje timer 
echo OFF:  Zatrzymuje timer 
echo /n zmiania jednostke timera (dostępne: ns, us, ms, s, m, h) 
echo /C CTRL+C 
echo /Q wyjscie 
echo /S podzial  & echo:
echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
Exit /B 

rem ---------------------------------------------------------------

rem Sprawdzamy ilosc argumantow, w celu poprawnego uruchomienia programu
:s_liczba_arg
set liczba_arg=0
for %%x in (%*) do Set /A liczba_arg+=1
goto :w_liczba_arg

:funkcje
rem jeśli występuje argument to przechodzi do danej funkcji w innym przypadku wyswietla blad
if "%1"=="-e" goto :ex
if "%1"=="-exec" goto :ex

if "%1"=="-es" goto :exstr
if "%1"=="-execstr" goto :exstr

if "%1"=="-t" goto :tim
if "%1"=="-timer" goto :tim

echo: & echo Bledne argumenty & echo:
goto :wyswietl_pomoc
Exit /B

rem ----------------------------------------------------------------

:ex

if %liczba_arg% EQ 0 (
    echo Nieprawidlowa liczba argumentow.
    echo Spodziewana ilosc: 1 & echo:
    goto :wyswietl_pomoc
)
echo Wynik dzialania komendy "%~2" 
echo %@exec[%~2]

Exit /B

rem ----------------------------------------------------------------

:exstr
echo Funkcja execstr nie instnieje w wersji 14

Exit /B

rem ----------------------------------------------------------------

:tim

if "%~2"=="/?" goto :timer_help

echo %@exec[timer %~2];

Exit /B