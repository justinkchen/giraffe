/*
 * LoadingPopup.cpp
 *
 *  Created on: Mar 21, 2013
 *      Author: Johan
 */

#include "LoadingPopup.h"


using namespace Tizen::Graphics;
using namespace Tizen::Ui::Controls;
using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;

LoadingPopup::LoadingPopup()
	: _animation(null)
	, _animationFrameList(null)
	{


	Construct(false, Dimension(100,100));
	AppResource* pAppResource = Application::GetInstance()->GetAppResource();
	if (pAppResource != null)
	{
		Bitmap *pBitmap0 = pAppResource->GetBitmapN("00_list_process_01.png");
		Bitmap *pBitmap1 = pAppResource->GetBitmapN("00_list_process_02.png");
		Bitmap *pBitmap2 = pAppResource->GetBitmapN("00_list_process_03.png");
		Bitmap *pBitmap3 = pAppResource->GetBitmapN("00_list_process_04.png");
		Bitmap *pBitmap4 = pAppResource->GetBitmapN("00_list_process_05.png");
		Bitmap *pBitmap5 = pAppResource->GetBitmapN("00_list_process_06.png");
		Bitmap *pBitmap6 = pAppResource->GetBitmapN("00_list_process_07.png");
		Bitmap *pBitmap7 = pAppResource->GetBitmapN("00_list_process_08.png");
		Bitmap *pBitmap8 = pAppResource->GetBitmapN("00_list_process_09.png");
		Bitmap *pBitmap9 = pAppResource->GetBitmapN("00_list_process_10.png");
		Bitmap *pBitmap10 = pAppResource->GetBitmapN("00_list_process_11.png");
		Bitmap *pBitmap11 = pAppResource->GetBitmapN("00_list_process_12.png");
		Bitmap *pBitmap12 = pAppResource->GetBitmapN("00_list_process_13.png");
		Bitmap *pBitmap13 = pAppResource->GetBitmapN("00_list_process_14.png");
		Bitmap *pBitmap14 = pAppResource->GetBitmapN("00_list_process_15.png");
		Bitmap *pBitmap15 = pAppResource->GetBitmapN("00_list_process_16.png");
		Bitmap *pBitmap16 = pAppResource->GetBitmapN("00_list_process_17.png");
		Bitmap *pBitmap17 = pAppResource->GetBitmapN("00_list_process_18.png");
		Bitmap *pBitmap18 = pAppResource->GetBitmapN("00_list_process_19.png");
		Bitmap *pBitmap19 = pAppResource->GetBitmapN("00_list_process_20.png");
		Bitmap *pBitmap20 = pAppResource->GetBitmapN("00_list_process_21.png");
		Bitmap *pBitmap21 = pAppResource->GetBitmapN("00_list_process_22.png");
		Bitmap *pBitmap22 = pAppResource->GetBitmapN("00_list_process_23.png");
		Bitmap *pBitmap23 = pAppResource->GetBitmapN("00_list_process_24.png");
		Bitmap *pBitmap24 = pAppResource->GetBitmapN("00_list_process_25.png");
		Bitmap *pBitmap25 = pAppResource->GetBitmapN("00_list_process_26.png");
		Bitmap *pBitmap26 = pAppResource->GetBitmapN("00_list_process_27.png");
		Bitmap *pBitmap27 = pAppResource->GetBitmapN("00_list_process_28.png");
		Bitmap *pBitmap28 = pAppResource->GetBitmapN("00_list_process_29.png");
		Bitmap *pBitmap29 = pAppResource->GetBitmapN("00_list_process_30.png");

		// Create AnimationFrames
		long duration = 17;
		AnimationFrame *pAniFrame1 = new (std::nothrow) AnimationFrame(*pBitmap0, duration);
		AnimationFrame *pAniFrame2 = new (std::nothrow) AnimationFrame(*pBitmap1, duration);
		AnimationFrame *pAniFrame3 = new (std::nothrow) AnimationFrame(*pBitmap2, duration);
		AnimationFrame *pAniFrame4 = new (std::nothrow) AnimationFrame(*pBitmap3, duration);
		AnimationFrame *pAniFrame5 = new (std::nothrow) AnimationFrame(*pBitmap4, duration);
		AnimationFrame *pAniFrame6 = new (std::nothrow) AnimationFrame(*pBitmap5, duration);
		AnimationFrame *pAniFrame7 = new (std::nothrow) AnimationFrame(*pBitmap6, duration);
		AnimationFrame *pAniFrame8 = new (std::nothrow) AnimationFrame(*pBitmap7, duration);
		AnimationFrame *pAniFrame9 = new (std::nothrow) AnimationFrame(*pBitmap8, duration);
		AnimationFrame *pAniFrame10 = new (std::nothrow) AnimationFrame(*pBitmap9, duration);
		AnimationFrame *pAniFrame11 = new (std::nothrow) AnimationFrame(*pBitmap10, duration);
		AnimationFrame *pAniFrame12 = new (std::nothrow) AnimationFrame(*pBitmap11, duration);
		AnimationFrame *pAniFrame13 = new (std::nothrow) AnimationFrame(*pBitmap12, duration);
		AnimationFrame *pAniFrame14 = new (std::nothrow) AnimationFrame(*pBitmap13, duration);
		AnimationFrame *pAniFrame15 = new (std::nothrow) AnimationFrame(*pBitmap14, duration);
		AnimationFrame *pAniFrame16 = new (std::nothrow) AnimationFrame(*pBitmap15, duration);
		AnimationFrame *pAniFrame17 = new (std::nothrow) AnimationFrame(*pBitmap16, duration);
		AnimationFrame *pAniFrame18 = new (std::nothrow) AnimationFrame(*pBitmap17, duration);
		AnimationFrame *pAniFrame19 = new (std::nothrow) AnimationFrame(*pBitmap18, duration);
		AnimationFrame *pAniFrame20 = new (std::nothrow) AnimationFrame(*pBitmap19, duration);
		AnimationFrame *pAniFrame21 = new (std::nothrow) AnimationFrame(*pBitmap20, duration);
		AnimationFrame *pAniFrame22 = new (std::nothrow) AnimationFrame(*pBitmap21, duration);
		AnimationFrame *pAniFrame23 = new (std::nothrow) AnimationFrame(*pBitmap22, duration);
		AnimationFrame *pAniFrame24 = new (std::nothrow) AnimationFrame(*pBitmap23, duration);
		AnimationFrame *pAniFrame25 = new (std::nothrow) AnimationFrame(*pBitmap24, duration);
		AnimationFrame *pAniFrame26 = new (std::nothrow) AnimationFrame(*pBitmap25, duration);
		AnimationFrame *pAniFrame27 = new (std::nothrow) AnimationFrame(*pBitmap26, duration);
		AnimationFrame *pAniFrame28 = new (std::nothrow) AnimationFrame(*pBitmap27, duration);
		AnimationFrame *pAniFrame29 = new (std::nothrow) AnimationFrame(*pBitmap28, duration);
		AnimationFrame *pAniFrame30 = new (std::nothrow) AnimationFrame(*pBitmap29, duration);

		// Create AnimationList
		_animationFrameList = new (std::nothrow) ArrayList();
		_animationFrameList->Construct();
		_animationFrameList->Add(*pAniFrame1);
		_animationFrameList->Add(*pAniFrame2);
		_animationFrameList->Add(*pAniFrame3);
		_animationFrameList->Add(*pAniFrame4);
		_animationFrameList->Add(*pAniFrame5);
		_animationFrameList->Add(*pAniFrame6);
		_animationFrameList->Add(*pAniFrame7);
		_animationFrameList->Add(*pAniFrame8);
		_animationFrameList->Add(*pAniFrame9);
		_animationFrameList->Add(*pAniFrame10);
		_animationFrameList->Add(*pAniFrame11);
		_animationFrameList->Add(*pAniFrame12);
		_animationFrameList->Add(*pAniFrame13);
		_animationFrameList->Add(*pAniFrame14);
		_animationFrameList->Add(*pAniFrame15);
		_animationFrameList->Add(*pAniFrame16);
		_animationFrameList->Add(*pAniFrame17);
		_animationFrameList->Add(*pAniFrame18);
		_animationFrameList->Add(*pAniFrame19);
		_animationFrameList->Add(*pAniFrame20);
		_animationFrameList->Add(*pAniFrame21);
		_animationFrameList->Add(*pAniFrame22);
		_animationFrameList->Add(*pAniFrame23);
		_animationFrameList->Add(*pAniFrame24);
		_animationFrameList->Add(*pAniFrame25);
		_animationFrameList->Add(*pAniFrame26);
		_animationFrameList->Add(*pAniFrame27);
		_animationFrameList->Add(*pAniFrame28);
		_animationFrameList->Add(*pAniFrame29);
		_animationFrameList->Add(*pAniFrame30);

		// Deallocate a Bitmap.
		delete pBitmap0;
		delete pBitmap1;
		delete pBitmap2;
		delete pBitmap3;
		delete pBitmap4;
		delete pBitmap5;
		delete pBitmap6;
		delete pBitmap7;
		delete pBitmap8;
		delete pBitmap9;
		delete pBitmap10;
		delete pBitmap11;
		delete pBitmap12;
		delete pBitmap13;
		delete pBitmap14;
		delete pBitmap15;
		delete pBitmap16;
		delete pBitmap17;
		delete pBitmap18;
		delete pBitmap19;
		delete pBitmap20;
		delete pBitmap21;
		delete pBitmap22;
		delete pBitmap23;
		delete pBitmap24;
		delete pBitmap25;
		delete pBitmap26;
		delete pBitmap27;
		delete pBitmap28;
		delete pBitmap29;

		// Create Animation
		_animation = new (std::nothrow) Animation();

		Rectangle clientArea = GetClientAreaBounds();

		_animation->Construct(Rectangle(clientArea.x-40, clientArea.y, 100, 100), *_animationFrameList);
		_animation->SetRepeatCount(10000);
		AddControl(*_animation);

	}

}

LoadingPopup::~LoadingPopup() {
	if(_animationFrameList != null)
	{
		_animationFrameList->RemoveAll(true);
		delete _animationFrameList;
		_animationFrameList = null;
	}
}

void
LoadingPopup::ShowPopup(void)
{
	SetShowState(true);
	_animation->Play();
	Show();
}

void
LoadingPopup::HidePopup(void)
{
	SetShowState(false);
	_animation->Stop();
	Invalidate(true);
}
