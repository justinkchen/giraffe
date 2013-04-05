

#ifndef HTTPCONNECTION_H_
#define HTTPCONNECTION_H_

#include <FBase.h>
#include <Fnet.h>

class Graffiti;
class User;

extern const Tizen::Base::String kHTTPMethodNameNearbyGraffiti;
extern const Tizen::Base::String kHTTPMethodNameNewGraffiti;
extern const Tizen::Base::String kHTTPMethodNameUserLogin;
extern const Tizen::Base::String kHTTPMethodNameUserSignup;
extern const Tizen::Base::String kHTTPMethodNameUserUpdate;
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
extern const Tizen::Base::String kHTTPParamNameFlagged;
extern const Tizen::Base::String kHTTPParamNameDateCreated;
extern const Tizen::Base::String kHTTPParamNameUser;
extern const Tizen::Base::String kHTTPParamNameUserID;
extern const Tizen::Base::String kHTTPParamNameFullname;
extern const Tizen::Base::String kHTTPParamNameUsername;
extern const Tizen::Base::String kHTTPParamNameEmail;
extern const Tizen::Base::String kHTTPParamNameYear;
extern const Tizen::Base::String kHTTPParamNameMonth;
extern const Tizen::Base::String kHTTPParamNameDay;
extern const Tizen::Base::String kHTTPParamNameHour;
extern const Tizen::Base::String kHTTPParamNameMinute;
extern const Tizen::Base::String kHTTPParamNameSecond;
extern const Tizen::Base::String kHTTPParamNameError;

class HTTPConnection 
  : public Tizen::Net::Http::IHttpTransactionEventListener
{
public:
	  // Destructor
	  virtual ~HTTPConnection();

	  // Listener class
	  class HTTPConnectionListener
	  {
	  public:
		  virtual void connectionDidFinish(HTTPConnection *connection, Tizen::Base::Collection::HashMap *response) {}
		  virtual void connectionDidFail(HTTPConnection *connection) {}
	  };

	  // Factory methods
	  static HTTPConnection *nearbyGraffitiGetConnection(HTTPConnectionListener *listener, double latitude, double longitude);
	  static HTTPConnection *newGraffitiPostConnection(HTTPConnectionListener *listener, Graffiti *graffiti);
	  static HTTPConnection *userLoginPostConnection(HTTPConnectionListener *listener, Tizen::Net::Http::HttpMultipartEntity *userParameters);
	  static HTTPConnection *userSignupPostConnection(HTTPConnectionListener *listener, Tizen::Net::Http::HttpMultipartEntity *userParameters);
	  static HTTPConnection *userUpdatePutConnection(HTTPConnectionListener *listener, Tizen::Net::Http::HttpMultipartEntity *userParameters);
	  static HTTPConnection *userLogoutPostConnection(HTTPConnectionListener *listener);

	  // Instance Methods
	  void begin();

	  // Accessors
	  const Tizen::Base::String methodName() { return _methodName; }

private:
	  // Constructor
	  HTTPConnection(HTTPConnectionListener *listener,
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
	  virtual void OnTransactionHeaderCompleted(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, int headerLen, bool bAuthRequired) {}
  	  virtual void OnTransactionReadyToWrite(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, int recommendedChunkSize) {}

  	  // Private Members
  	  const Tizen::Base::String _methodName;
  	  HTTPConnectionListener *_listener;
  	  Tizen::Net::Http::HttpSession *_session;
  	  Tizen::Net::Http::HttpTransaction *_transaction;
  	  Tizen::Base::Collection::HashMap *_responseDictionary;
};




#endif /* HTTPCONNECTION_H_ */
