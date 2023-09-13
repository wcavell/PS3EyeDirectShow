#include <streams.h>
#include <strsafe.h>

#include "ps3eye.hpp"
#include "PS3EyeSourceFilter.h"
#include "PS3EyeGuids.h"

PS3EyeSource::PS3EyeSource(IUnknown *pUnk, HRESULT *phr, const GUID id, int index)
	: CSource(NAME("PS3EyeSource"), pUnk, id),
	_pin(NULL)
{
	const std::vector<std::shared_ptr<ps3eye::camera>> &devices = ps3eye::list_devices();
	std::shared_ptr<ps3eye::camera> dev;
	// Enumerate device list and pick camera at specifc index
	for (unsigned i = 0; i < devices.size(); i++) {
		if (i == index)
		{
			dev = devices[i];
			break;
		}
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
	PS3EyeSource *pNewFilter = new PS3EyeSource(pUnk, phr, CLSID_PS3EyeSource, 0);

	if (phr)
	{
		if (pNewFilter == NULL)
			*phr = E_OUTOFMEMORY;
		else
			*phr = S_OK;
	}

	return pNewFilter;
}

CUnknown * WINAPI PS3EyeSource::CreateInstance2(IUnknown * pUnk, HRESULT * phr)
{
	PS3EyeSource *pNewFilter = new PS3EyeSource(pUnk, phr, CLSID_PS3EyeSource2, 1);

	if (phr)
	{
		if (pNewFilter == NULL)
			*phr = E_OUTOFMEMORY;
		else
			*phr = S_OK;
	}

	return pNewFilter;
}

CUnknown * WINAPI PS3EyeSource::CreateInstance3(IUnknown * pUnk, HRESULT * phr)
{
	PS3EyeSource *pNewFilter = new PS3EyeSource(pUnk, phr, CLSID_PS3EyeSource3, 2);

	if (phr)
	{
		if (pNewFilter == NULL)
			*phr = E_OUTOFMEMORY;
		else
			*phr = S_OK;
	}

	return pNewFilter;
}

CUnknown * WINAPI PS3EyeSource::CreateInstance4(IUnknown * pUnk, HRESULT * phr)
{
	PS3EyeSource *pNewFilter = new PS3EyeSource(pUnk, phr, CLSID_PS3EyeSource4, 3);

	if (phr)
	{
		if (pNewFilter == NULL)
			*phr = E_OUTOFMEMORY;
		else
			*phr = S_OK;
	}

	return pNewFilter;
}

CUnknown * WINAPI PS3EyeSource::CreateInstance5(IUnknown * pUnk, HRESULT * phr)
{
	PS3EyeSource *pNewFilter = new PS3EyeSource(pUnk, phr, CLSID_PS3EyeSource5, 4);

	if (phr)
	{
		if (pNewFilter == NULL)
			*phr = E_OUTOFMEMORY;
		else
			*phr = S_OK;
	}

	return pNewFilter;
}

CUnknown * WINAPI PS3EyeSource::CreateInstance6(IUnknown * pUnk, HRESULT * phr)
{
	PS3EyeSource *pNewFilter = new PS3EyeSource(pUnk, phr, CLSID_PS3EyeSource6, 5);

	if (phr)
	{
		if (pNewFilter == NULL)
			*phr = E_OUTOFMEMORY;
		else
			*phr = S_OK;
	}

	return pNewFilter;
}

CUnknown * WINAPI PS3EyeSource::CreateInstance7(IUnknown * pUnk, HRESULT * phr)
{
	PS3EyeSource *pNewFilter = new PS3EyeSource(pUnk, phr, CLSID_PS3EyeSource7, 6);

	if (phr)
	{
		if (pNewFilter == NULL)
			*phr = E_OUTOFMEMORY;
		else
			*phr = S_OK;
	}

	return pNewFilter;
}

CUnknown * WINAPI PS3EyeSource::CreateInstance8(IUnknown * pUnk, HRESULT * phr)
{
	PS3EyeSource *pNewFilter = new PS3EyeSource(pUnk, phr, CLSID_PS3EyeSource8, 7);

	if (phr)
	{
		if (pNewFilter == NULL)
			*phr = E_OUTOFMEMORY;
		else
			*phr = S_OK;
	}

	return pNewFilter;
}