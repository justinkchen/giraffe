#include "ProjectGiraffePanelFactory.h"
#include "ProjectGiraffeTab1.h"
#include "ProjectGiraffeTab2.h"
#include "ProjectGiraffeTab3.h"
#include "ProjectGiraffeTab5.h"
#include "ProjectGiraffeTab4.h"

using namespace Tizen::Ui::Scenes;


ProjectGiraffePanelFactory::ProjectGiraffePanelFactory(void)
{
}

ProjectGiraffePanelFactory::~ProjectGiraffePanelFactory(void)
{
}

Tizen::Ui::Controls::Panel*
ProjectGiraffePanelFactory::CreatePanelN(const Tizen::Base::String& panelId, const Tizen::Ui::Scenes::SceneId& sceneId)
{

	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);
	Tizen::Ui::Controls::Panel* pNewPanel = null;

	if (panelId == L"IDC_PANEL1")
	{
		ProjectGiraffeTab1* pPanel = new ProjectGiraffeTab1();
		pPanel->Initialize();
		pSceneManager->AddSceneEventListener(sceneId, *pPanel);
		pNewPanel = pPanel;
	}
	else
	if (panelId == L"IDC_PANEL2")
	{
		ProjectGiraffeTab2* pPanel = new ProjectGiraffeTab2();
		pPanel->Initialize();
		pSceneManager->AddSceneEventListener(sceneId, *pPanel);
		pNewPanel = pPanel;
	}
	else
	if (panelId == L"IDC_PANEL3")
	{
		ProjectGiraffeTab3* pPanel = new ProjectGiraffeTab3();
		pPanel->Initialize();
		pSceneManager->AddSceneEventListener(sceneId, *pPanel);
		pNewPanel = pPanel;
	}
	else if (panelId == L"IDC_PANEL4")
	{
		ProjectGiraffeTab4* pPanel = new ProjectGiraffeTab4();
		pPanel->Initialize();
		pNewPanel = pPanel;
	}
	else if (panelId == L"IDC_PANEL5")
	{
		ProjectGiraffeTab5* pPanel = new ProjectGiraffeTab5();
		pPanel->Initialize();
		pNewPanel = pPanel;
	}


	// TODO:
	// Add your panel creation code here
	return pNewPanel;
}

