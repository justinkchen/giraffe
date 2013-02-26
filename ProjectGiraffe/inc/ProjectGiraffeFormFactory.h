#ifndef _PROJECTGIRAFFE_FORM_FACTORY_H_
#define _PROJECTGIRAFFE_FORM_FACTORY_H_

#include <FUi.h>


class ProjectGiraffeFormFactory
	: public Tizen::Ui::Scenes::IFormFactory
{
public:
	ProjectGiraffeFormFactory(void);
	virtual ~ProjectGiraffeFormFactory(void);

	virtual Tizen::Ui::Controls::Form* CreateFormN(const Tizen::Base::String& formId, const Tizen::Ui::Scenes::SceneId& sceneId);
};

#endif // _PROJECTGIRAFFE_FORM_FACTORY_H_
