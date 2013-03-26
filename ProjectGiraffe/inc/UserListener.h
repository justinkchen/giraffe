/*
 * UserListener.h
 *
 *  Created on: Mar 22, 2013
 *      Author: bryancheng
 */

#ifndef USERLISTENER_H_
#define USERLISTENER_H_

#include <FBase.h>
class User;

class UserListener :
	public Tizen::Base::Object
{
public :
	virtual void onUserUpdate(User *user) = 0;
};

#endif /* USERLISTENER_H_ */
