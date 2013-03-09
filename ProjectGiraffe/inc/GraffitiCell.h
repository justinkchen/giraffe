/*
 * GraffitiCell.h
 *
 *  Created on: Mar 3, 2013
 *      Author: kkhorimoto
 */

#ifndef GRAFFITICELL_H_
#define GRAFFITICELL_H_

#include <FBase.h>
#include <FUi.h>

class GraffitiCell
    : public Tizen::Ui::Controls::Panel
    , public Tizen::Ui::Scenes::ISceneEventListener
{
    public:
        GraffitiCell();
        virtual ~GraffitiCell();
        bool Initialize();

	    virtual result OnInitializing(void);
	    virtual result OnTerminating(void);
	    virtual void OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								       const Tizen::Ui::Scenes::SceneId& currentSceneId, 
                                       Tizen::Base::Collection::IList* pArgs);
	    virtual void OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
									    const Tizen::Ui::Scenes::SceneId& nextSceneId);

        Tizen::Base::String username() { return _username; }
        void setUsername(Tizen::Base::String username);
        Tizen::Base::String text() { return _text; }
        void setText(Tizen::Base::String text);
        float distance() { return _distance; }
        void setDistance(float distance);

    private:
        Tizen::Base::String _username;
        Tizen::Base::String _text;
        float _distance; // in feet.

        int nameLabelFontSize();
        int distanceLabelFontSize();
        int textLabelFontSize();
        Tizen::Ui::Controls::Label *_nameLabel;
        Tizen::Ui::Controls::Label *_distanceLabel;
        Tizen::Ui::Controls::Label *_textLabel;
};


#endif /* GRAFFITICELL_H_ */
