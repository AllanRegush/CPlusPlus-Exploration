@echo off

mkdir ..\build
pushd  ..\build
echo $pwd
cl -Zi ..\Win32UI\main.cpp user32.lib gdi32.lib
popd
