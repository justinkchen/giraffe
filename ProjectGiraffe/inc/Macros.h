/*
 * Macros.h
 *
 *  Created on: Mar 12, 2013
 *      Author: kkhorimoto
 */

#ifndef MACROS_H_
#define MACROS_H_

#include <FUi.h>

// The Construct macros can be passed into a Tizen Construct() method
// that requires nonzero dimensions.  They can be used when the objects
// will be resized before being drawn
#define kRectConstruct (Rectangle(0, 0, 1, 1))
#define kDimConstruct (Dimension(1,1))

#define kTextColor (Color::GetColor(COLOR_ID_BLACK))

#endif /* MACROS_H_ */
