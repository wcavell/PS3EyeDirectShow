@echo off
net session >nul 2>&1
if not %errorLevel% == 0 (
    echo Error: Need run as Administrator to change camera number.
    pause >nul
    goto end
)

set /p DeviceCount=Enter camera number (1-8): 

:: Unregist previous setting
regsvr32 /u "C:\Program Files (x86)\PS3 Eye Universal Driver\PS3EyeSourceFilter.dll"
regsvr32 /u "C:\Program Files\PS3 Eye Universal Driver\PS3EyeSourceFilter64.dll"

:: Regist with new DeviceCount
regsvr32 /n /i:"%DeviceCount%" "C:\Program Files (x86)\PS3 Eye Universal Driver\PS3EyeSourceFilter.dll"
regsvr32 /n /i:"%DeviceCount%" "C:\Program Files\PS3 Eye Universal Driver\PS3EyeSourceFilter64.dll"

:end