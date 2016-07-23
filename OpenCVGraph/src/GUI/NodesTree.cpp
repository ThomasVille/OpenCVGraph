#include "NodesTree.h"
#include "wx/wx.h"
#include "wx/colordlg.h"
#include "wx/numdlg.h"

#include "wx/artprov.h"
#include "wx/image.h"
#include "wx/imaglist.h"
#include "wx/treectrl.h"
#include "wx/math.h"
#include "wx/renderer.h"
#include "wx/wupdlock.h"

#include "icon1.xpm"
#include "icon2.xpm"
#include "icon3.xpm"
#include "icon4.xpm"
#include "icon5.xpm"

#include "state1.xpm"
#include "state2.xpm"
#include "state3.xpm"
#include "state4.xpm"
#include "state5.xpm"

#include "unchecked.xpm"
#include "checked.xpm"

using namespace std;

wxIMPLEMENT_DYNAMIC_CLASS(MyTreeCtrl, wxTreeCtrl);

// Hide the root
MyTreeCtrl::MyTreeCtrl(wxWindow *parent, std::shared_ptr<NodesProvider> nodesProvider, GraphView* graphView)
	: wxTreeCtrl(parent, wxID_ANY, wxDefaultPosition, wxSize(200, 200), wxTR_HIDE_ROOT | wxTR_LINES_AT_ROOT | wxTR_ROW_LINES | wxTR_HAS_BUTTONS | wxTR_TWIST_BUTTONS),
	m_nodesProvider(nodesProvider),
	m_graphView(graphView)
{
	CreateImageList();

	wxTreeItemId rootId = AddRoot(wxT("Root"), TreeCtrlIcon_Folder, TreeCtrlIcon_Folder, new MyTreeItemData(nullptr));
	AddItemsRecursively(rootId, m_nodesProvider->GetItems());
	ExpandAll();

	Bind(wxEVT_TREE_ITEM_ACTIVATED, &MyTreeCtrl::OnItemActivated, this);
}

void MyTreeCtrl::CreateImageList(int size)
{
	if (size == -1)
	{
		SetImageList(NULL);
		return;
	}
	if (size == 0)
		size = m_imageSize;
	else
		m_imageSize = size;

	// Make an image list containing small icons
	wxImageList *images = new wxImageList(size, size, true);

	// should correspond to TreeCtrlIcon_xxx enum
	wxBusyCursor wait;
	wxIcon icons[5];


	wxSize iconSize(size, size);

	icons[TreeCtrlIcon_File] =
		icons[TreeCtrlIcon_FileSelected] = wxArtProvider::GetIcon(wxART_NORMAL_FILE, wxART_LIST, iconSize);
	icons[TreeCtrlIcon_Folder] =
		icons[TreeCtrlIcon_FolderSelected] =
		icons[TreeCtrlIcon_FolderOpened] = wxArtProvider::GetIcon(wxART_FOLDER, wxART_LIST, iconSize);

	for (size_t i = 0; i < WXSIZEOF(icons); i++)
	{
		int sizeOrig = icons[0].GetWidth();
		if (size == sizeOrig)
		{
			images->Add(icons[i]);
		}
		else
		{
			images->Add(wxBitmap(wxBitmap(icons[i]).ConvertToImage().Rescale(size, size)));
		}
	}

	AssignImageList(images);
}

int MyTreeCtrl::OnCompareItems(const wxTreeItemId& item1,
	const wxTreeItemId& item2)
{
	return wxTreeCtrl::OnCompareItems(item1, item2);
}

void MyTreeCtrl::AddItemsRecursively(const wxTreeItemId& idParent, vector<shared_ptr<ModelNode>> nodes)
{
	// Append all nodes and their children
	for (auto node : nodes) {
		int image = node->HasChildren() ? TreeCtrlIcon_Folder : TreeCtrlIcon_File;
		wxTreeItemId id = AppendItem(idParent, node->GetName(), image , image+1, new MyTreeItemData(node));
		if (node->HasChildren())
			AddItemsRecursively(id, node->GetChildren());
	}
}

