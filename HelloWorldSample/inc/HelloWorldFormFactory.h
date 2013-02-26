#ifndef _HELLOWORLD_FORM_FACTORY_H_
#define _HELLOWORLD_FORM_FACTORY_H_

#include <FUi.h>


class HelloWorldFormFactory
	: public Tizen::Ui::Scenes::IFormFactory
{
public:
	HelloWorldFormFactory(void);
	virtual ~HelloWorldFormFactory(void);

	virtual Tizen::Ui::Controls::Form* CreateFormN(const Tizen::Base::String& formId, const Tizen::Ui::Scenes::SceneId& sceneId);
};

#endif // _HELLOWORLD_FORM_FACTORY_H_
