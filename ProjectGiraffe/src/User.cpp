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

User *currentUserSingleton = NULL;

User *User::currentUser()
{
	if (!currentUserSingleton) {
		currentUserSingleton = new User();
	}
	return currentUserSingleton;
}

User::User() :
	_id(0),
	_fullname(L""),
	_username(L""),
	_email(L""),
	_dateCreated(NULL),
	_listeners(NULL) {}

User::~User() {
	delete _dateCreated;
	delete _listeners;
}

result User::updateFromDictionary(HashMap *dictionary)
{
	result success = E_FAILURE;
	if (dictionary && !dictionary->ContainsKey(kHTTPParamNameError)) {
		Double *idValue = static_cast<Double *>(dictionary->GetValue(kHTTPParamNameUserID));
		if (idValue) {
			_id = idValue->ToInt();
			success = E_SUCCESS;
		}

		String *fullnameValue = static_cast<String *>(dictionary->GetValue(kHTTPParamNameFullname));
		if (fullnameValue) {
			_fullname = *fullnameValue;
			success = E_SUCCESS;
		}

		String *usernameValue = static_cast<String *>(dictionary->GetValue(kHTTPParamNameUsername));
		if (usernameValue) {
			_username = *usernameValue;
			success = E_SUCCESS;
		}

		String *emailValue = static_cast<String *>(dictionary->GetValue(kHTTPParamNameEmail));
		if (emailValue) {
			_email = *emailValue;
			success = E_SUCCESS;
		}

		HashMap *dateDictionary = static_cast<HashMap *>(dictionary->GetValue(kHTTPParamNameDateCreated));
		if (dateDictionary) {
			_dateCreated = new Date();
			result dateSuccess = _dateCreated->updateFromDictionary(dateDictionary);
			if (IsFailed(dateSuccess)) {
				delete _dateCreated;
				_dateCreated = NULL;
			} else {
				success = E_SUCCESS;
			}
		}

		if (!IsFailed(success)) {
			AppLogTag("user", "ab");
			if (_listeners) {
				AppLogTag("user", "cd");
				IEnumerator *iter = _listeners->GetEnumeratorN();
				while (iter->MoveNext() == E_SUCCESS) {
					UserListener *listener = static_cast<UserListener *>(iter->GetCurrent());
					listener->onUserUpdate(this);
				}
				delete iter;
			}
		}
	}

	return success;
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

void User::addListener(UserListener *listener)
{
	if (listener) {
		if (!_listeners) {
			_listeners = new ArrayList(SingleObjectDeleter);
			_listeners->Construct();
		}
		_listeners->Add(listener);
	}
}

void User::removeListener(UserListener *listener)
{
	if (listener && _listeners) {
		_listeners->Remove(*listener);
	}
}
