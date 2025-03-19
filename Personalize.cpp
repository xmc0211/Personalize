// MIT License
//
// Copyright (c) 2025 Personalize - xmc0211 <xmc0211@qq.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "Personalize.h"
#include <mmdeviceapi.h> 
#include <endpointvolume.h>
#include <audioclient.h>
#include "sphelper.h"

#pragma comment(lib, "sapi.lib")

BOOL InitSpeaker(hSpeaker* hSp, INT nLanguage, LONG lRate) {
    HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)hSp);
    if (FAILED(hr)) {
        return FALSE;
    }
    ISpObjectToken* pSpObjToken = NULL;
    if (SUCCEEDED(SpFindBestToken(SPCAT_VOICES, (std::wstring(L"language=") + std::to_wstring(nLanguage)).c_str(), NULL, &pSpObjToken))) {
        (*hSp)->SetVoice(pSpObjToken);
        (*hSp)->SetRate(lRate);
        pSpObjToken->Release();
        return TRUE;
    }
    return FALSE;
}
BOOL Speak(hSpeaker* hSp, LPCWSTR lpText) {
    if (hSp == NULL || (*hSp) == NULL) return FALSE;
    (*hSp)->Speak(lpText, 0, NULL);
    return TRUE;
}
BOOL UninitSpeaker(hSpeaker* hSp) {
    if (hSp == NULL || (*hSp) == NULL) return FALSE;
    (*hSp)->Release();
    (*hSp) = NULL;
    hSp = NULL;
    return TRUE;
}

BOOL SetSystemVolume(INT Volume) {
    BOOL bRes = FALSE;
    HRESULT hr;
    IMMDeviceEnumerator* pDeviceEnumerator = 0;
    IMMDevice* pDevice = 0;
    IAudioEndpointVolume* pAudioEndpointVolume = 0;
    IAudioClient* pAudioClient = 0;

    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pDeviceEnumerator);
    if (FAILED(hr)) goto EXIT;
    hr = pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &pDevice);
    if (FAILED(hr)) goto EXIT;
    hr = pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (void**)&pAudioEndpointVolume);
    if (FAILED(hr)) goto EXIT;
    hr = pDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, (void**)&pAudioClient);
    if (FAILED(hr)) goto EXIT;

    float fVolume;
    fVolume = Volume / 100.0f;
    hr = pAudioEndpointVolume->SetMasterVolumeLevelScalar(fVolume, &GUID_NULL);
    if (FAILED(hr)) goto EXIT;

    bRes = TRUE;

EXIT:
    if (pAudioClient) pAudioClient->Release();
    if (pAudioEndpointVolume) pAudioEndpointVolume->Release();
    if (pDevice) pDevice->Release();
    if (pDeviceEnumerator) pDeviceEnumerator->Release();

    return bRes;
}
BOOL GetSystemVolume(INT* lpVolume) {
    BOOL bRes = FALSE;
    HRESULT hr;
    IMMDeviceEnumerator* pDeviceEnumerator = 0;
    IMMDevice* pDevice = 0;
    IAudioEndpointVolume* pAudioEndpointVolume = 0;
    IAudioClient* pAudioClient = 0;

    if (lpVolume == nullptr) return FALSE;

    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pDeviceEnumerator);
    if (FAILED(hr)) goto EXIT;
    hr = pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &pDevice);
    if (FAILED(hr)) goto EXIT;
    hr = pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (void**)&pAudioEndpointVolume);
    if (FAILED(hr)) goto EXIT;
    hr = pDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, (void**)&pAudioClient);
    if (FAILED(hr)) goto EXIT;

    float fVolume;
    hr = pAudioEndpointVolume->GetMasterVolumeLevelScalar(&fVolume);
    if (FAILED(hr)) goto EXIT;

    *lpVolume = fVolume * 100;
EXIT:
    if (pAudioClient) pAudioClient->Release();
    if (pAudioEndpointVolume) pAudioEndpointVolume->Release();
    if (pDevice) pDevice->Release();
    if (pDeviceEnumerator) pDeviceEnumerator->Release();

    return bRes;
}