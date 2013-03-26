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

using namespace Tizen::Graphics;

BitmapControl::BitmapControl(void)
	:_pBmp(null),
	__rescale(false)
{
}

BitmapControl::~BitmapControl(void)
{
	SAFE_DELETE(_pBmp);
}

BitmapControl*
BitmapControl::ConstructN(Tizen::Ui::Control* pCtrl, bool rescale)
{
	result r = E_SUCCESS;
	BitmapControl* pBmpCtrl = null;

	TryCatch(pCtrl, r = E_SYSTEM, "pCtrl is null");

	pCtrl->SetShowState(false);
	pCtrl->RequestRedraw(false);

	pBmpCtrl = new (std::nothrow) BitmapControl();
	r = pBmpCtrl->Construct(pCtrl->GetBounds(), rescale);
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
	__rescale = rescale;

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

	SAFE_DELETE(_pBmp);

	if (__rescale == true)
	{

		xratio = (float) bmp.GetWidth() / (float) rect.width;
		yratio = (float) bmp.GetHeight() / (float) rect.height;

		rect.x = rect.y = 0;
		rect.width = bmp.GetWidth();
		rect.height = bmp.GetHeight();

		_pBmp = new (std::nothrow) Bitmap();
		r = _pBmp->Construct(bmp, rect);
		TryCatch(r == E_SUCCESS, , "pNewBitmap->Construct failed:%s", GetErrorMessage(r));

		ratio = xratio > yratio ? xratio : yratio;
		if (ratio > 1.0)
		{
			int width;
			int height;
			// make resized image and display.
			width = (int) ((float) bmp.GetWidth() / ratio);
			height = (int) ((float) bmp.GetHeight() / ratio);
			r = _pBmp->Scale(Dimension(width, height));
			TryCatch(r == E_SUCCESS, , "pBmp->Scale:%s %d %d", GetErrorMessage(r), width, height);
		}
	}
	else
	{

		int width = (rect.width > bmp.GetWidth()) ? bmp.GetWidth() : rect.width;
		int height = (rect.height > bmp.GetHeight()) ? bmp.GetHeight() : rect.height;
		int x = (bmp.GetWidth() - width) / 2;
		int y = (bmp.GetHeight() - height) / 2;

		_pBmp = new (std::nothrow) Bitmap();
		r = _pBmp->Construct(bmp, Rectangle(x, y, width, height));
		TryCatch(r == E_SUCCESS, , "pBmp->Construct:%s %d %d %d %d", GetErrorMessage(r), x, y, width, height);
	}
	return r;

CATCH:
	SAFE_DELETE(_pBmp);
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

	if (_pBmp != null)
	{
		x = (rect.width - _pBmp->GetWidth()) / 2;
		y = (rect.height - _pBmp->GetHeight()) / 2;

		r = pCanvas->DrawBitmap(Tizen::Graphics::Point(x, y), *_pBmp);
	}

	pCanvas->Show();

CATCH:
	SAFE_DELETE(pCanvas);
	return r;
}
