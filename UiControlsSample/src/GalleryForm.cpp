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
#include <FIoDirectory.h>
#include <FAppApp.h>
#include "GalleryForm.h"

using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Base;
using namespace Tizen::Io;
using namespace Tizen::App;
using namespace Tizen::Media;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Base::Collection;
using namespace Tizen::System;

const wchar_t GALLERY_IMAGE_PATH1[] = L"res/screen-density-high/image1.jpg";
const wchar_t GALLERY_IMAGE_PATH2[] = L"res/screen-density-high/image2.jpg";
const wchar_t GALLERY_IMAGE_PATH3[] = L"res/screen-density-high/image3.jpg";
const wchar_t GALLERY_IMAGE_PATH4[] = L"res/screen-density-high/image4.jpg";

GalleryForm::GalleryForm(void)
	: __visible(true)
	, __pImage1(null)
	, __pImage2(null)
	, __pImage3(null)
	, __pImage4(null)
	, __pMutex(null)
{
}

GalleryForm::~GalleryForm(void)
{
}

bool
GalleryForm::Initialize(void)
{
	Form::Construct(L"IDF_FORM_GALLERY");
	return true;
}

result
GalleryForm::OnInitializing(void)
{
	BaseForm::OnInitializing();
	result r = E_SUCCESS;

	r = SetActionBarsTranslucent(FORM_ACTION_BAR_INDICATOR| FORM_ACTION_BAR_HEADER| FORM_ACTION_BAR_FOOTER, true);
	SetOrientation(ORIENTATION_AUTOMATIC);
	AddOrientationEventListener(*this);

	__pHeader = GetHeader();
	__pHeader->SetStyle(HEADER_STYLE_TITLE);
	__pHeader->SetTitleText(L"Gallery");

	ButtonItem buttonItem;
	buttonItem.Construct(BUTTON_ITEM_STYLE_TEXT, ID_FOOTER__SLIDE_SHOW_START);
	buttonItem.SetText(L"Play");

	__pHeader->SetButton(BUTTON_POSITION_LEFT, buttonItem);
    __pHeader->AddActionEventListener(*this);

	CreateGallery();

	__pMutex = new (std::nothrow) Mutex();
	r = __pMutex->Create();

	__pThread = new (std::nothrow) Thread();
	__pThread->Construct(*this);
	r = __pThread->Start();

	return r;
}

result
GalleryForm::OnTerminating(void)
{
	result r = E_SUCCESS;
	// Deallocate bitmaps
	__items.RemoveAll(true);

	if (__pThread)
	{
		__pThread->Join();
		delete __pThread;
		__pThread = null;
	}

	if (__pMutex)
	{
		 delete __pMutex;
	}

	return r;
}

void
GalleryForm::OnOrientationChanged(const Control& source, OrientationStatus orientationStatus)
{
	Rectangle clientRect = GetClientAreaBounds();
	Rectangle rect = GetBounds();
	__pGallery->SetBounds(Rectangle(0, -clientRect.y, rect.width, rect.height));
	Invalidate(true);
}

void
GalleryForm::GetBitmap(void)
{
	Image* pImage = new (std::nothrow) Image();
	pImage->Construct();

	IList* pArgs = null;
	__pImage1 = pImage->DecodeN(App::GetInstance()->GetAppRootPath() + GALLERY_IMAGE_PATH1, BITMAP_PIXEL_FORMAT_ARGB8888);
	__pMutex->Acquire();
	__items.Add(*__pImage1);
	__pMutex->Release();
	pArgs = new (std::nothrow) ArrayList();
	pArgs->Add(*(new (std::nothrow) Integer(0)));
	Form::SendUserEvent(UPDATE_GALLERY, pArgs);

	__pImage2 = pImage->DecodeN(App::GetInstance()->GetAppRootPath() + GALLERY_IMAGE_PATH2, BITMAP_PIXEL_FORMAT_ARGB8888);
    __pMutex->Acquire();
	__items.Add(*__pImage2);
	__pMutex->Release();
	pArgs = new (std::nothrow) ArrayList();
	pArgs->Add(*(new (std::nothrow) Integer(1)));
	Form::SendUserEvent(UPDATE_GALLERY, pArgs);

	__pImage3 = pImage->DecodeN(App::GetInstance()->GetAppRootPath() + GALLERY_IMAGE_PATH3, BITMAP_PIXEL_FORMAT_ARGB8888);
    __pMutex->Acquire();
	__items.Add(*__pImage3);
	__pMutex->Release();
	pArgs = new (std::nothrow) ArrayList();
	pArgs->Add(*(new (std::nothrow) Integer(2)));
	Form::SendUserEvent(UPDATE_GALLERY, pArgs);

	__pImage4 = pImage->DecodeN(App::GetInstance()->GetAppRootPath() + GALLERY_IMAGE_PATH4, BITMAP_PIXEL_FORMAT_ARGB8888);
    __pMutex->Acquire();
	__items.Add(*__pImage4);
	__pMutex->Release();
	pArgs = new (std::nothrow) ArrayList();
	pArgs->Add(*(new (std::nothrow) Integer(3)));
	Form::SendUserEvent(UPDATE_GALLERY, pArgs);

	delete pImage;
}

