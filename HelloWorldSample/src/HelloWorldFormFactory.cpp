#include "HelloWorldFormFactory.h"
#include "HelloWorldMainForm.h"

using namespace Tizen::Ui::Scenes;


HelloWorldFormFactory::HelloWorldFormFactory(void)
{
}

HelloWorldFormFactory::~HelloWorldFormFactory(void)
{
}

Tizen::Ui::Controls::Form*
HelloWorldFormFactory::CreateFormN(const Tizen::Base::String& formId, const Tizen::Ui::Scenes::SceneId& sceneId)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);
	Tizen::Ui::Controls::Form* pNewForm = null;

	if (formId == L"IDF_FORM")
	{
		HelloWorldMainForm* pForm = new HelloWorldMainForm();
		pForm->Initialize();
		pSceneManager->AddSceneEventListener(sceneId, *pForm);
		pNewForm = pForm;
	}
	// TODO:
	// Add your form creation code here

	return pNewForm;
}
