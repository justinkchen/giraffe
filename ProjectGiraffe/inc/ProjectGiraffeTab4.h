#ifndef _PROJECTGIRAFFE_TAB4_H_
#define _PROJECTGIRAFFE_TAB4_H_

#include <FBase.h>
#include <FUi.h>

class ProjectGiraffeTab4
	: public Tizen::Ui::Controls::Panel
	, public Tizen::Ui::Scenes::ISceneEventListener
{
public:
	ProjectGiraffeTab4(void);
	virtual ~ProjectGiraffeTab4(void);
	bool Initialize(void);

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								   const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs);
	virtual void OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
									const Tizen::Ui::Scenes::SceneId& nextSceneId);

};

#endif // _PROJECTGIRAFFE_TAB4_H_
