@echo off
cd /d %~dp0\cpp\alineamiento_global
g++ -o needlman_wunsh.exe needlman_wunsh.cpp
needlman_wunsh.exe %1 %2
