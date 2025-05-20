@echo off
set BUILD_TYPE="Ninja"
set BUILD_SUFFIX=ninja

chcp 65001 >nul

set BUILD_FOLDER=build_%BUILD_SUFFIX%
set SOURCE_FOLDER=projects

if not exist %BUILD_FOLDER% mkdir %BUILD_FOLDER%

cd %BUILD_FOLDER%

cmake -G %BUILD_TYPE% ..\%SOURCE_FOLDER%
cmake --build .

echo.
echo === Проверка и копирование run_menu.bat ===
set FILE1=..\%SOURCE_FOLDER%\menu_task\run_menu.bat
if exist %FILE1% (
    echo [✅] Файл найден: %FILE1%
    if not exist .\menu_task mkdir .\menu_task
    copy %FILE1% .\menu_task >nul
    echo [✔] Скопирован в .\menu_task
) else (
    echo [❌] Файл не найден: %FILE1%
)

echo.
echo === Проверка и копирование run_test_sorting.bat ===
set FILE2=..\%SOURCE_FOLDER%\sorting_task\test\run_test_sorting.bat
if exist %FILE2% (
    echo [✅] Файл найден: %FILE2%
    if not exist .\sorting_task\test mkdir .\sorting_task\test
    copy %FILE2% .\sorting_task\test >nul
    echo [✔] Скопирован в .\sorting_task\test
) else (
    echo [❌] Файл не найден: %FILE2%
)

pause
