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

#include "AnimationForm.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;

const wchar_t PROGRESS_IMAGE_PATH1[] = L"00_list_process_01.png";
const wchar_t PROGRESS_IMAGE_PATH2[] = L"00_list_process_02.png";
const wchar_t PROGRESS_IMAGE_PATH3[] = L"00_list_process_03.png";
const wchar_t PROGRESS_IMAGE_PATH4[] = L"00_list_process_04.png";
const wchar_t PROGRESS_IMAGE_PATH5[] = L"00_list_process_05.png";
const wchar_t PROGRESS_IMAGE_PATH6[] = L"00_list_process_06.png";
const wchar_t PROGRESS_IMAGE_PATH7[] = L"00_list_process_07.png";
const wchar_t PROGRESS_IMAGE_PATH8[] = L"00_list_process_08.png";
const wchar_t PROGRESS_IMAGE_PATH9[] = L"00_list_process_09.png";
const wchar_t PROGRESS_IMAGE_PATH10[] = L"00_list_process_10.png";
const wchar_t PROGRESS_IMAGE_PATH11[] = L"00_list_process_11.png";
const wchar_t PROGRESS_IMAGE_PATH12[] = L"00_list_process_12.png";
const wchar_t PROGRESS_IMAGE_PATH13[] = L"00_list_process_13.png";
const wchar_t PROGRESS_IMAGE_PATH14[] = L"00_list_process_14.png";
const wchar_t PROGRESS_IMAGE_PATH15[] = L"00_list_process_15.png";
const wchar_t PROGRESS_IMAGE_PATH16[] = L"00_list_process_16.png";
const wchar_t PROGRESS_IMAGE_PATH17[] = L"00_list_process_17.png";
const wchar_t PROGRESS_IMAGE_PATH18[] = L"00_list_process_18.png";
const wchar_t PROGRESS_IMAGE_PATH19[] = L"00_list_process_19.png";
const wchar_t PROGRESS_IMAGE_PATH20[] = L"00_list_process_20.png";
const wchar_t PROGRESS_IMAGE_PATH21[] = L"00_list_process_21.png";
const wchar_t PROGRESS_IMAGE_PATH22[] = L"00_list_process_22.png";
const wchar_t PROGRESS_IMAGE_PATH23[] = L"00_list_process_23.png";
const wchar_t PROGRESS_IMAGE_PATH24[] = L"00_list_process_24.png";
const wchar_t PROGRESS_IMAGE_PATH25[] = L"00_list_process_25.png";
const wchar_t PROGRESS_IMAGE_PATH26[] = L"00_list_process_26.png";
const wchar_t PROGRESS_IMAGE_PATH27[] = L"00_list_process_27.png";
const wchar_t PROGRESS_IMAGE_PATH28[] = L"00_list_process_28.png";
const wchar_t PROGRESS_IMAGE_PATH29[] = L"00_list_process_29.png";
const wchar_t PROGRESS_IMAGE_PATH30[] = L"00_list_process_30.png";
const int DURATION = 500;
const int FRAME_COUNT = 30;
const int LABEL_HEIGHT = 60;

AnimationForm::AnimationForm(void)
	: __pAnimation(null)
	, __pAnimationFrameList(null)
	, __pAniPlayButton(null)
	, __pAniPauseButton(null)
	, __pAniStopButton(null)
{
}

AnimationForm::~AnimationForm(void)
{
	if(__pAnimationFrameList != null)
	{
		__pAnimationFrameList->RemoveAll(true);
		delete __pAnimationFrameList;
		__pAnimationFrameList = null;
	}
}

bool
AnimationForm::Initialize(void)
{
	Construct(L"IDF_FORM_ANIMATION");
	return true;
}

