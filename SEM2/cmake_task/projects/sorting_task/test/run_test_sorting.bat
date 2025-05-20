@echo off
chcp 65001 >nul

echo === Запуск CTest (подробно) ===
ctest -j 4 -V
if errorlevel 1 (
    echo [❌] Некоторые тесты завершились с ошибками.
) else (
    echo [✅] Все тесты прошли успешно.
)

pause