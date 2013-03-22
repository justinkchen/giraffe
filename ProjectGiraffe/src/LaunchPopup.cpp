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

LaunchPopup::LaunchPopup() {
	UiApp* currentApp = UiApp::GetInstance();
	Frame* mainFrame = currentApp->GetFrame(L"GiraffeMainFrame");
	Construct(false, Dimension(mainFrame->GetBounds().width,mainFrame->GetBounds().height));
}

LaunchPopup::~LaunchPopup() {
	// TODO Auto-generated destructor stub
}

result
LaunchPopup::OnInitializing(void)
{
    result r = E_SUCCESS;

    // Creates an instance of Button to close the popup.
    Button* closeButton = new Button();
    closeButton->Construct(Rectangle(10, 10, 250, 80), L"Close Popup");
    closeButton->SetActionId(ID_BUTTON_CLOSE_POPUP);
    closeButton->AddActionEventListener(*this);

    // Adds the button to the popup
    AddControl(*closeButton);

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
            // ....
        }
        break;
    default:
        break;
    }
}

void
LaunchPopup::OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList* pArgs)
{

}
