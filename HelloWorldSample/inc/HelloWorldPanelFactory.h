#ifndef _HELLOWORLD_PANEL_FACTORY_H_
#define _HELLOWORLD_PANEL_FACTORY_H_

#include <FUi.h>


class HelloWorldPanelFactory
	: public Tizen::Ui::Scenes::IPanelFactory
{
public:
	HelloWorldPanelFactory(void);
	virtual ~HelloWorldPanelFactory(void);

	virtual Tizen::Ui::Controls::Panel* CreatePanelN(const Tizen::Base::String& panelId, const Tizen::Ui::Scenes::SceneId& sceneId);
};

#endif // _HELLOWORLD_PANEL_FACTORY_H_
