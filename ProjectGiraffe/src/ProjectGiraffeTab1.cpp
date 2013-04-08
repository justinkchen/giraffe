#include "ProjectGiraffeTab1.h"
#include "ProjectGiraffeMainForm.h"
#include "User.h"
#include "GraffitiCellContentView.h"
#include "GraffitiCellSocialContextView.h"
#include <cstdlib>
#include <time.h>
#include <typeinfo>

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Media;

using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;

using namespace Tizen::Base;
using namespace Tizen::Net::Http;
using namespace Tizen::Web::Json;

using namespace Tizen::System;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Base::Utility;
using namespace Tizen::Base::Collection;
using namespace Tizen::Io;

ProjectGiraffeTab1::~ProjectGiraffeTab1(void)
{

}

bool
ProjectGiraffeTab1::Initialize(void)
{
	result r = Construct(L"IDC_PANEL1");
	srand (time(NULL));
	if (IsFailed(r))
		return false;

	return true;
}

#define kDebugUseDummyItems 0
#define kDebugUseHttpConnection 0

void
ProjectGiraffeTab1::updateItems()
{
#if kDebugUseDummyItems
	AppLog("Creating dummy items");
	User *dummyUser = new User();
	dummyUser->setUsername(L"Username");
	for (int i = 0; i < 10; i++) {
		Graffiti *graffiti = new Graffiti();
		graffiti->setUser(dummyUser);
		graffiti->setText(L"dummy string");
		_items->Add(graffiti);
	}

#else

#if kDebugUseHttpConnection

	double latitude = ProjectGiraffeMainForm::currentLatitude;
	double longitude = ProjectGiraffeMainForm::currentLongitude;
	HttpConnection *connection = HttpConnection::nearbyGraffitiGetConnection(this,latitude,longitude);
	connection->begin();

#else
	// Kick off http request for items based on location.
	// Populate item source array
	HttpSession* pHttpSession = null;
	HttpTransaction* pHttpTransaction = null;
	String* pProxyAddr = null;
	String hostAddr = L"http://ec2-54-243-69-6.compute-1.amazonaws.com/";
	String uri = L"http://ec2-54-243-69-6.compute-1.amazonaws.com/";

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
	pHttpRequest->SetUri(uri);

	// Submit the request:
	pHttpTransaction->Submit();
#endif

#endif
}

void ProjectGiraffeTab1::updateViews()
{
	// Remove all views if they exist
	if (_contentViews) _contentViews->RemoveAll(true);
	if (_contextViews) _contextViews->RemoveAll(true);
	delete _contentViews;
	delete _contextViews;

	if (_items && _items->GetCount()) {
		_contentViews = new ArrayList(SingleObjectDeleter);
		_contentViews->Construct();
		_contextViews = new ArrayList(SingleObjectDeleter);
		_contextViews->Construct();

		IEnumerator *iter = _items->GetEnumeratorN();
		int width = GetSize().width;
		while (iter->MoveNext() == E_SUCCESS) {
			Graffiti *graffiti = static_cast<Graffiti *>(iter->GetCurrent());
			if (graffiti) {
				// Create content view
				GraffitiCellContentView *contentView = new GraffitiCellContentView();
				contentView->Construct(Rectangle(0, 0, width, GetDefaultItemHeight()));
				contentView->setGraffiti(graffiti);
				contentView->sizeToFit();
				_contentViews->Add(contentView);

				// Create social context view
				GraffitiCellSocialContextView *socialContextView = new GraffitiCellSocialContextView();
				socialContextView->Construct(contentView->GetBounds());
				socialContextView->setGraffiti(graffiti);
				_contextViews->Add((Panel *)socialContextView);
			}
		}
	} else {
		_contentViews = NULL;
		_contextViews = NULL;
	}
}

void ProjectGiraffeTab1::setItems(ArrayList *items)
{
	if (_items != items) {
		// Deallocate old items
		if (_items) _items->RemoveAll(true);
		delete _items;
		_items = items;

		// Update views
		updateViews();

		// Use new items/views in table
		_tableView->UpdateTableView();
	}
}

