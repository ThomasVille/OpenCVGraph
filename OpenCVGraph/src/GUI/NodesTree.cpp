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
MyTreeCtrl::MyTreeCtrl(wxWindow *parent, std::shared_ptr<NodesProvider> nodesProvider)
	: wxTreeCtrl(parent, wxID_ANY, wxDefaultPosition, wxSize(200, 200), wxTR_HIDE_ROOT | wxTR_LINES_AT_ROOT | wxTR_ROW_LINES | wxTR_HAS_BUTTONS | wxTR_TWIST_BUTTONS),
	m_nodesProvider(nodesProvider)
{
	CreateImageList();

	wxTreeItemId rootId = AddRoot(wxT("Root"), TreeCtrlIcon_Folder, TreeCtrlIcon_Folder, new MyTreeItemData(nullptr));
	AddItemsRecursively(rootId, m_nodesProvider->GetItems());
	ExpandAll();
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

void LogKeyEvent(const wxChar *name, const wxKeyEvent& event)
{
	wxString key;
	long keycode = event.GetKeyCode();
	{
		switch (keycode)
		{
		case WXK_BACK: key = wxT("BACK"); break;
		case WXK_TAB: key = wxT("TAB"); break;
		case WXK_RETURN: key = wxT("RETURN"); break;
		case WXK_ESCAPE: key = wxT("ESCAPE"); break;
		case WXK_SPACE: key = wxT("SPACE"); break;
		case WXK_DELETE: key = wxT("DELETE"); break;
		case WXK_START: key = wxT("START"); break;
		case WXK_LBUTTON: key = wxT("LBUTTON"); break;
		case WXK_RBUTTON: key = wxT("RBUTTON"); break;
		case WXK_CANCEL: key = wxT("CANCEL"); break;
		case WXK_MBUTTON: key = wxT("MBUTTON"); break;
		case WXK_CLEAR: key = wxT("CLEAR"); break;
		case WXK_SHIFT: key = wxT("SHIFT"); break;
		case WXK_ALT: key = wxT("ALT"); break;
		case WXK_CONTROL: key = wxT("CONTROL"); break;
		case WXK_MENU: key = wxT("MENU"); break;
		case WXK_PAUSE: key = wxT("PAUSE"); break;
		case WXK_CAPITAL: key = wxT("CAPITAL"); break;
		case WXK_END: key = wxT("END"); break;
		case WXK_HOME: key = wxT("HOME"); break;
		case WXK_LEFT: key = wxT("LEFT"); break;
		case WXK_UP: key = wxT("UP"); break;
		case WXK_RIGHT: key = wxT("RIGHT"); break;
		case WXK_DOWN: key = wxT("DOWN"); break;
		case WXK_SELECT: key = wxT("SELECT"); break;
		case WXK_PRINT: key = wxT("PRINT"); break;
		case WXK_EXECUTE: key = wxT("EXECUTE"); break;
		case WXK_SNAPSHOT: key = wxT("SNAPSHOT"); break;
		case WXK_INSERT: key = wxT("INSERT"); break;
		case WXK_HELP: key = wxT("HELP"); break;
		case WXK_NUMPAD0: key = wxT("NUMPAD0"); break;
		case WXK_NUMPAD1: key = wxT("NUMPAD1"); break;
		case WXK_NUMPAD2: key = wxT("NUMPAD2"); break;
		case WXK_NUMPAD3: key = wxT("NUMPAD3"); break;
		case WXK_NUMPAD4: key = wxT("NUMPAD4"); break;
		case WXK_NUMPAD5: key = wxT("NUMPAD5"); break;
		case WXK_NUMPAD6: key = wxT("NUMPAD6"); break;
		case WXK_NUMPAD7: key = wxT("NUMPAD7"); break;
		case WXK_NUMPAD8: key = wxT("NUMPAD8"); break;
		case WXK_NUMPAD9: key = wxT("NUMPAD9"); break;
		case WXK_MULTIPLY: key = wxT("MULTIPLY"); break;
		case WXK_ADD: key = wxT("ADD"); break;
		case WXK_SEPARATOR: key = wxT("SEPARATOR"); break;
		case WXK_SUBTRACT: key = wxT("SUBTRACT"); break;
		case WXK_DECIMAL: key = wxT("DECIMAL"); break;
		case WXK_DIVIDE: key = wxT("DIVIDE"); break;
		case WXK_F1: key = wxT("F1"); break;
		case WXK_F2: key = wxT("F2"); break;
		case WXK_F3: key = wxT("F3"); break;
		case WXK_F4: key = wxT("F4"); break;
		case WXK_F5: key = wxT("F5"); break;
		case WXK_F6: key = wxT("F6"); break;
		case WXK_F7: key = wxT("F7"); break;
		case WXK_F8: key = wxT("F8"); break;
		case WXK_F9: key = wxT("F9"); break;
		case WXK_F10: key = wxT("F10"); break;
		case WXK_F11: key = wxT("F11"); break;
		case WXK_F12: key = wxT("F12"); break;
		case WXK_F13: key = wxT("F13"); break;
		case WXK_F14: key = wxT("F14"); break;
		case WXK_F15: key = wxT("F15"); break;
		case WXK_F16: key = wxT("F16"); break;
		case WXK_F17: key = wxT("F17"); break;
		case WXK_F18: key = wxT("F18"); break;
		case WXK_F19: key = wxT("F19"); break;
		case WXK_F20: key = wxT("F20"); break;
		case WXK_F21: key = wxT("F21"); break;
		case WXK_F22: key = wxT("F22"); break;
		case WXK_F23: key = wxT("F23"); break;
		case WXK_F24: key = wxT("F24"); break;
		case WXK_NUMLOCK: key = wxT("NUMLOCK"); break;
		case WXK_SCROLL: key = wxT("SCROLL"); break;
		case WXK_PAGEUP: key = wxT("PAGEUP"); break;
		case WXK_PAGEDOWN: key = wxT("PAGEDOWN"); break;
		case WXK_NUMPAD_SPACE: key = wxT("NUMPAD_SPACE"); break;
		case WXK_NUMPAD_TAB: key = wxT("NUMPAD_TAB"); break;
		case WXK_NUMPAD_ENTER: key = wxT("NUMPAD_ENTER"); break;
		case WXK_NUMPAD_F1: key = wxT("NUMPAD_F1"); break;
		case WXK_NUMPAD_F2: key = wxT("NUMPAD_F2"); break;
		case WXK_NUMPAD_F3: key = wxT("NUMPAD_F3"); break;
		case WXK_NUMPAD_F4: key = wxT("NUMPAD_F4"); break;
		case WXK_NUMPAD_HOME: key = wxT("NUMPAD_HOME"); break;
		case WXK_NUMPAD_LEFT: key = wxT("NUMPAD_LEFT"); break;
		case WXK_NUMPAD_UP: key = wxT("NUMPAD_UP"); break;
		case WXK_NUMPAD_RIGHT: key = wxT("NUMPAD_RIGHT"); break;
		case WXK_NUMPAD_DOWN: key = wxT("NUMPAD_DOWN"); break;
		case WXK_NUMPAD_PAGEUP: key = wxT("NUMPAD_PAGEUP"); break;
		case WXK_NUMPAD_PAGEDOWN: key = wxT("NUMPAD_PAGEDOWN"); break;
		case WXK_NUMPAD_END: key = wxT("NUMPAD_END"); break;
		case WXK_NUMPAD_BEGIN: key = wxT("NUMPAD_BEGIN"); break;
		case WXK_NUMPAD_INSERT: key = wxT("NUMPAD_INSERT"); break;
		case WXK_NUMPAD_DELETE: key = wxT("NUMPAD_DELETE"); break;
		case WXK_NUMPAD_EQUAL: key = wxT("NUMPAD_EQUAL"); break;
		case WXK_NUMPAD_MULTIPLY: key = wxT("NUMPAD_MULTIPLY"); break;
		case WXK_NUMPAD_ADD: key = wxT("NUMPAD_ADD"); break;
		case WXK_NUMPAD_SEPARATOR: key = wxT("NUMPAD_SEPARATOR"); break;
		case WXK_NUMPAD_SUBTRACT: key = wxT("NUMPAD_SUBTRACT"); break;
		case WXK_NUMPAD_DECIMAL: key = wxT("NUMPAD_DECIMAL"); break;
		case WXK_BROWSER_BACK: key = wxT("BROWSER_BACK"); break;
		case WXK_BROWSER_FORWARD: key = wxT("BROWSER_FORWARD"); break;
		case WXK_BROWSER_REFRESH: key = wxT("BROWSER_REFRESH"); break;
		case WXK_BROWSER_STOP: key = wxT("BROWSER_STOP"); break;
		case WXK_BROWSER_SEARCH: key = wxT("BROWSER_SEARCH"); break;
		case WXK_BROWSER_FAVORITES: key = wxT("BROWSER_FAVORITES"); break;
		case WXK_BROWSER_HOME: key = wxT("BROWSER_HOME"); break;
		case WXK_VOLUME_MUTE: key = wxT("VOLUME_MUTE"); break;
		case WXK_VOLUME_DOWN: key = wxT("VOLUME_DOWN"); break;
		case WXK_VOLUME_UP: key = wxT("VOLUME_UP"); break;
		case WXK_MEDIA_NEXT_TRACK: key = wxT("MEDIA_NEXT_TRACK"); break;
		case WXK_MEDIA_PREV_TRACK: key = wxT("MEDIA_PREV_TRACK"); break;
		case WXK_MEDIA_STOP: key = wxT("MEDIA_STOP"); break;
		case WXK_MEDIA_PLAY_PAUSE: key = wxT("MEDIA_PLAY_PAUSE"); break;
		case WXK_LAUNCH_MAIL: key = wxT("LAUNCH_MAIL"); break;
		case WXK_LAUNCH_APP1: key = wxT("LAUNCH_APP1"); break;
		case WXK_LAUNCH_APP2: key = wxT("LAUNCH_APP2"); break;

		default:
		{
			if (keycode < 128 && wxIsprint((int)keycode))
				key.Printf(wxT("'%c'"), (char)keycode);
			else if (keycode > 0 && keycode < 27)
				key.Printf(_("Ctrl-%c"), wxT('A') + keycode - 1);
			else
				key.Printf(wxT("unknown (%ld)"), keycode);
		}
		}
	}

	wxLogMessage(wxT("%s event: %s (flags = %c%c%c%c)"),
		name,
		key.c_str(),
		event.ControlDown() ? wxT('C') : wxT('-'),
		event.AltDown() ? wxT('A') : wxT('-'),
		event.ShiftDown() ? wxT('S') : wxT('-'),
		event.MetaDown() ? wxT('M') : wxT('-'));
}

void MyTreeCtrl::OnTreeKeyDown(wxTreeEvent& event)
{
	LogKeyEvent(wxT("Tree key down "), event.GetKeyEvent());

	event.Skip();
}

void MyTreeCtrl::OnBeginLabelEdit(wxTreeEvent& event)
{
	wxLogMessage(wxT("OnBeginLabelEdit"));

	// for testing, prevent this item's label editing
	wxTreeItemId itemId = event.GetItem();
	if (IsTestItem(itemId))
	{
		wxMessageBox(wxT("You can't edit this item."));

		event.Veto();
	}
	else if (itemId == GetRootItem())
	{
		// test that it is possible to change the text of the item being edited
		SetItemText(itemId, wxT("Editing root item"));
	}
}

void MyTreeCtrl::OnEndLabelEdit(wxTreeEvent& event)
{
	wxLogMessage(wxT("OnEndLabelEdit"));

	// don't allow anything except letters in the labels
	if (!event.GetLabel().IsWord())
	{
		wxMessageBox(wxT("The new label should be a single word."));

		event.Veto();
	}
}

void MyTreeCtrl::OnItemCollapsing(wxTreeEvent& event)
{
	wxLogMessage(wxT("OnItemCollapsing"));

	// for testing, prevent the user from collapsing the first child folder
	wxTreeItemId itemId = event.GetItem();
	if (IsTestItem(itemId))
	{
		wxMessageBox(wxT("You can't collapse this item."));

		event.Veto();
	}
}

void MyTreeCtrl::OnItemActivated(wxTreeEvent& event)
{
	// show some info about this item
	wxTreeItemId itemId = event.GetItem();
	MyTreeItemData *item = (MyTreeItemData *)GetItemData(itemId);

	if (item != NULL)
	{
	}

	wxLogMessage(wxT("OnItemActivated"));
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