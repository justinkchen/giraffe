/*
 * Graffiti.cpp
 *
 *  Created on: Mar 10, 2013
 *      Author: kkhorimoto
 */

#include "Graffiti.h"
#include "Date.h"
#include "User.h"
#include "HttpConnection.h" // TODO: maybe find a better place for the parameter names to live.

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;

Graffiti::Graffiti() :
	_text(L""),
	_imageURL(L""),
	_longitude(0),
	_latitude(0),
	_directionX(0),
	_directionZ(0),
	_radius(0),
	_likeCount(0),
	_flagged(false),
	_dateCreated(NULL),
	_user(NULL),
	_listeners(NULL) {}

Graffiti::~Graffiti() {
	delete _dateCreated;
	delete _user;
	delete _listeners;
}

result Graffiti::updateFromDictionary(HashMap *dictionary)
{
	AppLog("In updateFromDictionary");
	result success = E_FAILURE;
	if (dictionary && !dictionary->ContainsKey(kHTTPParamNameError)) {
		AppLog("updating from dictionary");
		Double *dblValue = static_cast<Double *>(dictionary->GetValue(kHTTPParamNameLongitude));
		if (dblValue) {
			_longitude = dblValue->ToDouble();
			success = E_SUCCESS;
		}

		dblValue = static_cast<Double *>(dictionary->GetValue(kHTTPParamNameLatitude));
		if (dblValue) {
			_latitude = dblValue->ToDouble();
			success = E_SUCCESS;
		}

		dblValue = static_cast<Double *>(dictionary->GetValue(kHTTPParamNameDirectionX));
		if (dblValue) {
			_directionX = dblValue->ToDouble();
			success = E_SUCCESS;
		}

		dblValue = static_cast<Double *>(dictionary->GetValue(kHTTPParamNameDirectionY));
		if (dblValue) {
			_directionY = dblValue->ToDouble();
			success = E_SUCCESS;
		}

		dblValue = static_cast<Double *>(dictionary->GetValue(kHTTPParamNameDirectionZ));
		if (dblValue) {
			_directionZ = dblValue->ToDouble();
			success = E_SUCCESS;
		}

		dblValue = static_cast<Double *>(dictionary->GetValue(kHTTPParamNameRadius));
		if (dblValue) {
			_radius = dblValue->ToDouble();
			success = E_SUCCESS;
		}

		String *textValue = static_cast<String *>(dictionary->GetValue(kHTTPParamNameText));
		if (textValue) {
			_text = *textValue;
			success = E_SUCCESS;
		}

		String *imageURLValue = static_cast<String *>(dictionary->GetValue(kHTTPParamNameImageURL));
		if (imageURLValue) {
			_imageURL = *imageURLValue;
			success = E_SUCCESS;
		}

		HashMap *dateDictionary = static_cast<HashMap *>(dictionary->GetValue(kHTTPParamNameDateCreated));
		if (dateDictionary) {
			// TODO: Handle dates
//			_dateCreated = new Date();
//			result dateSuccess = _dateCreated->updateFromDictionary(dateDictionary);
//			if (IsFailed(dateSuccess)) {
//				delete _dateCreated;
//				_dateCreated = NULL;
//			} else {
//				success = E_SUCCESS;
//			}
		}

		String *usernameValue = static_cast<String *>(dictionary->GetValue(kHTTPParamNameUsername));
		if (usernameValue) {
			_user = new User();
			_user->setUsername(usernameValue->GetPointer());
			success = E_SUCCESS;
		}

		HashMap *userDictionary = static_cast<HashMap *>(dictionary->GetValue(kHTTPParamNameUser));
		if (userDictionary) {
			// TODO: Handle users using a dictionary instead of just a username
			_user = new User();
			result userSuccess = _user->updateFromDictionary(userDictionary);
			if (IsFailed(userSuccess)) {
				delete _user;
				_user = NULL;
			} else {
				success = E_SUCCESS;
			}
		}
	}
	AppLog("Finished updating from dictionary");
	return success;
}

HashMap *Graffiti::parameterDictionary()
{
	HashMap *parameters = new HashMap(SingleObjectDeleter);
	parameters->Construct();
	parameters->Add(new String(kHTTPParamNameText), new String(_text));
	parameters->Add(new String(kHTTPParamNameImageURL), new String(_imageURL));
	parameters->Add(new String(kHTTPParamNameLongitude), new Double(_longitude));
	parameters->Add(new String(kHTTPParamNameLatitude), new Double(_latitude));
	parameters->Add(new String(kHTTPParamNameDirectionX), new Double(_directionX));
	parameters->Add(new String(kHTTPParamNameDirectionY), new Double(_directionY));
	parameters->Add(new String(kHTTPParamNameDirectionZ), new Double(_directionZ));
	parameters->Add(new String(kHTTPParamNameRadius), new Double(_radius));
	parameters->Add(new String(kHTTPParamNameLikeCount), new Integer(_likeCount));
	parameters->Add(new String(kHTTPParamNameFlagged), new Boolean(_flagged));
	parameters->Add(new String(kHTTPParamNameDateCreated), _dateCreated->parameterDictionary());
	parameters->Add(new String(kHTTPParamNameUserID), new Double(_user->id()));
	return parameters;
}

void Graffiti::addListener(GraffitiListener *listener)
{
	if (listener) {
		if (!_listeners) {
			_listeners = new (std::nothrow) ArrayList();
		}

		if (!_listeners->Contains(*listener)) {
			_listeners->Add(listener);
		}
	}
}

void Graffiti::removeListener(GraffitiListener *listener)
{
	AppLog("removing listener");
	AppLogIf(_listeners, "_listeners is non-null");
	if (_listeners) {
		AppLog("trying to remove");
		_listeners->Remove(*listener);
	}
	AppLog("removed listener");
}

void Graffiti::setLikeCount(int likeCount)
{
	if (_likeCount != likeCount) {
		_likeCount = likeCount;

		if (_listeners) {
	        IEnumerator *enumerator = _listeners->GetEnumeratorN();
	        Object* obj = null;
	        while (enumerator->MoveNext() == E_SUCCESS) {
	        	GraffitiListener *listener = dynamic_cast<GraffitiListener *>(obj);
	        	listener->onLikeCount();
	        }
	        delete enumerator;
		}
	}
}

void Graffiti::setFlagged(bool flagged)
{
	if (_flagged != flagged) {
		_flagged = flagged;

		if (_listeners) {
	        IEnumerator *enumerator = _listeners->GetEnumeratorN();
	        Object* obj = null;
	        while (enumerator->MoveNext() == E_SUCCESS) {
	        	GraffitiListener *listener = dynamic_cast<GraffitiListener *>(obj);
	        	listener->onFlagged();
	        }
	        delete enumerator;
		}
	}
}