result
ProjectGiraffeTab1::OnInitializing(void)
{
	result r = E_SUCCESS;

	// Layout setting
	const Form* pForm = dynamic_cast<Form*>(GetParent());
	Rectangle formBounds = pForm->GetClientAreaBounds();
	RelativeLayout* pRelativeLayout = dynamic_cast<RelativeLayout*>(pForm->GetLandscapeLayoutN());
	pRelativeLayout->SetHorizontalFitPolicy(*this, FIT_POLICY_PARENT);
	pRelativeLayout->SetVerticalFitPolicy(*this, FIT_POLICY_PARENT);
	delete pRelativeLayout;
	pRelativeLayout = dynamic_cast<RelativeLayout*>(pForm->GetPortraitLayoutN());
	pRelativeLayout->SetHorizontalFitPolicy(*this, FIT_POLICY_PARENT);
	pRelativeLayout->SetVerticalFitPolicy(*this, FIT_POLICY_PARENT);
	delete pRelativeLayout;

	// Create tableView
	_tableView = new TableView();
	_tableView->Construct(Rectangle(0,0,formBounds.width, formBounds.height), \
			true, TABLE_VIEW_SCROLL_BAR_STYLE_FADE_OUT);
	_tableView->SetItemProvider(this);
	_tableView->AddTableViewItemEventListener(*this);
	AddControl(*_tableView);

	_items = new (std::nothrow) ArrayList();

	_pValueList = new (std::nothrow) LinkedList();

	_pJsonKeyList = new (std::nothrow) ArrayList();
	_pJsonKeyList->Construct();
	_isArray = 0;

	return r;
}

result
ProjectGiraffeTab1::OnTerminating(void)
{
	if (_pValueList)
	{
		_pValueList->RemoveAll(true);
		delete _pValueList;
		_pValueList = null;
	}

	if (_pJsonKeyList)
	{
		_pJsonKeyList->RemoveAll(true);
		delete _pJsonKeyList;
		_pJsonKeyList = null;
	}

	if (_items)
	{
		_items->RemoveAll(true);
		delete _items;
		_items = null;
	}

	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void
ProjectGiraffeTab1::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
		const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs)
{
	updateItems();

	AppLog("OnSceneActivatedN");
}

void
ProjectGiraffeTab1::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
		const Tizen::Ui::Scenes::SceneId& nextSceneId)
{
	// TODO:
	// Add your scene deactivate code here
	AppLog("OnSceneDeactivated");
}

// ITableViewItemEventListener
void ProjectGiraffeTab1::OnTableViewItemStateChanged(Tizen::Ui::Controls::TableView& tableView,
		int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem, Tizen::Ui::Controls::TableViewItemStatus status)
{

}

void ProjectGiraffeTab1::OnTableViewContextItemActivationStateChanged(Tizen::Ui::Controls::TableView& tableView, int itemIndex,
		Tizen::Ui::Controls::TableViewContextItem* pContextItem, bool activated)
{
}

void ProjectGiraffeTab1::OnTableViewItemReordered(Tizen::Ui::Controls::TableView& tableView, int itemIndexFrom, int itemIndexTo)
{
}

// ITableViewItemProvider
int ProjectGiraffeTab1::GetItemCount(void)
{
	AppLog("Counting Items");
	return _items ? _items->GetCount() : 0;
}

TableViewItem* ProjectGiraffeTab1::CreateItem(int itemIndex, int itemWidth)
{
	AppLog("Creating Items");

	// Fetch Graffiti object
	Graffiti *graffiti = dynamic_cast<Graffiti *>(_items->GetAt(itemIndex));

	// Create item
	TableViewItem *item = new TableViewItem();
	item->Construct(Dimension(itemWidth, GetDefaultItemHeight()),
			TABLE_VIEW_ANNEX_STYLE_NORMAL);

	// Create contextItem
	TableViewContextItem *contextItem = new TableViewContextItem();
	contextItem->Construct(item->GetSize());
	item->SetContextItem(contextItem);

#if kDebugUseHttpConnection
	GraffitiCellContentView *contentView = static_cast<GraffitiCellContentView *>(_contentViews->GetAt(itemIndex));
	if (contentView) {
		item->AddControl(*contentView);
		item->SetSize(contentView->GetSize());
		contextItem->SetSize(contentView->GetSize());
	}
	GraffitiCellSocialContextView *contextView = static_cast<GraffitiCellSocialContextView *>(_contextViews->GetAt(itemIndex));
	if (contextView) {
		contextItem->AddControl(*contextView);
	}
#else
	// Create content view
	GraffitiCellContentView *contentView = new GraffitiCellContentView();
	contentView->Construct(Rectangle(0, 0, itemWidth, GetDefaultItemHeight()));
	contentView->setGraffiti(graffiti);
	contentView->sizeToFit();
	item->AddControl(*contentView);
	item->SetSize(contentView->GetSize());
	contextItem->SetSize(contentView->GetSize());

	// Create social context view
	GraffitiCellSocialContextView *socialContextView = new GraffitiCellSocialContextView();
	socialContextView->Construct(contentView->GetBounds());
	socialContextView->setGraffiti(graffiti);
	contextItem->AddControl(*socialContextView);
#endif


	return item;
}

bool ProjectGiraffeTab1::DeleteItem(int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem)
{
	AppLog("Deleting item %d", itemIndex);
// TODO: Figure out what is causing this to crash...seems to work fine without this, but would be good to fix I think.
//	delete pItem;
	return true;
}

