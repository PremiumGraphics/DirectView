#include "stdafx.h"

namespace FileTest{

	class Frame : public wxFrame//wxMDIParentFrame
	{
	public:
		Frame();

		void OnFileOpen(wxRibbonButtonBarEvent& e);

		void OnFileSave(wxRibbonButtonBarEvent&);

		void OnFileSaveAs(wxRibbonButtonBarEvent& e);

		void OnImport(wxRibbonButtonBarEvent& e);

		void OnExport(wxRibbonButtonBarEvent& e);

		void OnNew(wxRibbonButtonBarEvent&);

		void OnClose(wxRibbonButtonBarEvent&);

		void OnAbout(wxRibbonButtonBarEvent&);

	};

}