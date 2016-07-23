#ifndef _GUI_NODESTREE_H_
#define _GUI_NODESTREE_H_
#include <memory>
#include <vector>
#include <wx/treectrl.h>
#include <wx/imaglist.h>
#include "../NodesProvider.h"
#include "GraphView.h"
#include "../GraphEngine.h"

class MyTreeItemData : public wxTreeItemData
{
public:
	MyTreeItemData(const std::shared_ptr<ModelNode> model) : m_model(model) { }

	std::shared_ptr<ModelNode> const Get() const { return m_model; }

private:
	std::shared_ptr<ModelNode> m_model;
};

class MyTreeCtrl : public wxTreeCtrl
{
public:
	enum
	{
		TreeCtrlIcon_File,
		TreeCtrlIcon_FileSelected,
		TreeCtrlIcon_Folder,
		TreeCtrlIcon_FolderSelected,
		TreeCtrlIcon_FolderOpened
	};

	MyTreeCtrl() {}
	MyTreeCtrl(wxWindow *parent, std::shared_ptr<NodesProvider> nodesProvider, GraphView* graphView);
	virtual ~MyTreeCtrl() {};

	void OnBeginDrag(wxTreeEvent& event);
	void OnBeginRDrag(wxTreeEvent& event);
	void OnEndDrag(wxTreeEvent& event);
	void OnDeleteItem(wxTreeEvent& event);
	void OnContextMenu(wxContextMenuEvent& event);
	void OnItemMenu(wxTreeEvent& event);
	void OnGetInfo(wxTreeEvent& event);
	void OnSetInfo(wxTreeEvent& event);
	void OnItemExpanded(wxTreeEvent& event);
	void OnItemExpanding(wxTreeEvent& event);
	void OnItemCollapsed(wxTreeEvent& event);
	void OnSelChanged(wxTreeEvent& event);
	void OnSelChanging(wxTreeEvent& event);
	void OnTreeKeyDown(wxTreeEvent& event);
	void OnItemActivated(wxTreeEvent& event);
	void OnItemRClick(wxTreeEvent& event);


	void CreateImageList(int size = 16);

	void DoSortChildren(const wxTreeItemId& item)
	{
		wxTreeCtrl::SortChildren(item);
	}

	void DoToggleIcon(const wxTreeItemId& item);

	void ShowMenu(wxTreeItemId id, const wxPoint& pt);

	int ImageSize(void) const { return m_imageSize; }

protected:
	virtual int OnCompareItems(const wxTreeItemId& i1, const wxTreeItemId& i2) wxOVERRIDE;

private:
	// Find the very last item in the tree.
	void AddItemsRecursively(const wxTreeItemId& idParent, std::vector<std::shared_ptr<ModelNode>> nodes);

	int          m_imageSize;               // current size of images
	
	std::shared_ptr<NodesProvider> m_nodesProvider;
	GraphView* m_graphView;

	wxDECLARE_DYNAMIC_CLASS(MyTreeCtrl);
};

// menu and control ids
enum
{
	TreeTest_Quit = wxID_EXIT,
	TreeTest_About = wxID_ABOUT,
	TreeTest_ClearLog = wxID_CLEAR,
	TreeTest_TogButtons = wxID_HIGHEST,
	TreeTest_TogTwist,
	TreeTest_TogLines,
	TreeTest_TogEdit,
	TreeTest_TogHideRoot,
	TreeTest_TogRootLines,
	TreeTest_TogBorder,
	TreeTest_TogFullHighlight,
	TreeTest_SetFgColour,
	TreeTest_SetBgColour,
	TreeTest_ResetStyle,
	TreeTest_Highlight,
	TreeTest_Dump,
	TreeTest_DumpSelected,
	TreeTest_Count,
	TreeTest_CountRec,
	TreeTest_Sort,
	TreeTest_SortRev,
	TreeTest_SetBold,
	TreeTest_ClearBold,
	TreeTest_Rename,
	TreeTest_Delete,
	TreeTest_DeleteChildren,
	TreeTest_DeleteAll,
	TreeTest_Recreate,
	TreeTest_ToggleImages,
	TreeTest_ToggleStates,
	TreeTest_ToggleBell,
	TreeTest_ToggleAlternateImages,
	TreeTest_ToggleAlternateStates,
	TreeTest_ToggleButtons,
	TreeTest_SetImageSize,
	TreeTest_ToggleSel,
	TreeTest_CollapseAndReset,
	TreeTest_EnsureVisible,
	TreeTest_SetFocus,
	TreeTest_AddItem,
	TreeTest_AddManyItems,
	TreeTest_InsertItem,
	TreeTest_IncIndent,
	TreeTest_DecIndent,
	TreeTest_IncSpacing,
	TreeTest_DecSpacing,
	TreeTest_ToggleIcon,
	TreeTest_ToggleState,
	TreeTest_Select,
	TreeTest_Unselect,
	TreeTest_SelectRoot,
	TreeTest_ClearFocused,
	TreeTest_SetFocusedRoot,
	TreeTest_SelectChildren,
	TreeTest_ShowFirstVisible,
	TreeTest_ShowLastVisible,
	TreeTest_ShowNextVisible,
	TreeTest_ShowPrevVisible,
	TreeTest_ShowParent,
	TreeTest_ShowPrevSibling,
	TreeTest_ShowNextSibling,
	TreeTest_ScrollTo,
	TreeTest_SelectLast,
	TreeTest_Ctrl = 1000
};


#endif