/*
 * HttpConnection.cpp
 *
 *  Created on: Mar 17, 2013
 *      Author: Elliott
 */

#include "HttpConnection.h"
#include "Graffiti.h"
#include "User.h"
#include "JSONParser.h"
#include <FWeb.h>
#include <cstdlib>

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Net::Http;
using namespace Tizen::Web::Json;

const String kHTTPHostURL = L"https://ec2-54-243-69-6.compute-1.amazonaws.com/";
const String kServerCert =
		L"/C=US/ST=California/L=Palo Alto/O=Unsamsung Heroes/CN=giraffe-server/emailAddress=bbch@stanford.edu";

const String kHTTPMethodNameGraffitiNearby = L"graffiti/nearby";
const String kHTTPMethodNameGraffitiNew = L"graffiti/new";
const String kHTTPMethodNameGraffitiLike = L"graffiti/like";
const String kHTTPMethodNameGraffitiFlag = L"graffiti/flag";
const String kHTTPMethodNameUserLogin = L"users/login";
const String kHTTPMethodNameUserSignup = L"users/signup";
const String kHTTPMethodNameUserUpdate = L"users/update";
const String kHTTPMethodNameUserPosts = L"users/graffiti";
const String kHTTPMethodNameUserStats = L"users/stats";
const String kHTTPMethodNameUserLogout = L"users/logout";

const String kHTTPParamNameGraffiti = L"graffiti";
const String kHTTPParamNameGraffitoId = L"id";
const String kHTTPParamNameText = L"message";
const String kHTTPParamNameImageURL = L"imageUrl";
const String kHTTPParamNameLongitude = L"longitude";
const String kHTTPParamNameLatitude = L"latitude";
const String kHTTPParamNameDirectionX = L"directionX";
const String kHTTPParamNameDirectionY = L"directionY";
const String kHTTPParamNameDirectionZ = L"directionZ";
const String kHTTPParamNameDateCreated = L"dateCreated";
const String kHTTPParamNameLikeCount = L"likeCount";
const String kHTTPParamNameFlagged = L"flagged";
const String kHTTPParamNameUser = L"user";
const String kHTTPParamNameUserID = L"id";
const String kHTTPParamNameRadius = L"radius";
const String kHTTPParamNameUsername = L"username";
const String kHTTPParamNameEmail = L"email";
const String kHTTPParamNameAvatarUrl = L"avatar";
const String kHTTPParamNameYear = L"year";
const String kHTTPParamNameMonth = L"month";
const String kHTTPParamNameDay = L"day";
const String kHTTPParamNameHour = L"hour";
const String kHTTPParamNameMinute = L"minute";
const String kHTTPParamNameSecond = L"second";
const String kHTTPParamNameError = L"error";

const String cookiesKey = "HttpConnectionCookie";
static String _cookies = "";

HttpConnection::HttpConnection(HttpConnectionListener *listener,
		const Tizen::Base::String methodName,
		Tizen::Net::Http::NetHttpMethod methodType,
		Tizen::Net::Http::HttpMultipartEntity *parameters) :
		_methodName(methodName), _listener(listener), _responseDictionary(NULL)
{
	// Create session
	_session = new HttpSession();
	_session->Construct(NET_HTTP_SESSION_MODE_NORMAL, NULL, kHTTPHostURL, NULL,
			NET_HTTP_COOKIE_FLAG_ALWAYS_MANUAL);

	_transaction = _session->OpenTransactionN();
	_transaction->AddHttpTransactionListener(*this);

	HttpRequest *request = _transaction->GetRequest();
	request->SetMethod(methodType);
	String uri = kHTTPHostURL;
	uri.Append(methodName);
	request->SetUri(uri);
	if (parameters) {
		AppLogTag("user", "added");
		request->SetEntity(*parameters);
	}

	if (!_cookies.Equals("", false)) {
		String cookieString = "Cookie: ";
		cookieString.Append(_cookies);
		request->SetCookie(cookieString);
	}
}

HttpConnection::~HttpConnection()
{
	delete _session;
	delete _transaction;
	delete _responseDictionary;
}

// Factory methods
HttpConnection *
HttpConnection::graffitiNearbyGetConnection(
		HttpConnectionListener *listener, double latitude, double longitude)
{
	String fullParameterPath;
	String urlPath;
	urlPath.Append(kHTTPMethodNameGraffitiNearby);
	fullParameterPath.Format(100, L"%ls?latitude=%f&longitude=%f", urlPath.GetPointer(), latitude, longitude);

	HttpConnection *connection = new HttpConnection(listener,
			fullParameterPath, NET_HTTP_METHOD_GET, null);

	return connection;
}

HttpConnection *
HttpConnection::userPostsGetConnection(
		HttpConnectionListener *listener, int uid)
{
	String fullParameterPath;
	String urlPath;
	urlPath.Append(kHTTPMethodNameUserPosts);
	fullParameterPath.Format(100, L"%ls?id=%d", urlPath.GetPointer(), uid);

	HttpConnection *connection = new HttpConnection(listener,
			fullParameterPath, NET_HTTP_METHOD_GET, null);

	return connection;
}


