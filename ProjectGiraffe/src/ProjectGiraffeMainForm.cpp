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
	if (pHeader)
	{
		pHeader->AddActionEventListener(*this);
	}
	Footer* pFooter = GetFooter();
	if (pFooter)
	{
		pFooter->AddActionEventListener(*this);
	}

	// Setup back event listener
	SetFormBackEventListener(this);

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
	Header* pHeader = GetHeader();

	switch(actionId)
	{
	case ID_FOOTER_ITEM1:
		pSceneManager->GoForward(SceneTransitionId(L"ID_SCNT_1"));
		pHeader->SetTitleText(L"Nearby Graffiti");
		break;
	case ID_FOOTER_ITEM2:
		pSceneManager->GoForward(SceneTransitionId(L"ID_SCNT_2"));
		pHeader->SetTitleText(L"Graffiti Map");
		break;
	case ID_FOOTER_ITEM3:
		pSceneManager->GoForward(SceneTransitionId(L"ID_SCNT_3"));
		pHeader->SetTitleText(L"Post Graffiti");
		break;
	case ID_FOOTER_ITEM4:
		pSceneManager->GoForward(SceneTransitionId(L"ID_SCNT_4"));
		pHeader->SetTitleText(L"Profile");
		break;
	case ID_FOOTER_ITEM5:
		pSceneManager->GoForward(SceneTransitionId(L"ID_SCNT_5"));
		pHeader->SetTitleText(L"Settings");
		break;
	default:
		break;
	}
}

void
ProjectGiraffeMainForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source)
{
	UiApp* pApp = UiApp::GetInstance();
	AppAssert(pApp);
	pApp->Terminate();
}

void
ProjectGiraffeMainForm::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs)
{
	// TODO: Add your implementation codes here

}

void
ProjectGiraffeMainForm::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
								const Tizen::Ui::Scenes::SceneId& nextSceneId)
{
	// TODO: Add your implementation codes here

}
