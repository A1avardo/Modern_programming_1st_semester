@echo off
g++ -std=c++17 -Wall main.cpp menu_functions.cpp menu_items.cpp -o menu_app.exe && menu_app.exe
pause