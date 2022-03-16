@echo off
cl /c /D UNICODE /EHsc *.cpp 
if %errorlevel%  gtr 0 goto :END
echo 编译成功，开始链接
link -dll *.obj *.res
echo ====链接完成====
goto :SUCCESS
 
:END
echo 编译失败
:SUCCESS