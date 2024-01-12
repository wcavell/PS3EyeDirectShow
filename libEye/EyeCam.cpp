#include "EyeCam.h"

extern "C" {
	/*ONE_API eye_t* EyeCam_Create(uint32_t id)
	{
		const std::vector<std::shared_ptr<ps3eye::camera>>& devices = ps3eye::list_devices();
		if (id < devices.size())
		{
			auto dev = devices[id];
			return new eye_t(dev);
		}
		return nullptr;
	}*/
	ONE_API int getEyeCount()
	{
		return usb_manager::instance().getEyeCount();
	}
}