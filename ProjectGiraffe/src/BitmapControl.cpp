//
// Tizen Native SDK
// Copyright (c) 2012-2013 Samsung Electronics Co., Ltd.
//
// Licensed under the Flora License, Version 1.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://floralicense.org/license/
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an AS IS BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//


#include "BitmapControl.h"
#include "SafeMacros.h"
#include <FAppApp.h>
#include <FMediaImageBuffer.h>

using namespace Tizen::Graphics;
using namespace Tizen::Base;
using namespace Tizen::Media;
using namespace Tizen::Io;
using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::System;

BitmapControl::BitmapControl(void)
	:_srcBitmap(null),
	_rescale(false)
	// TODO: Add more initializations
{
}

BitmapControl::~BitmapControl(void)
{
	// TODO: ADD MORE MEMORY MANAGEMENT HERE
	SAFE_DELETE(_srcBitmap);
}

BitmapControl*
BitmapControl::ConstructN(Tizen::Ui::Control* ctrl, bool rescale)
{
	result r = E_SUCCESS;
	BitmapControl* pBmpCtrl = null;

	TryCatch(ctrl, r = E_SYSTEM, "ctrl is null");

	ctrl->SetShowState(false);
	ctrl->RequestRedraw(false);

	pBmpCtrl = new (std::nothrow) BitmapControl();
	r = pBmpCtrl->Construct(ctrl->GetBounds(), rescale);
	TryCatch(r == E_SUCCESS, , "pBmpCtrl->Construct failed:%s", GetErrorMessage(r));

CATCH:
	SetLastResult(r);
	return pBmpCtrl;
}

result
BitmapControl::Construct(const Tizen::Graphics::Rectangle& rect, bool rescale)
{
	result r = E_SUCCESS;
	r = Container::Construct(rect, true);
	TryReturn(E_SUCCESS == r, r , "[%s] Propagated.", GetErrorMessage(r));
	_rescale = rescale;

	return r;
}


BitmapControl*
BitmapControl::ConstructFromPath(String filePath, const Tizen::Graphics::Rectangle& rect, bool rescale)
{
	AppLog("Testing: Constructing Bitmap");
	result r = E_SUCCESS;

	BitmapControl* bmpCtrl = null;

	bmpCtrl = new (std::nothrow) BitmapControl();
	r = bmpCtrl->Construct(filePath, rect, rescale);
	TryCatch(r == E_SUCCESS, , "bmpCtrl->Construct failed:%s", GetErrorMessage(r));

CATCH:
	SetLastResult(r);
	return bmpCtrl;
}

result
BitmapControl::Construct(String filePath, const Tizen::Graphics::Rectangle& rect, bool rescale)
{
	result r = E_SUCCESS;
	AppLog("Testing: Constructing img");
	r = _img.Construct();

	AppLog("Testing: Constructing button");
	_ctrlButton = new Button();
	_ctrlButton->Construct(rect);

	_srcFilePath = filePath;
	AppLog("Testing: Resetting file attributes");
	FileAttributes attr;
	this->ResetFileAtrributes();

	if (_srcBitmap != null)
	{
		delete _srcBitmap;
		_srcBitmap = null;
	}

	AppLog("Testing: Getting file attributes");
	r = Tizen::Io::File::GetAttributes(_srcFilePath, attr);

	_ctrlButton->SetShowState(false);
	_ctrlButton->RequestRedraw(false);
	AppLog("Testing: Changing button status");

	_srcFileSize = attr.GetFileSize();

	AppLog("Testing: Decoding image %ls", _srcFilePath.GetPointer());
	BitmapPixelFormat pixelFmt = BITMAP_PIXEL_FORMAT_RGB565;
	_srcBitmap = _img.DecodeN(_srcFilePath, pixelFmt);
	TryReturn(r == E_SUCCESS, r, "[%s] Failed to construct image instance.", GetErrorMessage(r));
	_srcWidth = _srcBitmap->GetWidth();
	_srcHeight = _srcBitmap->GetHeight();

	AppLog("Testing: Constructing container");
	r = Container::Construct(rect, true);
	TryReturn(E_SUCCESS == r, r , "[%s] Propagated.", GetErrorMessage(r));
	_rescale = rescale;

	// Remember to ->Clear() before setting bitmap and calling ->Draw() afterwards
	AppLog("Testing: Setting bitmap");
//	this->SetBitmap(*_srcBitmap);

	AppLog("Testing: Complete");
	return r;
}

