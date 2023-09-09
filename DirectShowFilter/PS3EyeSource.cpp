#include <streams.h>
#include <strsafe.h>

#include "ps3eye.hpp"
#include "PS3EyeSourceFilter.h"
#include "PS3EyeGuids.h"

PS3EyeSource::PS3EyeSource(IUnknown *pUnk, HRESULT *phr) 
	: CSource(NAME("PS3EyeSource"), pUnk, CLSID_PS3EyeSource),
	_pin(NULL)
{
	const std::vector<std::shared_ptr<ps3eye::camera>> &devices = ps3eye::list_devices();
	std::shared_ptr<ps3eye::camera> dev;
	if (devices.size() > 0) {
		dev = devices[0];
	}
	_pin = new PS3EyePushPin(phr, this, dev);
	if (phr) {
		if (_pin == NULL)
			*phr = E_OUTOFMEMORY;
		else
			*phr = S_OK;
	}
}

PS3EyeSource::~PS3EyeSource() {
	if(_pin != NULL) delete _pin;
}

CUnknown * WINAPI PS3EyeSource::CreateInstance(IUnknown * pUnk, HRESULT * phr)
{
	PS3EyeSource *pNewFilter = new PS3EyeSource(pUnk, phr);

	if (phr)
	{
		if (pNewFilter == NULL)
			*phr = E_OUTOFMEMORY;
		else
			*phr = S_OK;
	}

	return pNewFilter;
}