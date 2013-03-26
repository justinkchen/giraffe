/*
 * LaunchPopup.cpp
 *
 *  Created on: Mar 21, 2013
 *      Author: Justin
 */

#include "LaunchPopup.h"
#include <FGraphics.h>


using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;

#define kDebugCloseButton 1

LaunchPopup::LaunchPopup() {
	UiApp* currentApp = UiApp::GetInstance();
	Frame* mainFrame = currentApp->GetFrame(L"GiraffeMainFrame");

	_popupLayout.Construct();
	Construct(_popupLayout, false, Dimension(mainFrame->GetBounds().width,mainFrame->GetBounds().height));

	_locationFound = false;
}

LaunchPopup::~LaunchPopup() {
	// TODO Auto-generated destructor stub
}

result
LaunchPopup::OnInitializing(void)
{
    result r = E_SUCCESS;

    // Initialize Launch Image
    AppResource* appResource = Application::GetInstance()->GetAppResource();
	if (appResource != null)
	{
		Bitmap *bitmap0 = appResource->GetBitmapN("00_list_process_01.png");
		Bitmap *bitmap1 = appResource->GetBitmapN("00_list_process_02.png");
		Bitmap *bitmap2 = appResource->GetBitmapN("00_list_process_03.png");
		Bitmap *bitmap3 = appResource->GetBitmapN("00_list_process_04.png");
		Bitmap *bitmap4 = appResource->GetBitmapN("00_list_process_05.png");
		Bitmap *bitmap5 = appResource->GetBitmapN("00_list_process_06.png");
		Bitmap *bitmap6 = appResource->GetBitmapN("00_list_process_07.png");
		Bitmap *bitmap7 = appResource->GetBitmapN("00_list_process_08.png");
		Bitmap *bitmap8 = appResource->GetBitmapN("00_list_process_09.png");
		Bitmap *bitmap9 = appResource->GetBitmapN("00_list_process_10.png");
		Bitmap *bitmap10 = appResource->GetBitmapN("00_list_process_11.png");
		Bitmap *bitmap11 = appResource->GetBitmapN("00_list_process_12.png");
		Bitmap *bitmap12 = appResource->GetBitmapN("00_list_process_13.png");
		Bitmap *bitmap13 = appResource->GetBitmapN("00_list_process_14.png");
		Bitmap *bitmap14 = appResource->GetBitmapN("00_list_process_15.png");
		Bitmap *bitmap15 = appResource->GetBitmapN("00_list_process_16.png");
		Bitmap *bitmap16 = appResource->GetBitmapN("00_list_process_17.png");
		Bitmap *bitmap17 = appResource->GetBitmapN("00_list_process_18.png");
		Bitmap *bitmap18 = appResource->GetBitmapN("00_list_process_19.png");
		Bitmap *bitmap19 = appResource->GetBitmapN("00_list_process_20.png");
		Bitmap *bitmap20 = appResource->GetBitmapN("00_list_process_21.png");
		Bitmap *bitmap21 = appResource->GetBitmapN("00_list_process_22.png");
		Bitmap *bitmap22 = appResource->GetBitmapN("00_list_process_23.png");
		Bitmap *bitmap23 = appResource->GetBitmapN("00_list_process_24.png");
		Bitmap *bitmap24 = appResource->GetBitmapN("00_list_process_25.png");
		Bitmap *bitmap25 = appResource->GetBitmapN("00_list_process_26.png");
		Bitmap *bitmap26 = appResource->GetBitmapN("00_list_process_27.png");
		Bitmap *bitmap27 = appResource->GetBitmapN("00_list_process_28.png");
		Bitmap *bitmap28 = appResource->GetBitmapN("00_list_process_29.png");
		Bitmap *bitmap29 = appResource->GetBitmapN("00_list_process_30.png");

		// Create AnimationFrames
		long duration = DURATION / PROGRESS_COUNT;
		AnimationFrame *aniFrame1 = new (std::nothrow) AnimationFrame(*bitmap0, duration);
		AnimationFrame *aniFrame2 = new (std::nothrow) AnimationFrame(*bitmap1, duration);
		AnimationFrame *aniFrame3 = new (std::nothrow) AnimationFrame(*bitmap2, duration);
		AnimationFrame *aniFrame4 = new (std::nothrow) AnimationFrame(*bitmap3, duration);
		AnimationFrame *aniFrame5 = new (std::nothrow) AnimationFrame(*bitmap4, duration);
		AnimationFrame *aniFrame6 = new (std::nothrow) AnimationFrame(*bitmap5, duration);
		AnimationFrame *aniFrame7 = new (std::nothrow) AnimationFrame(*bitmap6, duration);
		AnimationFrame *aniFrame8 = new (std::nothrow) AnimationFrame(*bitmap7, duration);
		AnimationFrame *aniFrame9 = new (std::nothrow) AnimationFrame(*bitmap8, duration);
		AnimationFrame *aniFrame10 = new (std::nothrow) AnimationFrame(*bitmap9, duration);
		AnimationFrame *aniFrame11 = new (std::nothrow) AnimationFrame(*bitmap10, duration);
		AnimationFrame *aniFrame12 = new (std::nothrow) AnimationFrame(*bitmap11, duration);
		AnimationFrame *aniFrame13 = new (std::nothrow) AnimationFrame(*bitmap12, duration);
		AnimationFrame *aniFrame14 = new (std::nothrow) AnimationFrame(*bitmap13, duration);
		AnimationFrame *aniFrame15 = new (std::nothrow) AnimationFrame(*bitmap14, duration);
		AnimationFrame *aniFrame16 = new (std::nothrow) AnimationFrame(*bitmap15, duration);
		AnimationFrame *aniFrame17 = new (std::nothrow) AnimationFrame(*bitmap16, duration);
		AnimationFrame *aniFrame18 = new (std::nothrow) AnimationFrame(*bitmap17, duration);
		AnimationFrame *aniFrame19 = new (std::nothrow) AnimationFrame(*bitmap18, duration);
		AnimationFrame *aniFrame20 = new (std::nothrow) AnimationFrame(*bitmap19, duration);
		AnimationFrame *aniFrame21 = new (std::nothrow) AnimationFrame(*bitmap20, duration);
		AnimationFrame *aniFrame22 = new (std::nothrow) AnimationFrame(*bitmap21, duration);
		AnimationFrame *aniFrame23 = new (std::nothrow) AnimationFrame(*bitmap22, duration);
		AnimationFrame *aniFrame24 = new (std::nothrow) AnimationFrame(*bitmap23, duration);
		AnimationFrame *aniFrame25 = new (std::nothrow) AnimationFrame(*bitmap24, duration);
		AnimationFrame *aniFrame26 = new (std::nothrow) AnimationFrame(*bitmap25, duration);
		AnimationFrame *aniFrame27 = new (std::nothrow) AnimationFrame(*bitmap26, duration);
		AnimationFrame *aniFrame28 = new (std::nothrow) AnimationFrame(*bitmap27, duration);
		AnimationFrame *aniFrame29 = new (std::nothrow) AnimationFrame(*bitmap28, duration);
		AnimationFrame *aniFrame30 = new (std::nothrow) AnimationFrame(*bitmap29, duration);

		// Create AnimationList
		_animationFrameList = new (std::nothrow) ArrayList();
		_animationFrameList->Construct();
		_animationFrameList->Add(*aniFrame1);
		_animationFrameList->Add(*aniFrame2);
		_animationFrameList->Add(*aniFrame3);
		_animationFrameList->Add(*aniFrame4);
		_animationFrameList->Add(*aniFrame5);
		_animationFrameList->Add(*aniFrame6);
		_animationFrameList->Add(*aniFrame7);
		_animationFrameList->Add(*aniFrame8);
		_animationFrameList->Add(*aniFrame9);
		_animationFrameList->Add(*aniFrame10);
		_animationFrameList->Add(*aniFrame11);
		_animationFrameList->Add(*aniFrame12);
		_animationFrameList->Add(*aniFrame13);
		_animationFrameList->Add(*aniFrame14);
		_animationFrameList->Add(*aniFrame15);
		_animationFrameList->Add(*aniFrame16);
		_animationFrameList->Add(*aniFrame17);
		_animationFrameList->Add(*aniFrame18);
		_animationFrameList->Add(*aniFrame19);
		_animationFrameList->Add(*aniFrame20);
		_animationFrameList->Add(*aniFrame21);
		_animationFrameList->Add(*aniFrame22);
		_animationFrameList->Add(*aniFrame23);
		_animationFrameList->Add(*aniFrame24);
		_animationFrameList->Add(*aniFrame25);
		_animationFrameList->Add(*aniFrame26);
		_animationFrameList->Add(*aniFrame27);
		_animationFrameList->Add(*aniFrame28);
		_animationFrameList->Add(*aniFrame29);
		_animationFrameList->Add(*aniFrame30);

		// Deallocate a Bitmap.
		delete bitmap0;
		delete bitmap1;
		delete bitmap2;
		delete bitmap3;
		delete bitmap4;
		delete bitmap5;
		delete bitmap6;
		delete bitmap7;
		delete bitmap8;
		delete bitmap9;
		delete bitmap10;
		delete bitmap11;
		delete bitmap12;
		delete bitmap13;
		delete bitmap14;
		delete bitmap15;
		delete bitmap16;
		delete bitmap17;
		delete bitmap18;
		delete bitmap19;
		delete bitmap20;
		delete bitmap21;
		delete bitmap22;
		delete bitmap23;
		delete bitmap24;
		delete bitmap25;
		delete bitmap26;
		delete bitmap27;
		delete bitmap28;
		delete bitmap29;
	}

    _launchAnimation = new Animation();
    _launchAnimation->Construct(Rectangle(0,5*GetClientAreaBounds().height/6,100,100), *_animationFrameList);
    _launchAnimation->SetRepeatCount(5);
    _launchAnimation->AddAnimationEventListener(*this);
    AddControl(*_launchAnimation);
    _launchAnimation->Play();

    // Creates instances of Label and an instance of Button
    Label* titleLabel = new Label();
    titleLabel->Construct(Rectangle(0,GetClientAreaBounds().height/4,GetClientAreaBounds().width,100), L"Project Giraffe");
    titleLabel->SetTextConfig(75, LABEL_TEXT_STYLE_BOLD);
    titleLabel->SetBackgroundColor(Color(0x00, 0x00, 0x00, 0x00));
    AddControl(*titleLabel);

    Label* subtitleLabel = new Label();
    subtitleLabel->Construct(Rectangle(0,0,GetClientAreaBounds().width,100), L"Keep moving!");
    subtitleLabel->SetTextConfig(40, LABEL_TEXT_STYLE_NORMAL);
    subtitleLabel->SetBackgroundColor(Color(0x00, 0x00, 0x00, 0x00));
    AddControl(*subtitleLabel);

    Label* loadingLabel = new Label();
    loadingLabel->Construct(Rectangle(0,8*GetClientAreaBounds().height/9,GetClientAreaBounds().width,100), L"...Searching for Location...");
    loadingLabel->SetTextConfig(20, LABEL_TEXT_STYLE_ITALIC);
    loadingLabel->SetBackgroundColor(Color(0x00, 0x00, 0xC0, 0x00));
    AddControl(*loadingLabel);

    // Creates an instance of Button to close the popup.
    Button* closeButton = new Button();
    closeButton->Construct(Rectangle(0, 2*GetClientAreaBounds().height/5, GetClientAreaBounds().width/2,100), L"Close Popup\n(in case location not found)");
    closeButton->SetActionId(ID_BUTTON_CLOSE_POPUP);
    closeButton->AddActionEventListener(*this);
    closeButton->SetTextSize(20);

    // Adding logo
    Tizen::Base::String filePath = App::GetInstance()->GetAppRootPath() + L"res/Image/tizen_logo.jpg";
    _bitmapControl = BitmapControl::ConstructFromPath(filePath,Rectangle(0, 3*GetClientAreaBounds().height/5, 175,175), true);
    _bitmapControl->Draw();
    AddControl(*_bitmapControl);

#if kDebugCloseButton
    AddControl(*closeButton);
#else
    // Don't add control
#endif

    // Sets relations each label and button
    _popupLayout.SetCenterAligned(*_launchAnimation, CENTER_ALIGN_HORIZONTAL);
    _popupLayout.SetCenterAligned(*_bitmapControl, CENTER_ALIGN_HORIZONTAL);
    _popupLayout.SetCenterAligned(*titleLabel, CENTER_ALIGN_HORIZONTAL);
    _popupLayout.SetCenterAligned(*subtitleLabel, CENTER_ALIGN_HORIZONTAL);
    _popupLayout.SetCenterAligned(*loadingLabel, CENTER_ALIGN_HORIZONTAL);
    _popupLayout.SetCenterAligned(*closeButton, CENTER_ALIGN_HORIZONTAL);

    _popupLayout.SetRelation(*subtitleLabel, *titleLabel, RECT_EDGE_RELATION_TOP_TO_BOTTOM);
    _popupLayout.SetMargin(*subtitleLabel, 10, 10, 10, 10);

    return r;
}

result
LaunchPopup::OnTerminating(void)
{
	RemoveAllControls();

	result r = E_SUCCESS;

	return r;
}

void
LaunchPopup::ShowPopup(void)
{
    SetShowState(true);
    Show();
}

void
LaunchPopup::HidePopup(void)
{
    SetShowState(false);
    Invalidate(true);
}

// IActionEventListener implementation
void
LaunchPopup::OnActionPerformed(const Control& source, int actionId)
{
    switch (actionId)
    {
    case ID_BUTTON_CLOSE_POPUP:
	{
		HidePopup();
	}
	break;
    default:
        break;
    }
}

void
LaunchPopup::OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList* pArgs)
{
	AppLogDebug("We received an event.");
	if(!_locationFound){
		if (requestId == 101) // Location Found
		{
			AppLogDebug("Location found, closing Launch popup");
			this->HidePopup();
			_locationFound = true;
		}
	}
	if(pArgs)
	{
		pArgs->RemoveAll(true);
		delete pArgs;
	}
}

void
LaunchPopup::OnAnimationStopped(const Control& source){
	// Start Again
	_launchAnimation->Play();
}