result
AnimationForm::OnInitializing(void)
{
	BaseForm::OnInitializing();
	result r = E_SUCCESS;

	// Add Scroll Panel Control
	ScrollPanel* pScrollPanel =static_cast <ScrollPanel*> (GetControl("IDC_SCROLLPANEL"));

	// Create Bitmap
	AppResource* pAppResource = Application::GetInstance()->GetAppResource();
	Bitmap* pBitmap1 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH1);
	Bitmap* pBitmap2 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH2);
	Bitmap* pBitmap3 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH3);
	Bitmap* pBitmap4 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH4);
	Bitmap* pBitmap5 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH5);
	Bitmap* pBitmap6 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH6);
	Bitmap* pBitmap7 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH7);
	Bitmap* pBitmap8 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH8);
	Bitmap* pBitmap9 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH9);
	Bitmap* pBitmap10 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH10);
	Bitmap* pBitmap11 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH11);
	Bitmap* pBitmap12 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH12);
	Bitmap* pBitmap13 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH13);
	Bitmap* pBitmap14 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH14);
	Bitmap* pBitmap15 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH15);
	Bitmap* pBitmap16 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH16);
	Bitmap* pBitmap17 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH17);
	Bitmap* pBitmap18 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH18);
	Bitmap* pBitmap19 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH19);
	Bitmap* pBitmap20 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH20);
	Bitmap* pBitmap21 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH21);
	Bitmap* pBitmap22 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH22);
	Bitmap* pBitmap23 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH23);
	Bitmap* pBitmap24 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH24);
	Bitmap* pBitmap25 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH25);
	Bitmap* pBitmap26 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH26);
	Bitmap* pBitmap27 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH27);
	Bitmap* pBitmap28 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH28);
	Bitmap* pBitmap29 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH29);
	Bitmap* pBitmap30 = pAppResource->GetBitmapN(PROGRESS_IMAGE_PATH30);

	// Create AnimationFrames
	long duration = DURATION / FRAME_COUNT;
	AnimationFrame* pAniFrame1 = new (std::nothrow) AnimationFrame(*pBitmap1, duration);
	AnimationFrame* pAniFrame2 = new (std::nothrow) AnimationFrame(*pBitmap2, duration);
	AnimationFrame* pAniFrame3 = new (std::nothrow) AnimationFrame(*pBitmap3, duration);
	AnimationFrame* pAniFrame4 = new (std::nothrow) AnimationFrame(*pBitmap4, duration);
	AnimationFrame* pAniFrame5 = new (std::nothrow) AnimationFrame(*pBitmap5, duration);
	AnimationFrame* pAniFrame6 = new (std::nothrow) AnimationFrame(*pBitmap6, duration);
	AnimationFrame* pAniFrame7 = new (std::nothrow) AnimationFrame(*pBitmap7, duration);
	AnimationFrame* pAniFrame8 = new (std::nothrow) AnimationFrame(*pBitmap8, duration);
	AnimationFrame* pAniFrame9 = new (std::nothrow) AnimationFrame(*pBitmap9, duration);
	AnimationFrame* pAniFrame10 = new (std::nothrow) AnimationFrame(*pBitmap10, duration);
	AnimationFrame* pAniFrame11 = new (std::nothrow) AnimationFrame(*pBitmap11, duration);
	AnimationFrame* pAniFrame12 = new (std::nothrow) AnimationFrame(*pBitmap12, duration);
	AnimationFrame* pAniFrame13 = new (std::nothrow) AnimationFrame(*pBitmap13, duration);
	AnimationFrame* pAniFrame14 = new (std::nothrow) AnimationFrame(*pBitmap14, duration);
	AnimationFrame* pAniFrame15 = new (std::nothrow) AnimationFrame(*pBitmap15, duration);
	AnimationFrame* pAniFrame16 = new (std::nothrow) AnimationFrame(*pBitmap16, duration);
	AnimationFrame* pAniFrame17 = new (std::nothrow) AnimationFrame(*pBitmap17, duration);
	AnimationFrame* pAniFrame18 = new (std::nothrow) AnimationFrame(*pBitmap18, duration);
	AnimationFrame* pAniFrame19 = new (std::nothrow) AnimationFrame(*pBitmap19, duration);
	AnimationFrame* pAniFrame20 = new (std::nothrow) AnimationFrame(*pBitmap20, duration);
	AnimationFrame* pAniFrame21 = new (std::nothrow) AnimationFrame(*pBitmap21, duration);
	AnimationFrame* pAniFrame22 = new (std::nothrow) AnimationFrame(*pBitmap22, duration);
	AnimationFrame* pAniFrame23 = new (std::nothrow) AnimationFrame(*pBitmap23, duration);
	AnimationFrame* pAniFrame24 = new (std::nothrow) AnimationFrame(*pBitmap24, duration);
	AnimationFrame* pAniFrame25 = new (std::nothrow) AnimationFrame(*pBitmap25, duration);
	AnimationFrame* pAniFrame26 = new (std::nothrow) AnimationFrame(*pBitmap26, duration);
	AnimationFrame* pAniFrame27 = new (std::nothrow) AnimationFrame(*pBitmap27, duration);
	AnimationFrame* pAniFrame28 = new (std::nothrow) AnimationFrame(*pBitmap28, duration);
	AnimationFrame* pAniFrame29 = new (std::nothrow) AnimationFrame(*pBitmap29, duration);
	AnimationFrame* pAniFrame30 = new (std::nothrow) AnimationFrame(*pBitmap30, duration);

	__pAnimationFrameList = new (std::nothrow) ArrayList();
	__pAnimationFrameList->Construct();
	__pAnimationFrameList->Add(*pAniFrame1);
	__pAnimationFrameList->Add(*pAniFrame2);
	__pAnimationFrameList->Add(*pAniFrame3);
	__pAnimationFrameList->Add(*pAniFrame4);
	__pAnimationFrameList->Add(*pAniFrame5);
	__pAnimationFrameList->Add(*pAniFrame6);
	__pAnimationFrameList->Add(*pAniFrame7);
	__pAnimationFrameList->Add(*pAniFrame8);
	__pAnimationFrameList->Add(*pAniFrame9);
	__pAnimationFrameList->Add(*pAniFrame10);
	__pAnimationFrameList->Add(*pAniFrame11);
	__pAnimationFrameList->Add(*pAniFrame12);
	__pAnimationFrameList->Add(*pAniFrame13);
	__pAnimationFrameList->Add(*pAniFrame14);
	__pAnimationFrameList->Add(*pAniFrame15);
	__pAnimationFrameList->Add(*pAniFrame16);
	__pAnimationFrameList->Add(*pAniFrame17);
	__pAnimationFrameList->Add(*pAniFrame18);
	__pAnimationFrameList->Add(*pAniFrame19);
	__pAnimationFrameList->Add(*pAniFrame20);
	__pAnimationFrameList->Add(*pAniFrame21);
	__pAnimationFrameList->Add(*pAniFrame22);
	__pAnimationFrameList->Add(*pAniFrame23);
	__pAnimationFrameList->Add(*pAniFrame24);
	__pAnimationFrameList->Add(*pAniFrame25);
	__pAnimationFrameList->Add(*pAniFrame26);
	__pAnimationFrameList->Add(*pAniFrame27);
	__pAnimationFrameList->Add(*pAniFrame28);
	__pAnimationFrameList->Add(*pAniFrame29);
	__pAnimationFrameList->Add(*pAniFrame30);

	// Deallocate a Bitmap.
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
	delete pBitmap30;

	__pAnimation = new (std::nothrow) Animation();
	__pAnimation->Construct(Rectangle(133, 247, 64, 64), *__pAnimationFrameList);
	__pAnimation->SetRepeatCount(10);
	__pAnimation->AddAnimationEventListener(*this);

	__pAniPlayButton = static_cast<Button*>(GetControl("IDC_BUTTON_PLAY", true));
	__pAniPauseButton = static_cast<Button*>(GetControl("IDC_BUTTON_PAUSE", true));
	__pAniStopButton = static_cast<Button*>(GetControl("IDC_BUTTON_STOP", true));

	__pAniPlayButton->SetActionId(ID_BUTTON_ANIMATION_PLAY);
	__pAniPauseButton->SetActionId(ID_BUTTON_ANIMATION_PAUSE);
	__pAniStopButton->SetActionId(ID_BUTTON_ANIMATION_STOP);

	__pAniPlayButton->AddActionEventListener(*this);
	__pAniPauseButton->AddActionEventListener(*this);
	__pAniStopButton->AddActionEventListener(*this);

	__pAniPauseButton->SetEnabled(false);
	__pAniStopButton->SetEnabled(false);

	pScrollPanel->AddControl(*__pAnimation);
	AddControl(*pScrollPanel);

	return r;
}

void
AnimationForm::OnActionPerformed(const Control& source, int actionId)
{
	switch(actionId)
	{
	case ID_BUTTON_ANIMATION_PLAY:
		__pAniPlayButton->SetEnabled(false);
		__pAniPauseButton->SetEnabled(true);
		__pAniStopButton->SetEnabled(true);
		__pAnimation->Play();
		break;
	case ID_BUTTON_ANIMATION_PAUSE:
		__pAniPlayButton->SetText("Resume");
		__pAniPlayButton->SetEnabled(true);
		__pAnimation->Pause();
		break;
	case ID_BUTTON_ANIMATION_STOP:
		__pAniPlayButton->SetText("Play");
		__pAniPlayButton->SetEnabled(true);
		__pAniPauseButton->SetEnabled(false);
		__pAniStopButton->SetEnabled(false);
		__pAnimation->Stop();
		break;
	default:
		break;
	}
	Invalidate(true);
}

void
AnimationForm::OnAnimationStopped(const Control& source)
{
	__pAniPlayButton->SetEnabled(true);
	__pAniPauseButton->SetEnabled(false);
	__pAniStopButton->SetEnabled(false);
	__pAniPlayButton->SetText("Play");
	Invalidate(true);
}

