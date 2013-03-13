/*
 * Graffiti.cpp
 *
 *  Created on: Mar 10, 2013
 *      Author: kkhorimoto
 */

#include "Graffiti.h"

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
	_dateCreated(),
	_user(null),
	_listeners(null)
{
	// TODO Auto-generated constructor stub
}

Graffiti::~Graffiti() {
	// TODO Auto-generated destructor stub
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
