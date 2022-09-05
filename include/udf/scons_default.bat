rem 
rem  Copyright 1987-2022 ANSYS, Inc. All Rights Reserved.
rem 
@echo off
set PYTHONHOME=%FLUENT_INC%/../commonfiles/CPython/3_7/winx64/Release/python
set PYTHONPATH=%FLUENT_INC%/../commonfiles/CPython/3_7/winx64/Release/python
set FLUENT_UDF_COMPILER=msvc
cl.exe
if not errorlevel 1 goto nmake_c
:clang_c
set FLUENT_UDF_COMPILER=clang
clang-cl --version
set FLUENT_UDF_CLANG=clangenv
if not errorlevel 1 goto scons_c
set FLUENT_UDF_CLANG=builtin
:scons_c
"%FLUENT_INC%/../commonfiles/CPython/3_7/winx64/Release/python/Scripts/scons" -s
:nmake_c
nmake /S
