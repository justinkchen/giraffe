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
		AppResource* pAppResource = Application::GetInstance()->GetAppResource();

		Tizen::Graphics::Bitmap* pNearbyBitmap = pAppResource->GetBitmapN(L"74-location.png");
		Tizen::Graphics::Bitmap* pMapBitmap = pAppResource->GetBitmapN(L"73-radar.png");
		Tizen::Graphics::Bitmap* pSpraycanBitmap = pAppResource->GetBitmapN(L"bluespraycan.png");
		Tizen::Graphics::Bitmap* pProfileBitmap = pAppResource->GetBitmapN(L"111-user.png");
		Tizen::Graphics::Bitmap* pSettingsBitmap = pAppResource->GetBitmapN(L"19-gear.png");

		FooterItem footerItem1;
		FooterItem footerItem2;
		FooterItem footerItem3;
		FooterItem footerItem4;
		FooterItem footerItem5;

		footerItem1.Construct(ID_FOOTER_ITEM1);
		footerItem2.Construct(ID_FOOTER_ITEM2);
		footerItem3.Construct(ID_FOOTER_ITEM3);
		footerItem4.Construct(ID_FOOTER_ITEM4);
		footerItem5.Construct(ID_FOOTER_ITEM5);

		footerItem1.SetIcon(FOOTER_ITEM_STATUS_NORMAL, pNearbyBitmap);
		footerItem2.SetIcon(FOOTER_ITEM_STATUS_NORMAL, pMapBitmap);
		footerItem3.SetIcon(FOOTER_ITEM_STATUS_NORMAL, pSpraycanBitmap);
		footerItem4.SetIcon(FOOTER_ITEM_STATUS_NORMAL, pProfileBitmap);
		footerItem5.SetIcon(FOOTER_ITEM_STATUS_NORMAL, pSettingsBitmap);

		pFooter->InsertItemAt(0, footerItem1);
		pFooter->InsertItemAt(1, footerItem2);
		pFooter->InsertItemAt(2, footerItem3);
		pFooter->InsertItemAt(3, footerItem4);
		pFooter->InsertItemAt(4, footerItem5);

		pFooter->AddActionEventListener(*this);

		pFooter->SetItemColor(FOOTER_ITEM_STATUS_DISABLED, Tizen::Graphics::Color(0x00, 128, 255));
		pFooter->SetItemEnabled(0,false);
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
	Footer* pFooter = GetFooter();
	switch(actionId)
	{
	case ID_FOOTER_ITEM1:
		pSceneManager->GoForward(SceneTransitionId(L"ID_SCNT_1"));
		pHeader->SetTitleText(L"Nearby Graffiti");
		pFooter->SetItemColor(FOOTER_ITEM_STATUS_DISABLED, Tizen::Graphics::Color(0x00, 128, 255));
		pFooter->SetItemEnabled(0,false);
		pFooter->SetItemEnabled(1,true);
		pFooter->SetItemEnabled(2,true);
		pFooter->SetItemEnabled(3,true);
		pFooter->SetItemEnabled(4,true);
		break;
	case ID_FOOTER_ITEM2:
		pSceneManager->GoForward(SceneTransitionId(L"ID_SCNT_2"));
		pHeader->SetTitleText(L"Graffiti Map");
		pFooter->SetItemColor(FOOTER_ITEM_STATUS_DISABLED, Tizen::Graphics::Color(0x00, 128, 255));
		pFooter->SetItemEnabled(0,true);
		pFooter->SetItemEnabled(1,false);
		pFooter->SetItemEnabled(2,true);
		pFooter->SetItemEnabled(3,true);
		pFooter->SetItemEnabled(4,true);
		break;
	case ID_FOOTER_ITEM3:
		pSceneManager->GoForward(SceneTransitionId(L"ID_SCNT_3"));
		pHeader->SetTitleText(L"Post Graffiti");
		pFooter->SetItemColor(FOOTER_ITEM_STATUS_DISABLED, Tizen::Graphics::Color(0x00, 128, 255));
		pFooter->SetItemEnabled(0,true);
		pFooter->SetItemEnabled(1,true);
		pFooter->SetItemEnabled(2,false);
		pFooter->SetItemEnabled(3,true);
		pFooter->SetItemEnabled(4,true);
		break;
	case ID_FOOTER_ITEM4:
		pSceneManager->GoForward(SceneTransitionId(L"ID_SCNT_4"));
		pHeader->SetTitleText(L"Profile");
		pFooter->SetItemColor(FOOTER_ITEM_STATUS_DISABLED, Tizen::Graphics::Color(0x00, 128, 255));
		pFooter->SetItemEnabled(0,true);
		pFooter->SetItemEnabled(1,true);
		pFooter->SetItemEnabled(2,true);
		pFooter->SetItemEnabled(3,false);
		pFooter->SetItemEnabled(4,true);
		break;
	case ID_FOOTER_ITEM5:
		pSceneManager->GoForward(SceneTransitionId(L"ID_SCNT_5"));
		pHeader->SetTitleText(L"Settings");
		pFooter->SetItemColor(FOOTER_ITEM_STATUS_DISABLED, Tizen::Graphics::Color(0x00, 128, 255));
		pFooter->SetItemEnabled(0,true);
		pFooter->SetItemEnabled(1,true);
		pFooter->SetItemEnabled(2,true);
		pFooter->SetItemEnabled(3,true);
		pFooter->SetItemEnabled(4,false);
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
