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

#ifndef PERSONALIZE_H
#define PERSONALIZE_H

#include <windows.h> 
#include <sapi.h>
#include <string>

// For nLanguage
#define LANGUAGE_ZH_CH (804)
#define LANGUAGE_EN_US (409)

typedef ISpVoice* hSpeaker;

// Speak (narrator)
BOOL InitSpeaker(hSpeaker* hSp, INT nLanguage = LANGUAGE_EN_US, LONG lRate = -2);
BOOL Speak(hSpeaker* hSp, LPCWSTR lpText);
BOOL UninitSpeaker(hSpeaker* hSp);

// Set/Get system volume
BOOL SetSystemVolume(INT Volume);
BOOL GetSystemVolume(INT* lpVolume);

#endif