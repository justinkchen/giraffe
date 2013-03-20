

#ifndef HTTPCONNECTION_H_
#define HTTPCONNECTION_H_

#include <FBase.h>
#include <FUi.h>
#include <FWebJson.h>
#include <Fnet.h>
#include <FWeb.h>
#include "Graffiti.h"


using namespace Tizen::Base;

using namespace Tizen::Web::Json;

class HTTPConnection 
  : public Tizen::Net::Http::IHttpTransactionEventListener
  {


public:
  HTTPConnection(String hostAddr);
  virtual ~HTTPConnection();
  


  // IHttpTransactionEventListener
  virtual void OnTransactionAborted(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, result r);
  virtual void OnTransactionCertVerificationRequiredN(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, Tizen::Base::String *pCert);
  virtual void OnTransactionCompleted(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction);
  virtual void OnTransactionHeaderCompleted(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, int headerLen, bool bAuthRequired);
  virtual void OnTransactionReadyToRead(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, int availableBodyLen);
  virtual void OnTransactionReadyToWrite(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, int recommendedChunkSize);


private:
    String HOST_ADDR = L"http://ec2-54-243-69-6.compute-1.amazonaws.com/";
    String URI = L"http://ec2-54-243-69-6.compute-1.amazonaws.com/";




};




#endif /* HTTPCONNECTION_H_ */
