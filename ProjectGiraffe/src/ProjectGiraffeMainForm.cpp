#include <FApp.h>
#include "ProjectGiraffeMainForm.h"

using namespace Tizen::Base;
using namespace Tizen::App;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;


ProjectGiraffeMainForm::ProjectGiraffeMainForm(void)
{
}

ProjectGiraffeMainForm::~ProjectGiraffeMainForm(void)
{
}

bool
ProjectGiraffeMainForm::Initialize(void)
{
	Construct(L"IDF_FORM");

	return true;
}

result
ProjectGiraffeMainForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO:
	// Add your initialization code here
	Header* pHeader = GetHeader();
	Footer* pFooter = GetFooter();
	if (pHeader)
	{
		pHeader->AddActionEventListener(*this);
	}

	// Initialize footer event listener
	if (pFooter)
	{
		pFooter->AddActionEventListener(*this);
	}

	// Setup back event listener
	SetFormBackEventListener(this);

	toggleButtonStatus = 0;
	return r;
}

result
ProjectGiraffeMainForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO:
	// Add your termination code here
	return r;
}

void
ProjectGiraffeMainForm::OnActionPerformed(const Tizen::Ui::Control& source, int actionId)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);

	switch(actionId)
	{
		case ID_FOOTER_ITEM1:
		{
			FooterItem toggleButton;
			Footer* pFooter = GetFooter();
			toggleButton.Construct(actionId);
			if (toggleButtonStatus == 0){
				toggleButton.SetText(L"List");
				toggleButtonStatus = 1;
				AppLog("Switching to List View");
			} else if (toggleButtonStatus == 1){
				toggleButton.SetText("Map");
				toggleButtonStatus = 0;
				AppLog("Switching to Map View");
			}
			pFooter->SetItemAt(0,toggleButton);
			pSceneManager->GoForward(SceneTransitionId(L"ID_SCNT_1"));
			break;
		}
		case ID_FOOTER_ITEM2:
		{
			pSceneManager->GoForward(SceneTransitionId(L"ID_SCNT_2"));
			break;
		}
		case ID_FOOTER_ITEM3:
		{
			pSceneManager->GoForward(SceneTransitionId(L"ID_SCNT_3"));
			break;
		}
		default:
		{
			break;
		}
	}
}

void
ProjectGiraffeMainForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source)
{
	UiApp* pApp = UiApp::GetInstance();
	AppAssert(pApp);
	pApp->Terminate();
}