void MyTreeCtrl::DoToggleIcon(const wxTreeItemId& item)
{
	int image = GetItemImage(item) == TreeCtrlIcon_Folder
		? TreeCtrlIcon_File
		: TreeCtrlIcon_Folder;
	SetItemImage(item, image, wxTreeItemIcon_Normal);

	image = GetItemImage(item, wxTreeItemIcon_Selected) == TreeCtrlIcon_FolderSelected
		? TreeCtrlIcon_FileSelected
		: TreeCtrlIcon_FolderSelected;
	SetItemImage(item, image, wxTreeItemIcon_Selected);
}

// avoid repetition
#define TREE_EVENT_HANDLER(name)                                 \
void MyTreeCtrl::name(wxTreeEvent& event)                        \
{                                                                \
    event.Skip();                                                \
}

TREE_EVENT_HANDLER(OnBeginRDrag)
TREE_EVENT_HANDLER(OnDeleteItem)
TREE_EVENT_HANDLER(OnGetInfo)
TREE_EVENT_HANDLER(OnSetInfo)
TREE_EVENT_HANDLER(OnItemExpanded)
TREE_EVENT_HANDLER(OnItemExpanding)
TREE_EVENT_HANDLER(OnItemCollapsed)
TREE_EVENT_HANDLER(OnSelChanged)
TREE_EVENT_HANDLER(OnSelChanging)

#undef TREE_EVENT_HANDLER

void MyTreeCtrl::OnItemActivated(wxTreeEvent& event)
{
	wxTreeItemId itemId = event.GetItem();
	MyTreeItemData *item = (MyTreeItemData *)GetItemData(itemId);

	// Do nothing if we clicked on a folder
	if (item != NULL && !item->Get()->HasChildren())
	{
		// Create the new node and add it to the graphView and the graphEngine
		auto newNode = m_nodesProvider->GetNewNode(item->Get());
		m_graphView->AddNode(newNode);
	}
}

void MyTreeCtrl::OnItemMenu(wxTreeEvent& event)
{
	wxTreeItemId itemId = event.GetItem();
	wxCHECK_RET(itemId.IsOk(), "should have a valid item");

	MyTreeItemData *item = (MyTreeItemData *)GetItemData(itemId);
	wxPoint clientpt = event.GetPoint();
	wxPoint screenpt = ClientToScreen(clientpt);

	wxLogMessage(wxT("OnItemMenu for item \"%s\" at screen coords (%i, %i)"),
		item ? item->Get()->GetName() : wxString(wxS("unknown")), screenpt.x, screenpt.y);

	ShowMenu(itemId, clientpt);
	event.Skip();
}

void MyTreeCtrl::OnContextMenu(wxContextMenuEvent& event)
{
	wxPoint pt = event.GetPosition();

	wxLogMessage(wxT("OnContextMenu at screen coords (%i, %i)"), pt.x, pt.y);

	event.Skip();
}

void MyTreeCtrl::ShowMenu(wxTreeItemId id, const wxPoint& pt)
{
	wxString title;
	if (id.IsOk())
	{
		title << wxT("Menu for ") << GetItemText(id);
	}
	else
	{
		title = wxT("Menu for no particular item");
	}

#if wxUSE_MENUS
	wxMenu menu(title);
	menu.Append(TreeTest_About, wxT("&About"));
	menu.AppendSeparator();
	menu.Append(TreeTest_Highlight, wxT("&Highlight item"));
	menu.Append(TreeTest_Dump, wxT("&Dump"));

	PopupMenu(&menu, pt);
#endif // wxUSE_MENUS
}

void MyTreeCtrl::OnItemRClick(wxTreeEvent& event)
{
	wxTreeItemId itemId = event.GetItem();
	wxCHECK_RET(itemId.IsOk(), "should have a valid item");

	MyTreeItemData *item = (MyTreeItemData *)GetItemData(itemId);

	wxLogMessage(wxT("Item \"%s\" right clicked"), item ? item->Get()->GetName() : wxString(wxS("unknown")));

	event.Skip();
}