HttpConnection *
HttpConnection::graffitiNewPostConnection(
		HttpConnectionListener *listener, HttpMultipartEntity *graffitiParameters)
{
//	HttpConnection *connection = NULL;

//	HttpMultipartEntity *parameters = parametersForGraffiti(graffiti);

//	if (parameters) {
	HttpConnection *connection = new HttpConnection(listener, kHTTPMethodNameGraffitiNew,
				NET_HTTP_METHOD_POST, graffitiParameters);
//		delete parameters;
//	}

	return connection;
}

HttpConnection *
HttpConnection::userLoginPostConnection(
		HttpConnectionListener *listener, HttpMultipartEntity *userParameters)
{
	HttpConnection *connection = new HttpConnection(listener,
			kHTTPMethodNameUserLogin, NET_HTTP_METHOD_POST, userParameters);

	return connection;
}

HttpConnection *
HttpConnection::userSignupPostConnection(
		HttpConnectionListener *listener, HttpMultipartEntity *userParameters)
{
	HttpConnection *connection = new HttpConnection(listener,
			kHTTPMethodNameUserSignup, NET_HTTP_METHOD_POST, userParameters);

	return connection;
}

HttpConnection *
HttpConnection::userUpdatePutConnection(
		HttpConnectionListener *listener, HttpMultipartEntity *userParameters)
{
	HttpConnection *connection = new HttpConnection(listener,
			kHTTPMethodNameUserUpdate, NET_HTTP_METHOD_PUT, userParameters);

	return connection;
}

HttpConnection *
HttpConnection::userLogoutPostConnection(
		HttpConnectionListener *listener)
{
	HttpConnection *connection = new HttpConnection(listener,
			kHTTPMethodNameUserLogout, NET_HTTP_METHOD_POST, NULL);

	return connection;
}

// Instance Methods
void
HttpConnection::begin()
{
	_transaction->Submit();
}

// Utility methods
HttpMultipartEntity *
HttpConnection::parametersForDictionary(
		Tizen::Base::Collection::HashMap *dictionary)
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

HttpMultipartEntity *
HttpConnection::parametersForGraffiti(Graffiti *graffiti)
{
	HashMap *dictionary = (graffiti ? graffiti->parameterDictionary() : NULL);
	return parametersForDictionary(dictionary);
}

HttpMultipartEntity *
HttpConnection::parametersForUser(User *user)
{
	HashMap *dictionary = (user ? user->parameterDictionary() : NULL);
	return parametersForDictionary(dictionary);
}

void
HttpConnection::saveCookies()
{
	AppRegistry* appRegistry = Application::GetInstance()->GetAppRegistry();

	String tempCookies;
	result r = appRegistry->Get(cookiesKey, tempCookies);
	if (r == E_KEY_NOT_FOUND) {
		appRegistry->Add(cookiesKey, _cookies);
	} else {
		appRegistry->Set(cookiesKey, _cookies);
	}

	appRegistry->Save();
}

void
HttpConnection::loadCookies()
{
	AppRegistry* appRegistry = Application::GetInstance()->GetAppRegistry();

	appRegistry->Get(cookiesKey, _cookies);
}

// IHttpTransactionEventListener
void
HttpConnection::OnTransactionAborted(HttpSession &httpSession,
		HttpTransaction &httpTransaction, result r)
{
	_listener->connectionDidFail(this);
}

void
HttpConnection::OnTransactionCertVerificationRequiredN(
		HttpSession &httpSession, HttpTransaction &httpTransaction,
		Tizen::Base::String *pCert)
{
	if (pCert->Equals(kServerCert)) {
		httpTransaction.Resume();
	} else {
		httpTransaction.Pause();
		//	_listener->connectionDidFail(this);
	}
}

void
HttpConnection::OnTransactionCompleted(HttpSession &httpSession,
		HttpTransaction &httpTransaction)
{
	if (_responseDictionary) {
		_listener->connectionDidFinish(this, _responseDictionary);
	} else {
		_listener->connectionDidFail(this);
	}
}

void
HttpConnection::OnTransactionReadyToRead(HttpSession &httpSession,
		HttpTransaction &httpTransaction, int availableBodyLen)
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

void
HttpConnection::OnTransactionHeaderCompleted(HttpSession &httpSession,
		HttpTransaction &httpTransaction, int headerLen, bool bAuthRequired)
{
	HttpResponse* httpResponse = httpTransaction.GetResponse();
	IList* cookieList = httpResponse->GetCookies();

	if (cookieList == null) {
		return;
	}

	String cookieString = "";
	for (int i = 0; i < cookieList->GetCount(); i++) {
		HttpCookie *cookie = static_cast<HttpCookie*>(cookieList->GetAt(i));

		cookieString.Append(cookie->GetCookieName());
		cookieString.Append('=');
		cookieString.Append(cookie->GetCookieValue());

		cookieString.Append(';');
	}

	cookieString.SetLength(cookieString.GetLength() - 1);
	_cookies = cookieString;
}