void ProjectGiraffeTab1::UpdateItem(int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem)
{
	AppLog("Updating Items");
}

int ProjectGiraffeTab1::GetDefaultItemHeight(void)
{
	return 150;
}


void ProjectGiraffeTab1::connectionDidFinish(HttpConnection *connection, Tizen::Base::Collection::HashMap *response)
{
	AppLog("HttpConnection finished");
	if (response) {
		ArrayList *graffitiList = static_cast<ArrayList *>(response->GetValue(kHTTPParamNameGraffiti));
		if (graffitiList) {
			ArrayList *newItems = new ArrayList(SingleObjectDeleter);
			newItems->Construct();

			for (int i = 0; i < graffitiList->GetCount(); i++) {
				HashMap *graffitiDictionary = static_cast<HashMap *>(graffitiList->GetAt(i));
				if (graffitiDictionary) {
					Graffiti *newGraffiti = new Graffiti();
					newGraffiti->updateFromDictionary(graffitiDictionary);
					newItems->Add(newGraffiti);
				}
			}
			setItems(newItems);
		}
	} else {
		connectionDidFail(connection);
	}
}

void ProjectGiraffeTab1::connectionDidFail(HttpConnection *connection)
{
	AppLog("HttpConnection failed");

	MessageBox msgBox;
	msgBox.Construct(L"HTTP STATUS", L"HTTP Request Aborted, Check internet connection", MSGBOX_STYLE_NONE, 3000);
	int modalresult = 0;
	msgBox.ShowAndWait(modalresult);
	delete connection;
}

void
ProjectGiraffeTab1::OnTransactionAborted (HttpSession &httpSession, HttpTransaction &httpTransaction, result r)
{
	AppLog("HTTP Transaction Aborted");

	MessageBox msgBox;
	msgBox.Construct(L"HTTP STATUS", L"HTTP Request Aborted, Check internet connection", MSGBOX_STYLE_NONE, 3000);
	int modalresult = 0;
	msgBox.ShowAndWait(modalresult);
}

void
ProjectGiraffeTab1::OnTransactionCertVerificationRequiredN (HttpSession &httpSession, HttpTransaction &httpTransaction, Tizen::Base::String *pCert)
{

}

void
ProjectGiraffeTab1::OnTransactionCompleted (HttpSession &httpSession, HttpTransaction &httpTransaction)
{
	AppLog("HTTP Transaction Completed");
}

void
ProjectGiraffeTab1::OnTransactionHeaderCompleted (HttpSession &httpSession, HttpTransaction &httpTransaction, int headerLen, bool bAuthRequired)
{

}

void
ProjectGiraffeTab1::OnTransactionReadyToRead (HttpSession &httpSession, HttpTransaction &httpTransaction, int availableBodyLen)
{
	HttpResponse* pHttpResponse = httpTransaction.GetResponse();
	HttpHeader* pHttpHeader = null;
	AppLog("Checking HTTP Status Code");
	if (pHttpResponse->GetHttpStatusCode() == HTTP_STATUS_OK)
	{
		//		MessageBox msgBox;
		//		msgBox.Construct(L"HTTP STATUS", L"HTTP Request OK", MSGBOX_STYLE_NONE, 3000);
		//		int modalresult = 0;
		//		msgBox.ShowAndWait(modalresult);

		ByteBuffer* pBody = null;
		String statusText = pHttpResponse->GetStatusText();
		String version = pHttpResponse->GetVersion();

		pHttpHeader = pHttpResponse->GetHeader();
		pBody = pHttpResponse->ReadBodyN();
		//delete pBody;

		//Parses from ByteBuffer
		IJsonValue* pValue = JsonParser::ParseN(*pBody);

		AppLog("Received HTTP response.");

		AppLog("Before traverse %d", _tableView->GetItemCount());
		_pJsonKeyList->RemoveAll(true);
		_pValueList->RemoveAll(true);
		_items->RemoveAll(true);
		// Populate the panel
		TraverseFunction(pValue);

		AppLog("After traverse");

		//clean up allocated jsonValues
		if (pValue->GetType() == JSON_TYPE_OBJECT)
		{
			// Converts the pValue to JsonObject
			JsonObject* pObject = static_cast< JsonObject* >(pValue);
			pObject->RemoveAll(true);
		}
		else if (pValue->GetType() == JSON_TYPE_ARRAY)
		{
			// Converts the pValue to JsonArray
			JsonArray* pArray = static_cast< JsonArray* >(pValue);
			pArray->RemoveAll(true);
		}

		delete pBody;
		delete pValue;
		_tableView->ScrollToItem(0);
	}else{
		AppLog("HTTP Status not OK");
	}
}

