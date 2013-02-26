#include "ProjectGiraffeFormFactory.h"
#include "ProjectGiraffeMainForm.h"

using namespace Tizen::Ui::Scenes;


ProjectGiraffeFormFactory::ProjectGiraffeFormFactory(void)
{
}

ProjectGiraffeFormFactory::~ProjectGiraffeFormFactory(void)
{
}

Tizen::Ui::Controls::Form*
ProjectGiraffeFormFactory::CreateFormN(const Tizen::Base::String& formId, const Tizen::Ui::Scenes::SceneId& sceneId)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);
	Tizen::Ui::Controls::Form* pNewForm = null;

	if (formId == L"IDF_FORM")
	{
		ProjectGiraffeMainForm* pForm = new ProjectGiraffeMainForm();
		pForm->Initialize();
		pNewForm = pForm;
	}
	// TODO:
	// Add your form creation code here

	return pNewForm;
}
