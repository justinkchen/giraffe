/*
 * HTTPConnection.cpp
 *
 *  Created on: Mar 17, 2013
 *      Author: Elliott
 */


#include "HTTPConnection.h"
#include "Graffiti.h"
#include "User.h"
#include "JSONParser.h"
#include <FWeb.h>
#include <cstdlib>

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Net::Http;
using namespace Tizen::Web::Json;

const String kHTTPHostURL = L"http://ec2-54-243-69-6.compute-1.amazonaws.com/";
const String kHTTPMethodNameNearbyGraffiti = L"nearby";
const String kHTTPMethodNameNewGraffiti = L"addgraffiti";
const String kHTTPMethodNameUserLogin = L"login";
const String kHTTPMethodNameUserSignup = L"signup";

const String kHTTPParamNameGraffiti = L"graffiti";
const String kHTTPParamNameText = L"text";
const String kHTTPParamNameImageURL = L"imageURL";
const String kHTTPParamNameLongitude = L"longitude";
const String kHTTPParamNameLatitude = L"latitude";
const String kHTTPParamNameDirectionX = L"directionX";
const String kHTTPParamNameDirectionY = L"directionY";
const String kHTTPParamNameDirectionZ = L"directionZ";
const String kHTTPParamNameLikeCount = L"likeCount";
const String kHTTPParamNameFlagged = L"flagged";
const String kHTTPParamNameDateCreated = L"dateCreated";
const String kHTTPParamNameUser = L"user";
const String kHTTPParamNameUserID = L"id";
const String kHTTPParamNameFullname = L"fullname";
const String kHTTPParamNameUsername = L"username";
const String kHTTPParamNameEmail = L"email";
const String kHTTPParamNameYear = L"year";
const String kHTTPParamNameMonth = L"month";
const String kHTTPParamNameDay = L"day";
const String kHTTPParamNameHour = L"hour";
const String kHTTPParamNameMinute = L"minute";
const String kHTTPParamNameSecond = L"second";


HTTPConnection::HTTPConnection(HTTPConnectionListener *listener, const Tizen::Base::String methodName, Tizen::Net::Http::NetHttpMethod methodType, Tizen::Net::Http::HttpMultipartEntity *parameters) :
		_methodName(methodName),
		_listener(listener),
		_responseDictionary(NULL)
{
	// Create session
	_session = new HttpSession();
	_session->Construct(NET_HTTP_SESSION_MODE_NORMAL, NULL, kHTTPHostURL, NULL, NET_HTTP_COOKIE_FLAG_ALWAYS_AUTOMATIC);

	_transaction = _session->OpenTransactionN();
	_transaction->AddHttpTransactionListener(*this);

	HttpRequest *request = _transaction->GetRequest();
	request->SetMethod(methodType);
	String uri = kHTTPHostURL;
	uri.Append(methodName);
	request->SetUri(uri);
	if (parameters) {
		request->SetEntity(*parameters);
	}
}

HTTPConnection::~HTTPConnection()
{
	delete _session;
	delete _transaction;
	delete _responseDictionary;
}

// Factory methods
HTTPConnection *HTTPConnection::nearbyGraffitiGetConnection(HTTPConnectionListener *listener, double latitude, double longitude)
{
	HttpMultipartEntity *parameters = new HttpMultipartEntity();
	parameters->Construct();
	parameters->AddStringPart(L"latitude", Double(latitude).ToString());
	parameters->AddStringPart(L"longitude", Double(longitude).ToString());

	HTTPConnection *connection = new HTTPConnection(listener, kHTTPMethodNameNearbyGraffiti, NET_HTTP_METHOD_GET, parameters);
	delete parameters;

	return connection;
}

HTTPConnection *HTTPConnection::newGraffitiPostConnection(HTTPConnectionListener *listener, Graffiti *graffiti)
{
	HTTPConnection *connection = NULL;

	HttpMultipartEntity *parameters = parametersForGraffiti(graffiti);
	if (parameters) {
		connection = new HTTPConnection(listener, kHTTPMethodNameNewGraffiti, NET_HTTP_METHOD_POST, parameters);
		delete parameters;
	}

	return connection;
}

