@echo off
setlocal enabledelayedexpansion

REM === Script location ===
set "SCRIPT_DIR=%~dp0"
REM Remove trailing backslash
if "%SCRIPT_DIR:~-1%"=="\" set "SCRIPT_DIR=%SCRIPT_DIR:~0,-1%"

REM === Project root = parent of tools ===
for %%I in ("%SCRIPT_DIR%\..") do set "PROJECT_ROOT=%%~fI"

set "CONTENT_ROOT=%PROJECT_ROOT%\Content\AiGenRpg"

echo Project root: "%PROJECT_ROOT%"
echo Content root: "%CONTENT_ROOT%"
echo.

REM === Create folders ===
call :MKDIR "%CONTENT_ROOT%\Maps\Worlds"
call :MKDIR "%CONTENT_ROOT%\Maps\Dev"

call :MKDIR "%CONTENT_ROOT%\Data\World\Catalogs"
call :MKDIR "%CONTENT_ROOT%\Data\LocationTypes\Forest"
call :MKDIR "%CONTENT_ROOT%\Data\LocationTypes\Hills"
call :MKDIR "%CONTENT_ROOT%\Data\LocationTypes\Plains"
call :MKDIR "%CONTENT_ROOT%\Data\LocationTypes\Swamp"
call :MKDIR "%CONTENT_ROOT%\Data\LocationTypes\Water"
call :MKDIR "%CONTENT_ROOT%\Data\Sites\Villages"
call :MKDIR "%CONTENT_ROOT%\Data\Sites\Ruins"
call :MKDIR "%CONTENT_ROOT%\Data\Sites\Camps"
call :MKDIR "%CONTENT_ROOT%\Data\Sites\Caves"
call :MKDIR "%CONTENT_ROOT%\Data\Simulation\TimeOfDay"
call :MKDIR "%CONTENT_ROOT%\Data\Simulation\Weather"
call :MKDIR "%CONTENT_ROOT%\Data\Simulation\Gameplay"

call :MKDIR "%CONTENT_ROOT%\PCG\Graphs"
call :MKDIR "%CONTENT_ROOT%\PCG\Helpers"

call :MKDIR "%CONTENT_ROOT%\Blueprints\World"
call :MKDIR "%CONTENT_ROOT%\Blueprints\Sites"
call :MKDIR "%CONTENT_ROOT%\Blueprints\NPC"

call :MKDIR "%CONTENT_ROOT%\Art\Meshes"
call :MKDIR "%CONTENT_ROOT%\Art\Materials"
call :MKDIR "%CONTENT_ROOT%\Art\Textures"
call :MKDIR "%CONTENT_ROOT%\Art\VFX"

call :MKDIR "%CONTENT_ROOT%\UI\Widgets"

echo.
echo Done. Restart UE editor to see folders in Content Browser if needed.
pause
exit /b 0

:MKDIR
set "P=%~1"
if not exist "%P%" (
    mkdir "%P%" >nul 2>&1
    if errorlevel 1 (
        echo [FAIL] "%P%"
        exit /b 1
    ) else (
        echo [OK]   "%P%"
    )
) else (
    echo [EXIST] "%P%"
)

REM Add .keep so Git tracks empty dirs
if not exist "%P%\.keep" (
    echo.>"%P%\.keep"
)
exit /b 0
