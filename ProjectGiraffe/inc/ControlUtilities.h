/*
 * ControlUtilities.h
 *
 *  Created on: Mar 12, 2013
 *      Author: kkhorimoto
 */

#ifndef CONTROLUTILITIES_H_
#define CONTROLUTILITIES_H_

#include <FUi.h>

namespace ControlUtil
{

void setBoundsX(Tizen::Ui::Control *control, int x);
void setBoundsY(Tizen::Ui::Control *control, int y);
void setBoundsWidth(Tizen::Ui::Control *control, int width);
void setBoundsHeight(Tizen::Ui::Control *control, int height);
void centerVertically(Tizen::Ui::Control *controlToCenter, Tizen::Ui::Control *referenceControl);
void centerHorizontally(Tizen::Ui::Control *controlToCenter, Tizen::Ui::Control *referenceControl);
int rightEdge(Tizen::Ui::Control *control);
int bottomEdge(Tizen::Ui::Control *control);

} // End of ControlUtil namespace

#endif /* CONTROLUTILITIES_H_ */
