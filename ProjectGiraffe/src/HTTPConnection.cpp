/*
 * HTTPConnection.cpp
 *
 *  Created on: Mar 17, 2013
 *      Author: Elliott
 */


#include "HTTPConnection.h"
#include <cstdlib>

using namespace Tizen::Base;
using namespace Tizen::Net::Http;
using namespace Tizen::Web::Json;


HTTPConnection::HTTPConnection (String hostAddr){


//   Kick off http request for items based on location.
//   Populate item source array
  HttpSession* pHttpSession = null;
  HttpTransaction* pHttpTransaction = null;
  String* pProxyAddr = null;
 
  AppLog("Starting the HTTP Session");
  pHttpSession = new HttpSession();
  // HttpSession construction.
  pHttpSession->Construct(NET_HTTP_SESSION_MODE_NORMAL, pProxyAddr, hostAddr, null);

  // Open a new HttpTransaction.
  pHttpTransaction = pHttpSession->OpenTransactionN();

  // Add a listener.
  pHttpTransaction->AddHttpTransactionListener(*this);

  // Get an HTTP request.
  HttpRequest* pHttpRequest = pHttpTransaction->GetRequest();

  // Set the HTTP method and URI:
  pHttpRequest->SetMethod(NET_HTTP_METHOD_GET);
  pHttpRequest->SetUri(URI);

  // Submit the request:
  pHttpTransaction->Submit();

}

HTTPConnection::~HTTPConnection(){

  
}












void
HTTPConnection::OnTransactionAborted (HttpSession &httpSession, HttpTransaction &httpTransaction, result r)
{
  AppLog("HTTP Transaction Aborted");

  // Come up with notification of aborted transaction
}

void
HTTPConnection::OnTransactionCertVerificationRequiredN (HttpSession &httpSession, HttpTransaction &httpTransaction, Tizen::Base::String *pCert)
{

}

void
HTTPConnection::OnTransactionCompleted (HttpSession &httpSession, HttpTransaction &httpTransaction)
{
  AppLog("HTTP Transaction Completed");
}

void
HTTPConnection::OnTransactionHeaderCompleted (HttpSession &httpSession, HttpTransaction &httpTransaction, int headerLen, bool bAuthRequired)
{

}

void
HTTPConnection::OnTransactionReadyToRead (HttpSession &httpSession, HttpTransaction &httpTransaction, int availableBodyLen)
{
  HttpResponse* pHttpResponse = httpTransaction.GetResponse();
  HttpHeader* pHttpHeader = null;
  AppLog("Checking HTTP Status Code");
  if (pHttpResponse->GetHttpStatusCode() == HTTP_STATUS_OK)
  {

    ByteBuffer* pBody = null;
    String statusText = pHttpResponse->GetStatusText();
    String version = pHttpResponse->GetVersion();

    pHttpHeader = pHttpResponse->GetHeader();
    pBody = pHttpResponse->ReadBodyN();
    //delete pBody;

    //Parses from ByteBuffer
    IJsonValue* pValue = JsonParser::ParseN(*pBody);

    AppLog("Received HTTP response.");

    // Implement JSON parsing to return
    // list of maps corresponding to json objects
  }

}

void
HTTPConnection::OnTransactionReadyToWrite (HttpSession &httpSession, HttpTransaction &httpTransaction, int recommendedChunkSize)
{

}












