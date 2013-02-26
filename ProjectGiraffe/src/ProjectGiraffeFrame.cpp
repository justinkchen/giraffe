#include "ProjectGiraffeFrame.h"
#include "ProjectGiraffeFormFactory.h"
#include "ProjectGiraffePanelFactory.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;

ProjectGiraffeFrame::ProjectGiraffeFrame(void)
{
}

ProjectGiraffeFrame::~ProjectGiraffeFrame(void)
{
}

result
ProjectGiraffeFrame::OnInitializing(void)
{
	// Prepare Scene management.
	SceneManager* pSceneManager = SceneManager::GetInstance();
	static ProjectGiraffeFormFactory formFactory;
	static ProjectGiraffePanelFactory panelFactory;
	pSceneManager->RegisterFormFactory(formFactory);
	pSceneManager->RegisterPanelFactory(panelFactory);
	pSceneManager->RegisterScene(L"workflow");

	// Goto the scene.
	result r = pSceneManager->GoForward(SceneTransitionId(L"ID_SCNT_START"));

	// TODO: Add your initialization code here
	return r;
}

result
ProjectGiraffeFrame::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO:
	// Add your termination code here
	return r;
}