void
ProjectGiraffeTab1::OnTransactionReadyToWrite (HttpSession &httpSession, HttpTransaction &httpTransaction, int recommendedChunkSize)
{

}

//Recursively traverse IJsonValue obtained by parser (using ParseN)
void
ProjectGiraffeTab1::TraverseFunction(IJsonValue* pValue)
{
	TryReturnVoid(_tableView, "tableView is null");

	TryReturnVoid(pValue, "input jsonvalue pointer is null");

	User *dummyUser = new User();
	dummyUser->setUsername(L"CS210 Student");

	Graffiti *lastCreatedGraffiti = NULL;

	switch (pValue->GetType())
	{
	case JSON_TYPE_OBJECT:
	{
		JsonObject* pObject = static_cast< JsonObject* >(pValue);
		IMapEnumeratorT< const String*, IJsonValue* >* pMapEnum = pObject->GetMapEnumeratorN();
		while (pMapEnum->MoveNext() == E_SUCCESS)
		{
			AppLog("IN JSON OBJECT");
			const String* key = null;
			IJsonValue* value = null;
			pMapEnum->GetKey(key);
			pMapEnum->GetValue(value);
			String* pListKey = new (std::nothrow) String(*key);
			_pJsonKeyList->Add(*pListKey);
			AppLog("Key: %ls", pListKey->GetPointer());

			if(pListKey->Equals("message",true)){
				AppLog("Message received");
				lastCreatedGraffiti = new Graffiti();
				lastCreatedGraffiti->setUser(dummyUser);
				JsonString* pVal = static_cast< JsonString* >(value);
				String* pListValue = new (std::nothrow) String(*pVal);
				lastCreatedGraffiti->setText(String(*pListValue));
				_items->Add(lastCreatedGraffiti);
				AppLog("message : %ls", lastCreatedGraffiti->text().GetPointer());
			} else if (value && pListKey->Equals("latitude", true)) {
				JsonNumber *jsonNum = static_cast<JsonNumber *>(value);
				Double *latValue = static_cast<Double *>(jsonNum);
				if (latValue && lastCreatedGraffiti) {
					lastCreatedGraffiti->setLatitude(latValue->ToFloat());
					AppLog("latitude : %f", lastCreatedGraffiti->longitude());
				}
			} else if (value != NULL && pListKey->Equals("longitude", true)) {
				JsonNumber *jsonNum = static_cast<JsonNumber *>(value);
				Double *lonValue = static_cast<Double *>(jsonNum);
				if (lonValue && lastCreatedGraffiti) {
					lastCreatedGraffiti->setLongitude(lonValue->ToFloat());
					AppLog("longitude : %f", lastCreatedGraffiti->longitude());
				}
			}
		}

		delete pMapEnum;
	}
	break;

	case JSON_TYPE_STRING:
	{
		JsonString* pVal = static_cast< JsonString* >(pValue);
		if (_isArray == 0)
		{
			String* pStr = new (std::nothrow) String(*pVal);
			_pValueList->Add(*pStr);
		}
	}
	break;

	case JSON_TYPE_ARRAY:
	{
		JsonArray* pJsonArray = static_cast< JsonArray* >(pValue);
		pJsonArray->GetCount();
		IEnumeratorT< IJsonValue* >* pEnum = pJsonArray->GetEnumeratorN();
		while (pEnum->MoveNext() == E_SUCCESS)
		{
			IJsonValue* pValue = null;
			pEnum->GetCurrent(pValue);
			if ((pValue->GetType() == JSON_TYPE_STRING) ||
					(pValue->GetType() == JSON_TYPE_NUMBER) ||
					(pValue->GetType() == JSON_TYPE_BOOL)   ||
					(pValue->GetType() == JSON_TYPE_NULL)) {
				_isArray = 1;
			}
			TraverseFunction(pValue);
		}
		delete pEnum;
	}
	break;

	case JSON_TYPE_NUMBER:
	{
		JsonNumber* pVal = static_cast< JsonNumber* >(pValue);
		String* pStr = new (std::nothrow) String((pVal->ToString()));
		if (_isArray == 0)
			_pValueList->Add(*pStr);
	}
	break;

	case JSON_TYPE_BOOL:
	{
		String* pStr = null;
		JsonBool* pVal = static_cast< JsonBool* >(pValue);
		if (*pVal == true)
			pStr = new (std::nothrow) String("true");
		else
			pStr = new (std::nothrow) String("false");
		if (_isArray == 0)
			_pValueList->Add(*pStr);
	}
	break;

	case JSON_TYPE_NULL:
	{
		String* pStr = null;
		pStr = new (std::nothrow) String("null");
		if (_isArray == 0)
			_pValueList->Add(*pStr);
	}
	break;

	default:
		break;
	}
	_tableView->UpdateTableView();
}