void
GalleryForm::CreateGallery(void)
{
	Rectangle clientRect = GetClientAreaBounds();
	Rectangle rect = GetBounds();

	__pGallery = static_cast<Gallery*>(GetControl("IDC_GALLERY"));
	__pGallery->SetItemProvider(*this);
	__pGallery->AddGalleryEventListener(*this);
	AddControl(*__pGallery);

	__pGallery->SetTextOfEmptyGallery(L"Loading...");
	__pGallery->SetSlideShowAnimation(GALLERY_ANIMATION_DISSOLVE);
	__pGallery->SetSlideShowViewDuration(3000);
}

void
GalleryForm::OnActionPerformed(const Control& source, int actionId)
{
	switch (actionId)
	{
	case ID_FOOTER__SLIDE_SHOW_START:
		__pGallery->StartSlideShow(true);
		break;
	case ID_FOOTER_SLIDE_SHOW_STOP:
		__pGallery->StopSlideShow();
		break;
	}
	Invalidate(true);
}

int
GalleryForm::GetItemCount(void)
{
	return __items.GetCount();
}

GalleryItem*
GalleryForm::CreateItem(int index)
{
	GalleryItem* pGallery = new (std::nothrow) GalleryItem();
    __pMutex->Acquire();
	Tizen::Graphics::Bitmap* __pImageTemp = static_cast<Bitmap*>(__items.GetAt(index));

	switch(index)
	{
	case 0:
		pGallery->Construct(*__pImageTemp, App::GetInstance()->GetAppRootPath() + GALLERY_IMAGE_PATH1);
		break;
	case 1:
		pGallery->Construct(*__pImageTemp, App::GetInstance()->GetAppRootPath() + GALLERY_IMAGE_PATH2);
		break;
	case 2:
		pGallery->Construct(*__pImageTemp, App::GetInstance()->GetAppRootPath() + GALLERY_IMAGE_PATH3);
		break;
	case 3:
		pGallery->Construct(*__pImageTemp, App::GetInstance()->GetAppRootPath() + GALLERY_IMAGE_PATH4);
		break;
	default:
		break;
	}
	__pMutex->Release();
	return pGallery;
}

bool
GalleryForm::DeleteItem(int index, GalleryItem* pItem)
{
	delete pItem;
	return true;
}

void
GalleryForm::OnGalleryCurrentItemChanged(Gallery& view, int index)
{
	String itemText(L"");
	itemText.Format(20, L"Item %d", index+1);
	__pHeader = GetHeader();
	__pHeader->SetTitleText(itemText);
	Invalidate(true);
}

void
GalleryForm::OnGalleryItemClicked(Gallery& view, int index)
{
	if (__visible)
	{
		SetActionBarsVisible(FORM_ACTION_BAR_INDICATOR| FORM_ACTION_BAR_HEADER| FORM_ACTION_BAR_FOOTER, false);
		__visible = false;

	}
	else
	{
		SetActionBarsVisible(FORM_ACTION_BAR_INDICATOR| FORM_ACTION_BAR_HEADER| FORM_ACTION_BAR_FOOTER, true);
		__visible = true;
	}

	Invalidate(true);
}

void
GalleryForm::OnGallerySlideShowStarted(Gallery& gallery)
{
	PowerManager::KeepScreenOnState(true, false);
	if (__visible)
	{
		SetActionBarsVisible(FORM_ACTION_BAR_INDICATOR| FORM_ACTION_BAR_HEADER| FORM_ACTION_BAR_FOOTER, false);
		__visible = false;
	}

	Rectangle clientRect = GetClientAreaBounds();
	Rectangle rect = GetBounds();
	__pGallery->SetBounds(Rectangle(0, -clientRect.y, rect.width, rect.height));
	Invalidate(true);
}

void
GalleryForm::OnGallerySlideShowStopped(Gallery& gallery)
{
	PowerManager::KeepScreenOnState(false, true);
	if (!__visible)
	{
		SetActionBarsVisible(FORM_ACTION_BAR_INDICATOR| FORM_ACTION_BAR_HEADER| FORM_ACTION_BAR_FOOTER, true);
		__visible = true;
	}

	int currentItemIndex;
	currentItemIndex = __pGallery->GetCurrentItemIndex();
	String itemText(L"");
	itemText.Format(20, L"Item %d", currentItemIndex+1);
	__pHeader = GetHeader();
	__pHeader->SetTitleText(itemText);

	Rectangle clientRect = GetClientAreaBounds();
	Rectangle rect = GetBounds();
	__pGallery->SetBounds(Rectangle(0, -clientRect.y, rect.width, rect.height));

	Invalidate(true);
}

bool
GalleryForm::OnStart(void)
{
	return true;
}
void
GalleryForm::OnStop(void)
{
}

void
GalleryForm::OnUserEventReceivedN(RequestId requestId, IList* pArgs)
{
	Integer *index = (Integer*)pArgs->GetAt(0);
	int galleryIndex = index->ToInt();
	__pGallery->RefreshGallery(galleryIndex, GALLERY_REFRESH_TYPE_ITEM_ADD);

	pArgs->RemoveAll(true);
	delete pArgs;

}

Tizen::Base::Object*
GalleryForm::Run(void)
{
	GetBitmap();
	return null;
}
