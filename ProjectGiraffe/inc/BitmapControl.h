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


#ifndef _BITMAP_CONTROL_H_
#define _BITMAP_CONTROL_H_

#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>
#include <FMedia.h>
#include <FGraphics.h>
#include <FApp.h>

class BitmapControl
	: public Tizen::Ui::Container
{
public:
	BitmapControl(void);
	virtual ~BitmapControl(void);

	static BitmapControl* ConstructN(Tizen::Ui::Control* pCtrl, bool rescale = true);
	result Construct(const Tizen::Graphics::Rectangle& rect, bool rescale);
	result SetBitmap(const Tizen::Graphics::Bitmap& bmp);
	result Clear(void);
	void ResetFileAtrributes(void);

	// Custom construction functions
	static BitmapControl* ConstructFromPath(Tizen::Base::String filePath, const Tizen::Graphics::Rectangle& rect, bool rescale = true);
	result Construct(Tizen::Base::String filePath, const Tizen::Graphics::Rectangle& rect, bool rescale);

protected:
	virtual result OnDraw(void);

private:
	bool _rescale;
	Tizen::Base::String _srcFilePath;
	Tizen::Graphics::Bitmap* _srcBitmap;
	int _srcWidth;
	int _srcHeight;
	int _srcFileSize;
	Tizen::Ui::Controls::Button* _ctrlButton;
	Tizen::Media::Image _img;

};

#endif // _BITMAP_CONTROL_H_
