#ifndef _PROJECTGIRAFFE_TAB1_H_
#define _PROJECTGIRAFFE_TAB1_H_

#include <FBase.h>
#include <FUi.h>
#include "GraffitiCell.h"

class ProjectGiraffeTab1
	: public Tizen::Ui::Controls::Panel
	, public Tizen::Ui::Scenes::ISceneEventListener
	, public Tizen::Ui::Controls::ITableViewItemProvider
	, public Tizen::Ui::Controls::ITableViewItemEventListener
	{
public:
	ProjectGiraffeTab1(void);
	virtual ~ProjectGiraffeTab1(void);
	bool Initialize(void);

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
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

private:
    Tizen::Ui::Controls::TableView* tableView;
    Tizen::Ui::Controls::TableViewContextItem* tableViewContextItem;

    unsigned int itemCount;
    //GraffitiCell **itemCells;
    Tizen::Base::String *itemTitles;
    virtual void updateItems();
};

#endif // _PROJECTGIRAFFE_TAB1_H_
