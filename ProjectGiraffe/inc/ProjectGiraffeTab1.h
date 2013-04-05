#ifndef _PROJECTGIRAFFE_TAB1_H_
#define _PROJECTGIRAFFE_TAB1_H_

#include <FBase.h>
#include <FUi.h>
#include <FWebJson.h>
#include <Fnet.h>
#include <FWeb.h>
<<<<<<< HEAD
#include "Graffiti.h"
#include "LoadingPopupThread.h"
||||||| merged common ancestors
#include "Graffiti.h"
=======
#include "HTTPConnection.h"
class Graffiti;
>>>>>>> origin/master

using namespace Tizen::Web::Json;

class ProjectGiraffeTab1 :
	public Tizen::Ui::Controls::Panel,
	public Tizen::Ui::Scenes::ISceneEventListener,
	public Tizen::Ui::Controls::ITableViewItemProvider,
	public Tizen::Ui::Controls::ITableViewItemEventListener,
	public Tizen::Net::Http::IHttpTransactionEventListener,
	public HTTPConnection::HTTPConnectionListener
	{
public:
<<<<<<< HEAD
	ProjectGiraffeTab1(void)
	: _pValueList(null)
	, _pJsonKeyList(null)
	, __pLoadingPopupThread(null)
	, _tableView(null) {}
||||||| merged common ancestors
	ProjectGiraffeTab1(void)
	: _pValueList(null)
	, _pJsonKeyList(null)
	, _tableView(null) {}
=======
	ProjectGiraffeTab1(void) :
		_pValueList(NULL),
		_pJsonKeyList(NULL),
		_items(NULL),
		_contentViews(NULL),
		_contextViews(NULL),
		_tableView(NULL) {}
>>>>>>> origin/master

	virtual ~ProjectGiraffeTab1(void);
	bool Initialize(void);
	void TraverseFunction(IJsonValue* pValue);
	void ParseAndDisplay(void);

	virtual result OnInitializing(void);
	virtual result OnTerminating(void);

	// HTTPConnectionListener
	virtual void connectionDidFinish(HTTPConnection *connection, Tizen::Base::Collection::HashMap *response);
	virtual void connectionDidFail(HTTPConnection *connection);

	// ISceneEventListener
	virtual void OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								   const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs);
	virtual void OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
									const Tizen::Ui::Scenes::SceneId& nextSceneId);

    // ITableViewItemEventListener
    virtual void OnTableViewItemStateChanged(Tizen::Ui::Controls::TableView& tableView, int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem, Tizen::Ui::Controls::TableViewItemStatus status);
    virtual void OnTableViewContextItemActivationStateChanged(Tizen::Ui::Controls::TableView& tableView, int itemIndex, Tizen::Ui::Controls::TableViewContextItem* pContextItem, bool activated);
    virtual void OnTableViewItemReordered(Tizen::Ui::Controls::TableView& tableView, int itemIndexFrom, int itemIndexTo);

    // ITableViewItemProvider
    virtual int GetItemCount(void);
    virtual Tizen::Ui::Controls::TableViewItem* CreateItem(int itemIndex, int itemWidth);
    virtual bool DeleteItem(int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem);
    virtual void UpdateItem(int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem);
    virtual int GetDefaultItemHeight(void);

    // IHttpTransactionEventListener
	virtual void OnTransactionAborted(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, result r);
	virtual void OnTransactionCertVerificationRequiredN(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, Tizen::Base::String *pCert);
	virtual void OnTransactionCompleted(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction);
	virtual void OnTransactionHeaderCompleted(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, int headerLen, bool bAuthRequired);
	virtual void OnTransactionReadyToRead(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, int availableBodyLen);
	virtual void OnTransactionReadyToWrite(Tizen::Net::Http::HttpSession &httpSession, Tizen::Net::Http::HttpTransaction &httpTransaction, int recommendedChunkSize);

protected:
	Tizen::Base::Collection::IList* _pValueList;
	Tizen::Base::Collection::ArrayList* _pJsonKeyList;
    int _isArray;

private:
    Tizen::Base::Collection::ArrayList *_items;
<<<<<<< HEAD
    LoadingPopupThread* __pLoadingPopupThread;
||||||| merged common ancestors
=======
    Tizen::Base::Collection::ArrayList *_contentViews;
    Tizen::Base::Collection::ArrayList *_contextViews;
>>>>>>> origin/master
    Tizen::Ui::Controls::TableView* _tableView;
    void updateItems();
    void updateViews();
    void setItems(Tizen::Base::Collection::ArrayList *items);
};

#endif // _PROJECTGIRAFFE_TAB1_H_