result
BitmapControl::SetBitmap(const Tizen::Graphics::Bitmap& bmp)
{
	result r = E_SUCCESS;
	float xratio;
	float yratio;
	float ratio;
	Rectangle rect;

	TryCatch(&bmp, r = E_INVALID_ARG, "bmp is null");

	rect = GetBounds();

	SAFE_DELETE(_srcBitmap);

	if (_rescale == true)
	{
		AppLog("Testing: resize bitmap");
		xratio = (float) bmp.GetWidth() / (float) rect.width;
		yratio = (float) bmp.GetHeight() / (float) rect.height;

		rect.x = rect.y = 0;
		rect.width = bmp.GetWidth();
		rect.height = bmp.GetHeight();

		_srcBitmap = new (std::nothrow) Bitmap();
		r = _srcBitmap->Construct(bmp, rect);
		TryCatch(r == E_SUCCESS, , "_srcBitmap->Construct failed:%s", GetErrorMessage(r));

		ratio = xratio > yratio ? xratio : yratio;
		if (ratio > 1.0)
		{
			int width;
			int height;
			// make resized image and display.
			width = (int) ((float) bmp.GetWidth() / ratio);
			height = (int) ((float) bmp.GetHeight() / ratio);
			r = _srcBitmap->Scale(Dimension(width, height));
			TryCatch(r == E_SUCCESS, , "_srcBitmap->Scale:%s %d %d", GetErrorMessage(r), width, height);
		}
	}
	else
	{

		int width = (rect.width > bmp.GetWidth()) ? bmp.GetWidth() : rect.width;
		int height = (rect.height > bmp.GetHeight()) ? bmp.GetHeight() : rect.height;
		int x = (bmp.GetWidth() - width) / 2;
		int y = (bmp.GetHeight() - height) / 2;

		_srcBitmap = new (std::nothrow) Bitmap();
		r = _srcBitmap->Construct(bmp, Rectangle(x, y, width, height));
		TryCatch(r == E_SUCCESS, , "_srcBitmap->Construct:%s %d %d %d %d", GetErrorMessage(r), x, y, width, height);
	}
	return r;

CATCH:
	SAFE_DELETE(_srcBitmap);
	return r;
}

result
BitmapControl::Clear(void)
{
	result r = E_SUCCESS;
	Tizen::Graphics::Canvas* pCanvas = GetCanvasN();

	TryCatch(pCanvas, r = GetLastResult(), "GetCanvasN failed:%s", GetErrorMessage(GetLastResult()));

	pCanvas->Clear();
	pCanvas->Show();

CATCH:
	SAFE_DELETE(pCanvas);
	return r;
}

result
BitmapControl::OnDraw(void)
{
	result r = E_SUCCESS;
	Tizen::Graphics::Canvas* pCanvas = null;
	Rectangle rect = GetBounds();
	int x;
	int y;

	pCanvas = GetCanvasN();
	TryCatch(pCanvas, r = GetLastResult(), "GetCanvasN failed:%s", GetErrorMessage(GetLastResult()));

	pCanvas->Clear();

	if (_srcBitmap != null)
	{
		x = (rect.width - _srcBitmap->GetWidth()) / 2;
		y = (rect.height - _srcBitmap->GetHeight()) / 2;

		r = pCanvas->DrawBitmap(Tizen::Graphics::Point(x, y), *_srcBitmap);
	}

	pCanvas->Show();

CATCH:
	SAFE_DELETE(pCanvas);
	return r;
}


void
BitmapControl::ResetFileAtrributes(void)
{
	_srcWidth = 0;
	_srcHeight = 0;
	_srcFileSize = 0;
}
