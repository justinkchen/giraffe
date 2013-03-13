/*
 * GraffitiCellSocialContextItem.h
 *
 *  Created on: Mar 13, 2013
 *      Author: kkhorimoto
 */

#ifndef GRAFFITICELLSOCIALCONTEXTITEM_H_
#define GRAFFITICELLSOCIALCONTEXTITEM_H_

#include <FUi.h>
#include <FBase.h>
#include "Graffiti.h"

class GraffitiCellSocialContextView :
    public Tizen::Ui::Controls::Panel ,
    public Tizen::Ui::IActionEventListener,
    public Graffiti::GraffitiListener
{
public:
   	GraffitiCellSocialContextView();
	virtual ~GraffitiCellSocialContextView();

	// Panel overrides
	virtual result OnDraw();

	// IActionEventListener overrides
    virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

    // GraffitiListener overrides
	virtual void onLikeCount();
	virtual void onFlagged();

	Graffiti *graffiti() { return _graffiti; }
	void setGraffiti(Graffiti *graffiti);
private:
	Tizen::Base::String likeButtonText();
	Tizen::Base::String flagButtonText();
	Tizen::Ui::Controls::Button *_likeButton;
	Tizen::Ui::Controls::Button *_flagButton;
	Graffiti *_graffiti;

	const Tizen::Base::String kLikeButtonText;
	const Tizen::Base::String kUnlikeButtonText;
	const Tizen::Base::String kFlagButtonText;
	const Tizen::Base::String kUnflagButtonText;
};

#endif /* GRAFFITICELLSOCIALCONTEXTITEM_H_ */
