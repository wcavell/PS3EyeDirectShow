#pragma once
#include <libusb.h>

#include "mgr.hpp"
#include "ps3eye.hpp"
using namespace ps3eye;
using namespace ps3eye::detail;
#ifdef _MSC_VER
#   define ONE_API __declspec(dllexport)
#else
#   define ONE_API
#   error Not a Windows platform.
#endif 

struct usb_t
{
	usb_t(std::vector<ps3eye::camera*> list):devices(list)
	{
		
	}
	~usb_t()
	{
		
	}
	std::vector<ps3eye::camera*> devices;
};
extern "C" {
	ONE_API usb_t* getListDevices(uint32_t& count)
	{
		const auto list = ps3eye::getdevices();
		count = list.size();
		return new usb_t(list);
	}
	ONE_API uint32_t getListCount(usb_t* usb)
	{
		return usb->devices.size();
	}
	ONE_API void listDeviceDestroy(usb_t* usb)
	{
		/*const auto devices = usb->devices;
		for (auto device : devices)
		{
			delete device;
		}*/
		usb->devices.clear();
		delete usb;
		usb = nullptr;
	}
	ONE_API camera* getEyeCamByList(usb_t* usb,uint32_t id)
	{
		if (id < usb->devices.size())
			return usb->devices[id];
		return nullptr;
	}

	//ONE_API camera* EyeCam_Create(uint32_t id);
	ONE_API void eye_Destroy(camera* cam)
	{
		delete cam;
		cam = nullptr;
	}
	ONE_API bool init(camera* cam, resolution res, int framerate, format fmt)
	{
		return cam->init(res, framerate, fmt);
	}
	ONE_API bool start(camera* cam)
	{
		return cam->start();
	}
	ONE_API void stop(camera* cam)
	{
		cam->stop();
	}
	ONE_API bool getAutogain(camera* cam)
	{
		if(cam==nullptr)
			return false;
		return cam->auto_gain();
	}
	ONE_API void setAutogain(camera* cam, bool val) { cam->set_auto_gain(val); }
	ONE_API bool getAutoWhiteBalance(camera* cam)
	{
		if (cam == nullptr)
			return false;
		return cam->awb();
	}
	ONE_API void setAutoWhiteBalance(camera* cam, bool val) { cam->set_awb(val); }
	ONE_API uint8_t getGain(camera* cam)
	{
		if (cam == nullptr)
			return 255;
		return cam->gain();
	}
	ONE_API void setGain(camera* cam, uint8_t val) { cam->set_gain(val); }
	ONE_API uint8_t getExposure(camera* cam)
	{
		if (cam == nullptr)
			return 255;
		return cam->exposure();
	}
	ONE_API void setExposure(camera* cam, uint8_t val) { cam->set_exposure(val); }
	ONE_API uint8_t getSharpness(camera* cam)
	{
		if (cam == nullptr)
			return 255;
		return cam->sharpness();
	}
	ONE_API void setSharpness(camera* cam, uint8_t val) { cam->set_sharpness(val); }
	ONE_API uint8_t getContrast(camera* cam)
	{
		if (cam == nullptr)
			return 255;
		return cam->contrast();
	}
	ONE_API void setContrast(camera* cam, uint8_t val) { cam->set_contrast(val); }
	ONE_API uint8_t getBrightness(camera* cam)
	{
		if (cam == nullptr)
			return 255;
		return cam->brightness();
	}
	ONE_API void setBrightness(camera* cam, uint8_t val) { cam->set_brightness(val); }
	ONE_API uint8_t getHue(camera* cam)
	{
		if (cam == nullptr)
			return 255;
		return cam->hue();
	}
	ONE_API void setHue(camera* cam, uint8_t val) { cam->set_hue(val); }
	ONE_API uint8_t getRedBalance(camera* cam)
	{
		if (cam == nullptr)
			return 255;
		return cam->red_balance();
	}
	ONE_API void setRedBalance(camera* cam, uint8_t val) { cam->set_red_balance(val); }
	ONE_API uint8_t getBlueBalance(camera* cam)
	{
		if (cam == nullptr)
			return 255;
		return cam->blue_balance();
	}
	ONE_API void setBlueBalance(camera* cam, uint8_t val) { cam->set_blue_balance(val); }
	ONE_API uint8_t getGreenBalance(camera* cam)
	{
		if (cam == nullptr)
			return 255;
		return cam->green_balance();
	}
	ONE_API void setGreenBalance(camera* cam, uint8_t val) { cam->set_green_balance(val); }
	ONE_API bool getFlipH(camera* cam)
	{
		if (cam == nullptr)
			return false;
		return cam->flip_status().first;
	}
	ONE_API bool getFlipV(camera* cam)
	{
		if (cam == nullptr)
			return false;
		return cam->flip_status().second;
	}
	ONE_API void setFlip(camera* cam, bool horizontal /*= false*/, bool vertical /*= false*/) { cam->set_flip_status(horizontal, vertical); }
	ONE_API bool getTestPattern(camera* cam)
	{
		if (cam == nullptr)
			return false;
		return cam->test_pattern_status();
	}
	ONE_API void setTestPattern(camera* cam, bool enable) { cam->set_test_pattern_status(enable); }
	ONE_API bool isStreaming(camera* cam)
	{
		if (cam == nullptr)
			return false;
		return cam->is_open();
	}
	ONE_API bool isInitialized(camera* cam)
	{
		if (cam == nullptr)
			return false;
		return cam->is_initialized();
	}
	ONE_API bool getUSBPortPath(camera* cam, char* out_identifier, size_t max_identifier_length) { return cam->usb_port(out_identifier, max_identifier_length); }
	ONE_API bool getFrame(camera* cam, uint8_t* frame) { return cam->get_frame(frame); }

	ONE_API int32_t getWidth(camera* cam)
	{
		if (cam == nullptr)
			return 0;
		return cam->width();
	}
	ONE_API int32_t getHeight(camera* cam)
	{
		if (cam == nullptr)
			return 0;
		return cam->height();
	}
	ONE_API int32_t getFrameRate(camera* cam)
	{
		if (cam == nullptr)
			return 0;
		return cam->framerate();
	}
	ONE_API void setFrameRate(camera* cam, int val) { return cam->set_framerate(val); }
	ONE_API int32_t getRowBytes(camera* cam)
	{
		if (cam == nullptr)
			return 0;
		return cam->stride();
	}
	ONE_API int32_t getOutputBytesPerPixel(camera* cam)
	{
		if (cam == nullptr)
			return 0;
		return cam->bytes_per_pixel();
	}

	ONE_API int normalize_framerate(int fps, resolution res) { return camera::normalize_framerate(fps, res); }
	ONE_API int getEyeCount();
	ONE_API bool availableState(camera* cam)
	{
		return cam->availableState();
	}
	ONE_API int getPortNum(camera* cam)
	{
		return libusb_get_bus_number(cam->device());
	}
	ONE_API int getBusNum(camera* cam)
	{
		return libusb_get_bus_number(cam->device());
	}
}

