#pragma once

// Filter name strings
#define g_ps3PS3EyeSource    L"PS3 Eye Universal"
#define g_ps3PS3EyeSource2    L"PS3 Eye Universal2"
#define g_ps3PS3EyeSource3    L"PS3 Eye Universal3"
#define g_ps3PS3EyeSource4    L"PS3 Eye Universal4"
#define g_ps3PS3EyeSource5    L"PS3 Eye Universal5"
#define g_ps3PS3EyeSource6    L"PS3 Eye Universal6"
#define g_ps3PS3EyeSource7    L"PS3 Eye Universal7"
#define g_ps3PS3EyeSource8    L"PS3 Eye Universal8"

class PS3EyePushPin;

class PS3EyePushPin : public CSourceStream, public IKsPropertySet, public IAMStreamConfig
{
protected:
	std::shared_ptr<ps3eye::camera> _device;
	CMediaType _currentMediaType;
	HRESULT _GetMediaType(int iPosition, CMediaType *pMediaType);
	REFERENCE_TIME _startTime;
	IReferenceClock *_refClock;

public:
	PS3EyePushPin(HRESULT *phr, CSource *pFilter, std::shared_ptr<ps3eye::camera> device);
	~PS3EyePushPin();

	DECLARE_IUNKNOWN

	STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void **ppv)
	{
		if (riid == IID_IKsPropertySet)
		{
			return GetInterface((IKsPropertySet*)this, ppv);
		}
		else if (riid == IID_IAMStreamConfig) {
			return GetInterface((IAMStreamConfig*)this, ppv);
		}
		return CSourceStream::NonDelegatingQueryInterface(riid, ppv);
	}

	HRESULT CheckMediaType(const CMediaType *);
	HRESULT GetMediaType(int iPosition, CMediaType *pMediaType);
	HRESULT DecideBufferSize(IMemAllocator *pAlloc, ALLOCATOR_PROPERTIES *pRequest);
	
	HRESULT OnThreadStartPlay();
	HRESULT OnThreadCreate();
	HRESULT OnThreadDestroy();
	HRESULT FillBuffer(IMediaSample *pSample);
	void FillError(BYTE *pData);

	// Quality control
	// Not implemented because we aren't going in real time.
	// If the file-writing filter slows the graph down, we just do nothing, which means
	// wait until we're unblocked. No frames are ever dropped.
	STDMETHODIMP Notify(IBaseFilter *pSelf, Quality q)
	{
		return E_FAIL;
	}


	// Inherited via IKsPropertySet
	virtual HRESULT __stdcall Set(REFGUID guidPropSet, DWORD dwPropID, LPVOID pInstanceData, DWORD cbInstanceData, LPVOID pPropData, DWORD cbPropData) override;

	virtual HRESULT __stdcall Get(REFGUID guidPropSet, DWORD dwPropID, LPVOID pInstanceData, DWORD cbInstanceData, LPVOID pPropData, DWORD cbPropData, DWORD * pcbReturned) override;

	virtual HRESULT __stdcall QuerySupported(REFGUID guidPropSet, DWORD dwPropID, DWORD * pTypeSupport) override;


	// Inherited via IAMStreamConfig
	virtual HRESULT __stdcall SetFormat(AM_MEDIA_TYPE * pmt) override;

	virtual HRESULT __stdcall GetFormat(AM_MEDIA_TYPE ** ppmt) override;

	virtual HRESULT __stdcall GetNumberOfCapabilities(int * piCount, int * piSize) override;

	virtual HRESULT __stdcall GetStreamCaps(int iIndex, AM_MEDIA_TYPE ** ppmt, BYTE * pSCC) override;

};

class PS3EyeSource : public CSource
{
private:
	PS3EyeSource(IUnknown *pUnk, HRESULT *phr, const GUID id, int index);
	~PS3EyeSource();

	PS3EyePushPin *_pin;

public:
	// Support up to 8 devices
	static CUnknown * WINAPI CreateInstance(IUnknown *pUnk, HRESULT *phr);
	static CUnknown * WINAPI CreateInstance2(IUnknown *pUnk, HRESULT *phr);
	static CUnknown * WINAPI CreateInstance3(IUnknown *pUnk, HRESULT *phr);
	static CUnknown * WINAPI CreateInstance4(IUnknown *pUnk, HRESULT *phr);
	static CUnknown * WINAPI CreateInstance5(IUnknown *pUnk, HRESULT *phr);
	static CUnknown * WINAPI CreateInstance6(IUnknown *pUnk, HRESULT *phr);
	static CUnknown * WINAPI CreateInstance7(IUnknown *pUnk, HRESULT *phr);
	static CUnknown * WINAPI CreateInstance8(IUnknown *pUnk, HRESULT *phr);
};