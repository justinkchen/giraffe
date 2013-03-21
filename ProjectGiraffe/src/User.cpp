/*
 * User.cpp
 *
 *  Created on: Mar 10, 2013
 *      Author: kkhorimoto
 */

#include "User.h"
#include "Date.h"
#include "HTTPConnection.h" // TODO: maybe find a better place for the parameter names to live.

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;

User::User() :
	_id(0),
	_fullname(L""),
	_username(L""),
	_email(L""),
	_dateCreated(NULL) {}
User::~User() {
	delete _dateCreated;
}
HashMap *User::parameterDictionary()
{
	HashMap *parameters = new HashMap(SingleObjectDeleter);
	parameters->Construct();
	parameters->Add(new String(kHTTPParamNameUserID), new Double(_id));
	parameters->Add(new String(kHTTPParamNameFullname), new String(_fullname));
	parameters->Add(new String(kHTTPParamNameUsername), new String(_username));
	parameters->Add(new String(kHTTPParamNameEmail), new String(_email));
	if (_dateCreated) {
		parameters->Add(new String(kHTTPParamNameDateCreated), _dateCreated->parameterDictionary());
	}
	return parameters;
}
