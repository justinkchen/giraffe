//
// Tizen native SDK
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
#ifndef _GALLERY_FORM_H_
#define _GALLERY_FORM_H_

#include <FSystem.h>
#include "BaseForm.h"

class GalleryForm
	: public BaseForm
	, public Tizen::Ui::IOrientationEventListener
	, public Tizen::Ui::Controls::IGalleryItemProvider
	, public Tizen::Ui::Controls::IGalleryEventListener
	, public Tizen::Base::Runtime::Thread
{
public:
	GalleryForm(void);
	virtual ~GalleryForm(void);

	virtual bool Initialize(void);
	void GetBitmap(void);
	void CreateGallery(void);
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
	virtual void OnOrientationChanged(const Tizen::Ui::Control &source, Tizen::Ui::OrientationStatus orientationStatus);

	// IGalleryItemEventListener
	virtual void OnGalleryCurrentItemChanged (Tizen::Ui::Controls::Gallery &view, int index);
	virtual void OnGalleryItemClicked(Tizen::Ui::Controls::Gallery& listView, int index);
	virtual void OnGallerySlideShowStarted(Tizen::Ui::Controls::Gallery& gallery);
	virtual void OnGallerySlideShowStopped(Tizen::Ui::Controls::Gallery& gallery);

	//IGalleryItemProvider
	virtual Tizen::Ui::Controls::GalleryItem* CreateItem(int index);
	virtual bool DeleteItem(int index, Tizen::Ui::Controls::GalleryItem* pItem);
	virtual int GetItemCount(void);

	//Thread
	virtual bool OnStart(void);
	virtual void OnStop(void);
	virtual void OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList *pArgs);
	virtual Tizen::Base::Object *  Run(void);

private:
	static const int ID_FOOTER_SLIDE_SHOW_STOP = 101;
	static const int ID_FOOTER__SLIDE_SHOW_START = 102;
	static const int ID_FORMAT_STRING = 500;
	static const RequestId    UPDATE_GALLERY 		= 200;
	bool __visible;
	Tizen::Ui::Controls::Header* __pHeader;
	Tizen::Graphics::Bitmap* __pImage1;
	Tizen::Graphics::Bitmap* __pImage2;
	Tizen::Graphics::Bitmap* __pImage3;
	Tizen::Graphics::Bitmap* __pImage4;
	Tizen::Ui::Controls::Gallery* __pGallery;
	Tizen::Base::Runtime::Thread* __pThread;
	Tizen::Base::Collection::ArrayList __items;
	Tizen::Base::Runtime::Mutex* __pMutex;
}; // GalleryForm

#endif // _GALLERY_FORM_H_
