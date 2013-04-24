

#ifndef HttpConnection_H_
#define HttpConnection_H_

#include <FApp.h>
#include <FBase.h>
#include <Fnet.h>

class Graffiti;
class User;

extern const Tizen::Base::String kHTTPMethodNameGraffitiNearby;
extern const Tizen::Base::String kHTTPMethodNameGraffitiNew;
extern const Tizen::Base::String kHTTPMethodNameGraffitiLike;
extern const Tizen::Base::String kHTTPMethodNameGraffitiFlag;

extern const Tizen::Base::String kHTTPMethodNameUserLogin;
extern const Tizen::Base::String kHTTPMethodNameUserSignup;
extern const Tizen::Base::String kHTTPMethodNameUserUpdate;
extern const Tizen::Base::String kHTTPMethodNameUserPosts;
extern const Tizen::Base::String kHTTPMethodNameUserStats;
extern const Tizen::Base::String kHTTPMethodNameUserLogout;

extern const Tizen::Base::String kHTTPParamNameGraffiti;
extern const Tizen::Base::String kHTTPParamNameText;
extern const Tizen::Base::String kHTTPParamNameImageURL;
extern const Tizen::Base::String kHTTPParamNameLongitude;
extern const Tizen::Base::String kHTTPParamNameLatitude;
extern const Tizen::Base::String kHTTPParamNameDirectionX;
extern const Tizen::Base::String kHTTPParamNameDirectionY;
extern const Tizen::Base::String kHTTPParamNameDirectionZ;
extern const Tizen::Base::String kHTTPParamNameLikeCount;
extern const Tizen::Base::String kHTTPParamNameRadius;
extern const Tizen::Base::String kHTTPParamNameFlagged;
extern const Tizen::Base::String kHTTPParamNameDateCreated;
extern const Tizen::Base::String kHTTPParamNameUser;
extern const Tizen::Base::String kHTTPParamNameUserID;
extern const Tizen::Base::String kHTTPParamNameFullname;
extern const Tizen::Base::String kHTTPParamNameUsername;
extern const Tizen::Base::String kHTTPParamNameEmail;
extern const Tizen::Base::String kHTTPParamNameAvatarUrl;
extern const Tizen::Base::String kHTTPParamNameYear;
extern const Tizen::Base::String kHTTPParamNameMonth;
extern const Tizen::Base::String kHTTPParamNameDay;
extern const Tizen::Base::String kHTTPParamNameHour;
extern const Tizen::Base::String kHTTPParamNameMinute;
extern const Tizen::Base::String kHTTPParamNameSecond;
extern const Tizen::Base::String kHTTPParamNameError;

class HttpConnection
  : public Tizen::Net::Http::IHttpTransactionEventListener
{
public:
	  // Destructor
	  virtual ~HttpConnection();

	  // Listener class
	  class HttpConnectionListener
	  {
	  public:
		  virtual void connectionDidFinish(HttpConnection *connection, Tizen::Base::Collection::HashMap *response) {}
		  virtual void connectionDidFail(HttpConnection *connection) {}
	  };

	  // Factory methods
	  static HttpConnection *nearbyGraffitiGetConnection(HttpConnectionListener *listener, double latitude, double longitude);
	  static HttpConnection *newGraffitiPostConnection(HttpConnectionListener *listener, Graffiti *graffiti);
	  static HttpConnection *userLoginPostConnection(HttpConnectionListener *listener, Tizen::Net::Http::HttpMultipartEntity *userParameters);
	  static HttpConnection *userSignupPostConnection(HttpConnectionListener *listener, Tizen::Net::Http::HttpMultipartEntity *userParameters);
	  static HttpConnection *userUpdatePutConnection(HttpConnectionListener *listener, Tizen::Net::Http::HttpMultipartEntity *userParameters);
	  static HttpConnection *userLogoutPostConnection(HttpConnectionListener *listener);
	  static HttpConnection *userPostsGetConnection(HttpConnectionListener *listener, int uid);

	  // Instance Methods
	  void begin();

	  // Accessors
	  const Tizen::Base::String methodName() { return _methodName; }

	  static void saveCookies(void);
	  static void loadCookies(void);

private:
	  // Constructor
	  HttpConnection(HttpConnectionListener *listener,
			  	  	 const Tizen::Base::String methodName,
			  	  	 Tizen::Net::Http::NetHttpMethod methodType,
			  	  	 Tizen::Net::Http::HttpMultipartEntity *parameters);

	  // Utility methods
	  static Tizen::Net::Http::HttpMultipartEntity *parametersForDictionary(Tizen::Base::Collection::HashMap *dictionary);
	  static Tizen::Net::Http::HttpMultipartEntity *parametersForGraffiti(Graffiti *graffiti);
	  static Tizen::Net::Http::HttpMultipartEntity *parametersForUser(User *user);

	  // IHttpTransactionEventListener
	  virtual void OnTransactionAborted(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, result r);
	  virtual void OnTransactionCertVerificationRequiredN(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, Tizen::Base::String *pCert);
	  virtual void OnTransactionCompleted(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction);
  	  virtual void OnTransactionReadyToRead(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, int availableBodyLen);
	  virtual void OnTransactionHeaderCompleted(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, int headerLen, bool bAuthRequired);
  	  virtual void OnTransactionReadyToWrite(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, int recommendedChunkSize) {}

  	  // Private Members
  	  const Tizen::Base::String _methodName;
  	  HttpConnectionListener *_listener;
  	  Tizen::Net::Http::HttpSession *_session;
  	  Tizen::Net::Http::HttpTransaction *_transaction;
  	  Tizen::Base::Collection::HashMap *_responseDictionary;
};




#endif /* HttpConnection_H_ */
