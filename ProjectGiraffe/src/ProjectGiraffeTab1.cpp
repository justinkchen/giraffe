#include "ProjectGiraffeTab1.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Media;

using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;

ProjectGiraffeTab1::ProjectGiraffeTab1(void)
{

}

ProjectGiraffeTab1::~ProjectGiraffeTab1(void)
{

}

bool
ProjectGiraffeTab1::Initialize(void)
{
	result r = Construct(L"IDC_PANEL1");
	if (IsFailed(r))
		return false;

	return true;
}

#define kDebugUseDummyItems 1

void
ProjectGiraffeTab1::updateItems()
{
#if kDebugUseDummyItems
    itemCount = 50;
    /*
    itemCells = new GraffitiCell*[itemCount];
    for (int i = 0; i < itemCount; i++) {
    	GraffitiCell *cell = new GraffitiCell();
    	//cell->Initialize();
    	cell->setUsername(L"Username");
    	cell->setDistance(i);
    	cell->setText(L"Graffiti!");
    	itemCells[i] = cell;
    }
    */


    itemTitles = new String[itemCount];

    for (int i = 0; i < itemCount; i++) {
        String title;
        title.Format(30, L"Item %d", i);
        itemTitles[i] = title;
    }

#else
    // Kick off http request for items based on location.
#endif
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
    tableView = new TableView();
    tableView->Construct(Rectangle(0,0,formBounds.width, formBounds.height), \
                         true, TABLE_VIEW_SCROLL_BAR_STYLE_FADE_OUT);
    tableView->SetItemProvider(this);
    tableView->AddTableViewItemEventListener(*this);
    AddControl(*tableView);

    // Create tableViewContextItem
    tableViewContextItem = new TableViewContextItem();
    tableViewContextItem->Construct(Dimension(720,100));

	return r;
}

result
ProjectGiraffeTab1::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void
ProjectGiraffeTab1::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs)
{
    // Populate item source array
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
void ProjectGiraffeTab1::OnTableViewItemStateChanged(Tizen::Ui::Controls::TableView& tableView, int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem, Tizen::Ui::Controls::TableViewItemStatus status)
{
}
    
void ProjectGiraffeTab1::OnTableViewContextItemActivationStateChanged(Tizen::Ui::Controls::TableView& tableView, int itemIndex, Tizen::Ui::Controls::TableViewContextItem* pContextItem, bool activated)
{
}
    
void ProjectGiraffeTab1::OnTableViewItemReordered(Tizen::Ui::Controls::TableView& tableView, int itemIndexFrom, int itemIndexTo)
{
}
    
// ITableViewItemProvider
int ProjectGiraffeTab1::GetItemCount(void)
{
    return itemCount;
}

TableViewItem* ProjectGiraffeTab1::CreateItem(int itemIndex, int itemWidth)
{
    TableViewItem *item = new TableViewItem();
    item->Construct(Dimension(itemWidth, GetDefaultItemHeight()),
                    TABLE_VIEW_ANNEX_STYLE_NORMAL);
    //item->AddControl(*itemCells[itemIndex]);

    Label*label = new Label();
    label->Construct(Rectangle(0,0,itemWidth,item->GetBounds().height), itemTitles[itemIndex]);
    item->AddControl(*label);
    item->SetContextItem(tableViewContextItem);


    return item;
}
    
bool ProjectGiraffeTab1::DeleteItem(int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem)
{
    delete pItem;
    return true;
}
    
void ProjectGiraffeTab1::UpdateItem(int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem)
{
}
    
int ProjectGiraffeTab1::GetDefaultItemHeight(void)
{
    return 150;
}

