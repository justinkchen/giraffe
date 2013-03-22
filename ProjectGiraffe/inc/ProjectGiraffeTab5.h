#ifndef _PROJECTGIRAFFE_TAB5_H_
#define _PROJECTGIRAFFE_TAB5_H_

#include <FBase.h>
#include <FUi.h>

class ProjectGiraffeTab5
	: public Tizen::Ui::Controls::Panel
	, public Tizen::Ui::Scenes::ISceneEventListener
{
public:
	ProjectGiraffeTab5(void);
	virtual ~ProjectGiraffeTab5(void);
	bool Initialize(void);

	virtual result OnInitializing(void);
	virtual result OnTerminating(void);

	// ISceneEventListener
	virtual void OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								   const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs);
	virtual void OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
									const Tizen::Ui::Scenes::SceneId& nextSceneId);

};

#endif // _PROJECTGIRAFFE_TAB5_H_
