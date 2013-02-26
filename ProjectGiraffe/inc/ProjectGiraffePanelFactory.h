#ifndef _PROJECTGIRAFFE_PANEL_FACTORY_H_
#define _PROJECTGIRAFFE_PANEL_FACTORY_H_

#include <FUi.h>


class ProjectGiraffePanelFactory
	: public Tizen::Ui::Scenes::IPanelFactory
{
public:
	ProjectGiraffePanelFactory(void);
	virtual ~ProjectGiraffePanelFactory(void);

	virtual Tizen::Ui::Controls::Panel* CreatePanelN(const Tizen::Base::String& panelId, const Tizen::Ui::Scenes::SceneId& sceneId);
};

#endif // _PROJECTGIRAFFE_PANEL_FACTORY_H_
