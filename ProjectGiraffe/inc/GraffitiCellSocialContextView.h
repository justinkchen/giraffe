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
    public Tizen::Ui::IActionEventListener
{
public:
   	GraffitiCellSocialContextView();
	virtual ~GraffitiCellSocialContextView();

	virtual result OnDraw();
    virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

	Graffiti *graffiti() { return _graffiti; }
	void setGraffiti(Graffiti *graffiti) { _graffiti = graffiti; }
private:
	Tizen::Base::String likeButtonText();
	Tizen::Ui::Controls::Button *_likeButton;
	Graffiti *_graffiti;
};

#endif /* GRAFFITICELLSOCIALCONTEXTITEM_H_ */
