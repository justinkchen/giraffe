/*
 * Graffiti.cpp
 *
 *  Created on: Mar 10, 2013
 *      Author: kkhorimoto
 */

#include "Graffiti.h"
#include "Date.h"
#include "User.h"
#include "HTTPConnection.h" // TODO: maybe find a better place for the parameter names to live.

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;

Graffiti::Graffiti() :
	_text(L""),
	_imageURL(L""),
	_longitude(0),
	_latitude(0),
	_directionX(0),
	_directionZ(0),
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
