## This fork is aiming to: 
1. Fix various issues on original repo.
2. Update the latest drivers and libraries.
3. Add more features to make PS3Eye more user friendly under Windows 10 environment.
   
## Right now it provides the following features:
- Totally get rid of CLEye and use libusb-win32 driver as base instead.
  - No more janky setup.
  - Compatible with other applications such as [Opentrack](https://github.com/opentrack/opentrack) and [PSMoveService](https://github.com/psmoveservice/PSMoveService).
- Updated PS3Eye driver to using latest version provided by opentrack
  - Alongside with previous modifications like BGRA/RGBA support and vertical flip fix.
- Updated Libusb to latest version.
- Fixed the DirectShow issue with Chrome, Discord, etc.
  - It finally shows on your web browser and Discord yay!
- Multiple camera devices support (up to 8 devices).
  - Default install setups one device only. See below section to configure device numbers.

## Installation
1. Following the driver installation tutorial [here](https://github.com/opentrack/opentrack/wiki/PS3-Eye-open-driver-instructions) provided by Opentrack.
2. Head to the [releases section](https://github.com/jkevin/PS3EyeDirectShow/releases) and download the installer. It will install both x86 and x64 DirectShow filters.
3. After installed you should be able to see "PS3 Eye Universal" appears on applications that supports DirectShow.
4. Profit.
5. For multiple camera devices, you can run C:\Program Files\PS3 Eye Universal Driver\ChangeCameraNumber.bat as adminAdministrator to change device number. Or you can run the following commands as administrator:

## Unregister then register 2 PS3Eye cameras (up to 8)
```
regsvr32 /u "C:\Program Files (x86)\PS3 Eye Universal Driver\PS3EyeSourceFilter.dll"
regsvr32 /u "C:\Program Files\PS3 Eye Universal Driver\PS3EyeSourceFilter64.dll"
regsvr32 /n /i:"2" "C:\Program Files (x86)\PS3 Eye Universal Driver\PS3EyeSourceFilter.dll"
regsvr32 /n /i:"2" "C:\Program Files\PS3 Eye Universal Driver\PS3EyeSourceFilter64.dll"
```

## TODO
- Microphone support?

## Reference
- Modern version of [DirectShow baseclasses](https://github.com/roman380/Windows-classic-samples/tree/directshow/Samples/Win7Samples/multimedia/directshow) by Ronan
- [PS3EYEDriver](https://github.com/opentrack/PS3EYEDriver) by Opentrack
- [obs-studio](https://github.com/obsproject/obs-studio) mainly the plugins/win-dshow section.
- [obs-virtual-cam](https://github.com/CatxFish/obs-virtual-cam/)
- [DirectShowで仮想カメラを自作しよう](https://qiita.com/HexagramNM/items/2311f025f3af758c83a0) for addressing the BGRA format issue.


If you enjoy this fork, feel free to buy me a [kofi](https://ko-fi.com/allancat) :3

Below is the original readme (outdated)

# PS3EyeDirectShow
Windows DirectShow source filter for the PS3 Eye Camera via WinUSB (32 / 64 bit)

This package is an extension of [https://github.com/inspirit/PS3EYEDriver/](https://github.com/inspirit/PS3EYEDriver/), which is itself a port of the PS3 Eye Linux driver to Windows. This project wraps that code into a DirectShow source filter so that it behaves like a USB camera with a native Windows driver. Any application that goes through the standard DirectShow API to connect to a webcam should (in theory) be able to use this driver. This code has only had limited testing so there may be compatibility issues with some apps.

## User Space WinUSB Based Driver
This project makes use of the generic WinUSB driver to communicate with the camera. This has several advantages and disadvantages compared to a native camera driver. The biggest advantage is all of the code runs in user space instead of kernel space. This means any flaws in this driver will only affect the program that's using the camera instead of crashing the entire operating system. The part that runs in kernel space is the WinUSB driver and it's a stable component provided by Microsoft. It provides a generic way for user space programs to communicate with the device.

Another big advantage of a user space driver is it's much easier to directly make use of other libraries such as libusb and the github project that this driver is based on.

On the other hand native camera drivers have slightly better performance. Also Windows will automatically make those cameras available via the DirectShow API (both 32 and 64 bit) as well as Windows Media Foundation. There isn't any need to provide a custom DirectShow or WMF source for a native camera.

## 32 / 64 bit
This project provides both a 32 bit and 64 bit source filter. Every application that uses a DirectShow camera must load its source filter library (usually a wrapper to a native camera provided by Microsoft). 32 bit applications require 32 bit libraries, and 64 bit applications require 64 bit libraries. Thus if the source filter is only provided as a 32 bit library the camera can only be used by 32 bit applications.

There's another PS3 Eye driver by [Code Laboratories](https://codelaboratories.com/) that seems to take a similar approach to this driver in that it provides a custom DirectShow source filter instead of using the default wrapper. That driver is more mature and well tested than this one, but it only provides a 32 bit source filter and won't work with 64 bit apps.

Some examples of 64 bit DirectShow applications:
- [ViewTracker](https://store.steampowered.com/app/929270/ViewTracker/)
- [OBS Studio](https://obsproject.com/)
- [VLC media player](https://www.videolan.org/vlc/)

## Installing

The easiest way to get started with this driver is to head to the [releases section](https://github.com/jkevin/PS3EyeDirectShow/releases) and download the installer. It will install the DirectShow filters as well as a generic WinUSB driver. If it detects that the Code Laboratories driver is already installed it will only install a 64 bit DirectShow filter. The driver component provided by Code Laboratories is WinUSB compatible so there isn't any need to install another one.

## Compiling From Source

Requirements:
- Visual Studio 2017
- Windows 10 SDK
- WIX

First clone the repo and init the submodules:
```
$ git clone https://github.com/jkevin/PS3EyeDirectShow.git
$ cd PS3EyeDirectShow
$ git submodule init
$ git submodule update
```

Open `libusb/msvc/libusb_2017.sln` in Visual Studio 2017. If you don't have the Windows 8.1 SDK, change the SDK target to Windows 10 in all of the libusb project properties. Build the solution with all desired configurations. Next open PS3EyeDriverMSVC.sln and build the desired configs again.

If you would like to make the compiled DirectShow filters available to other applications, run `c:\windows\system32\regsvr32.exe <path to filter dll>` from an administrator command prompt. If you have run the installer make sure to uninstall the package before doing this. Use `c:\windows\system32\regsvr32.exe /u <path to filter dll>` to unregister the filter.

If the DLL was built with a debug configuration it's possible to use WinDBG to set a breakpoint in the filter code which will be hit when using the camera with any DirectShow application.

To build the installer, first build the 32 and 64 bit release configurations of the solution. Then right click on the PS3EyeInstaller project in the solution explorer and click build.

## TODO
- Manual exposure and white balance controls
- Windows Media Foundation source?