HTTPConnection *HTTPConnection::userLoginPostConnection(HTTPConnectionListener *listener, User *user, String password)
{
	HTTPConnection *connection = NULL;

	HttpMultipartEntity *parameters = parametersForUser(user);
	if (parameters) {
		parameters->AddStringPart(L"password", password);
		connection = new HTTPConnection(listener, kHTTPMethodNameUserLogin, NET_HTTP_METHOD_POST, parameters);
		delete parameters;
	}

	return connection;
}

HTTPConnection *HTTPConnection::userSignupPostConnection(HTTPConnectionListener *listener, User *user, Tizen::Base::String password)
{
	HTTPConnection *connection = NULL;

	HttpMultipartEntity *parameters = parametersForUser(user);
	if (parameters) {
		parameters->AddStringPart(L"password", password);
		connection = new HTTPConnection(listener, kHTTPMethodNameUserSignup, NET_HTTP_METHOD_POST, parameters);
		delete parameters;
	}

	return connection;
}

// Instance Methods
void HTTPConnection::begin()
{
	_transaction->Submit();
}


// Utility methods
HttpMultipartEntity *HTTPConnection::parametersForDictionary(Tizen::Base::Collection::HashMap *dictionary)
{
	HttpMultipartEntity *parameters = NULL;
	if (dictionary) {
		parameters = new HttpMultipartEntity();
		parameters->Construct();

		IMapEnumerator *iter = dictionary->GetMapEnumeratorN();
		String *key = NULL, value = L"";
		while (iter->MoveNext() == E_SUCCESS) {
			key = static_cast<String *>(iter->GetKey());

			// The value will either be a String, Double, or Boolean
			Object *objValue = iter->GetValue();
			String *strValue = dynamic_cast<String *>(objValue);
			if (strValue) {
				value = *strValue;
			}

			Double *doubleValue = dynamic_cast<Double *>(objValue);
			if (doubleValue) {
				value = doubleValue->ToString();
			}

			Boolean *boolValue = dynamic_cast<Boolean *>(objValue);
			if (boolValue) {
				value = boolValue->ToString();
			}

			if (key && value.GetLength()) {
				parameters->AddStringPart(*key, value);
			}
		}
	}
	return parameters;
}

HttpMultipartEntity *HTTPConnection::parametersForGraffiti(Graffiti *graffiti)
{
	HashMap *dictionary = (graffiti ? graffiti->parameterDictionary() : NULL);
	return parametersForDictionary(dictionary);
}

HttpMultipartEntity *HTTPConnection::parametersForUser(User *user)
{
	HashMap *dictionary = (user ? user->parameterDictionary() : NULL);
	return parametersForDictionary(dictionary);
}

// IHttpTransactionEventListener
void
HTTPConnection::OnTransactionAborted (HttpSession &httpSession, HttpTransaction &httpTransaction, result r)
{
	_listener->connectionDidFail(this);
}

void
HTTPConnection::OnTransactionCertVerificationRequiredN (HttpSession &httpSession, HttpTransaction &httpTransaction, Tizen::Base::String *pCert)
{
	// TODO: figure out what we need to do for certification here.
	_listener->connectionDidFail(this);
}

void
HTTPConnection::OnTransactionCompleted (HttpSession &httpSession, HttpTransaction &httpTransaction)
{
	if (_responseDictionary) {
		_listener->connectionDidFinish(this, _responseDictionary);
	} else {
		_listener->connectionDidFail(this);
	}
}

void
HTTPConnection::OnTransactionReadyToRead (HttpSession &httpSession, HttpTransaction &httpTransaction, int availableBodyLen)
{
	HttpResponse *response = httpTransaction.GetResponse();
	if (response->GetHttpStatusCode() == HTTP_STATUS_OK) {
		ByteBuffer *body = response->ReadBodyN();
		IJsonValue *jsonValue = JsonParser::ParseN(*body);
		_responseDictionary = JSONParser::dictionaryForJSONValue(jsonValue);

		delete body;
		delete jsonValue;
	}
}
