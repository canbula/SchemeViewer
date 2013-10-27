/*
    This file is part of SchemeViewer.

    SchemeViewer is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SchemeViewer is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SchemeViewer.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "schemeviewer.h"

SchemeViewer::SchemeViewer(const wxString& title)
	: wxFrame(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(700,700),wxDEFAULT_FRAME_STYLE & ~ (wxRESIZE_BORDER|wxMAXIMIZE_BOX))
{
	
	wxImage::AddHandler(new wxPNGHandler);
	wxBitmap firstButton(svPath+wxT("resource/icons/first.png"),wxBITMAP_TYPE_PNG);
	wxBitmap lastButton(svPath+wxT("resource/icons/last.png"),wxBITMAP_TYPE_PNG);
	wxBitmap prevButton(svPath+wxT("resource/icons/prev.png"),wxBITMAP_TYPE_PNG);
	wxBitmap nextButton(svPath+wxT("resource/icons/next.png"),wxBITMAP_TYPE_PNG);
	
	wxMenuBar *menubar = new wxMenuBar;
	wxMenu *file = new wxMenu;
	file->Append(ID_MENU_FIRST,wxT("First Isotope\tCtrl+1"));
	file->Append(ID_MENU_PREV,wxT("Previous Isotope\tCtrl+2"));
	file->Append(ID_MENU_NEXT,wxT("Next Isotope\tCtrl+3"));
	file->Append(ID_MENU_LAST,wxT("Last Isotope\tCtrl+4"));
	file->AppendSeparator();
	file->Append(wxID_ABOUT,wxT("About\tCtrl+H"));
	file->Append(wxID_EXIT,wxT("Close\tCtrl+Q"));
	menubar->Append(file,wxT("Menu"));
	SetMenuBar(menubar);
	
	wxStatusBar *statusbar = new wxStatusBar(this,wxID_ANY,wxST_SIZEGRIP);
	this->SetStatusBar(statusbar);
	statusbar->SetStatusText(wxT("SchemeViewer - Discrete Level Scheme Viewer for NSTARC - Bora CANBULA - 2013"));
	
	wxPanel *outerpanel = new wxPanel(this,-1);
	wxBoxSizer *outerbox = new wxBoxSizer(wxHORIZONTAL);
	
	outerbox->Add(new wxStaticText(outerpanel,-1,wxT(" ")),0,wxEXPAND);

	wxPanel *mainpanel = new wxPanel(outerpanel,-1);
	wxBoxSizer *mainvbox = new wxBoxSizer(wxVERTICAL);
	
	mainvbox->Add(-1,5);
	
	wxPanel *toppanel = new wxPanel(mainpanel,-1);
	wxBoxSizer *topbox = new wxBoxSizer(wxHORIZONTAL);
	topbox->Add(new wxStaticText(toppanel,-1,wxT("")),1,wxEXPAND);
	topbox->Add(new wxBitmapButton(toppanel,ID_NAVIGATOR_FIRST,firstButton),0,wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER);
	topbox->Add(new wxBitmapButton(toppanel,ID_NAVIGATOR_PREV,prevButton),0,wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER);
	topbox->Add(new wxStaticText(toppanel,-1,wxT(" ")),0,wxEXPAND);
	wxPanel *topmidpanel = new wxPanel(toppanel,-1);
	wxBoxSizer *topmidbox = new wxBoxSizer(wxVERTICAL);
	wxPanel *topmidpanel1 = new wxPanel(topmidpanel,-1);
	wxBoxSizer *topmidbox1 = new wxBoxSizer(wxHORIZONTAL);
	topmidbox1->Add(new wxStaticText(topmidpanel1,-1,wxT("")),1,wxEXPAND);
	topmidbox1->Add(new wxStaticText(topmidpanel1,-1,wxT("SELECT ISOTOPE"),wxPoint(-1,-1),wxSize(-1,-1)),0,wxALIGN_CENTER|wxEXPAND);
	topmidbox1->Add(new wxStaticText(topmidpanel1,-1,wxT("")),1,wxEXPAND);
	topmidpanel1->SetSizer(topmidbox1);
	topmidbox->Add(topmidpanel1,1,wxALIGN_CENTER|wxEXPAND);
	isotopenames = new wxArrayString();
	wxDir lvlschdir(nstarcPath+wxT("lvlsch/01/"));
	wxString lvlschfilename;
	bool cont = lvlschdir.GetFirst(&lvlschfilename,wxT("*.png"));
	while (cont)
	{
		isotopenames->Add(lvlschfilename.Mid(0,8));
		cont = lvlschdir.GetNext(&lvlschfilename);
	}
	isotopename = new wxChoice(topmidpanel,ID_ISOTOPE_SELECTOR,wxPoint(-1,-1),wxSize(-1,-1),*isotopenames);
	isotopename->SetStringSelection(wxT("Z003A011"));
	topmidbox->Add(isotopename,1,wxALIGN_CENTER|wxEXPAND);
	topmidpanel->SetSizer(topmidbox);
	topbox->Add(topmidpanel,1,wxALIGN_CENTER|wxEXPAND);
	topbox->Add(new wxStaticText(toppanel,-1,wxT(" ")),0,wxEXPAND);
	topbox->Add(new wxBitmapButton(toppanel,ID_NAVIGATOR_NEXT,nextButton),0,wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER);
	topbox->Add(new wxBitmapButton(toppanel,ID_NAVIGATOR_LAST,lastButton),0,wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER);
	topbox->Add(new wxStaticText(toppanel,-1,wxT("")),1,wxEXPAND);
	toppanel->SetSizer(topbox);
	mainvbox->Add(toppanel,0,wxALIGN_CENTER|wxEXPAND);
	
	mainvbox->Add(-1,5);
	mainvbox->Add(new wxStaticLine(mainpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	
	wxPanel *middlepanel = new wxPanel(mainpanel,-1);
	wxBoxSizer *middlehbox = new wxBoxSizer(wxHORIZONTAL);
	
	middlehbox->Add(new wxStaticLine(middlepanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_VERTICAL),0,wxEXPAND);

	wxPanel *leftpanel = new wxPanel(middlepanel,-1);
	wxBoxSizer *leftvbox = new wxBoxSizer(wxVERTICAL);
	wxScrolledWindow *leftscwin1 = new wxScrolledWindow(leftpanel,-1);
	wxBitmap imagepot1(nstarcPath+wxT("lvlsch/01/Z011A024.png"),wxBITMAP_TYPE_PNG);
	imagepot1.SetWidth(320);
	imagepot1.SetHeight(240);
	imageholder1 = new wxStaticBitmap(leftscwin1, -1, imagepot1);
	leftscwin1->SetScrollbars(0, 10, 0, 24);
	leftscwin1->SetBackgroundColour(wxColour(255,255,255));
	leftvbox->Add(leftscwin1,1,wxEXPAND);
	leftvbox->Add(new wxStaticLine(leftpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	wxScrolledWindow *leftscwin2 = new wxScrolledWindow(leftpanel,-1);
	wxBitmap imagepot2(nstarcPath+wxT("lvlsch/02/Z011A024.png"),wxBITMAP_TYPE_PNG);
	imagepot2.SetWidth(320);
	imagepot2.SetHeight(240);
	imageholder2 = new wxStaticBitmap(leftscwin2, -1, imagepot2);
	leftscwin2->SetScrollbars(0, 10, 0, 24);
	leftscwin2->SetBackgroundColour(wxColour(255,255,255));
	leftvbox->Add(leftscwin2,1,wxEXPAND);
	leftpanel->SetSizer(leftvbox);
	middlehbox->Add(leftpanel,1,wxALIGN_LEFT|wxEXPAND);

	middlehbox->Add(new wxStaticLine(middlepanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_VERTICAL),0,wxEXPAND);

	wxPanel *rightpanel = new wxPanel(middlepanel,-1);
	wxBoxSizer *rightvbox = new wxBoxSizer(wxVERTICAL);
	wxScrolledWindow *rightscwin1 = new wxScrolledWindow(rightpanel,-1);
	wxBitmap imagepot3(nstarcPath+wxT("lvlsch/03/Z011A024.png"),wxBITMAP_TYPE_PNG);
	imagepot3.SetWidth(320);
	imagepot3.SetHeight(240);
	imageholder3 = new wxStaticBitmap(rightscwin1, -1, imagepot3);
	rightscwin1->SetScrollbars(0, 10, 0, 24);
	rightscwin1->SetBackgroundColour(wxColour(255,255,255));
	rightvbox->Add(rightscwin1,1,wxEXPAND);
	rightvbox->Add(new wxStaticLine(rightpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	wxScrolledWindow *rightscwin2 = new wxScrolledWindow(rightpanel,-1);
	wxBitmap imagepot4(nstarcPath+wxT("lvlsch/04/Z011A024.png"),wxBITMAP_TYPE_PNG);
	imagepot4.SetWidth(320);
	imagepot4.SetHeight(240);
	imageholder4 = new wxStaticBitmap(rightscwin2, -1, imagepot4);
	rightscwin2->SetScrollbars(0, 10, 0, 24);
	rightscwin2->SetBackgroundColour(wxColour(255,255,255));
	rightvbox->Add(rightscwin2,1,wxEXPAND);
	rightpanel->SetSizer(rightvbox);
	middlehbox->Add(rightpanel,1,wxALIGN_RIGHT|wxEXPAND);
	
	middlehbox->Add(new wxStaticLine(middlepanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_VERTICAL),0,wxEXPAND);

	middlepanel->SetSizer(middlehbox);
	
	mainvbox->Add(middlepanel,1,wxEXPAND);
	
	mainpanel->SetSizer(mainvbox);
	
	outerbox->Add(mainpanel,1,wxALIGN_CENTER|wxEXPAND);
	
	outerbox->Add(new wxStaticText(outerpanel,-1,wxT(" ")),0,wxEXPAND);
	outerpanel->SetSizer(outerbox);
	
	Connect(wxID_ABOUT,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(SchemeViewer::OnAbout));
	Connect(wxID_EXIT,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(SchemeViewer::OnQuit));
	Connect(ID_ISOTOPE_SELECTOR,wxEVT_COMMAND_CHOICE_SELECTED,wxCommandEventHandler(SchemeViewer::IsotopeChanger));
	Connect(ID_NAVIGATOR_FIRST,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(SchemeViewer::FirstIsotope));
	Connect(ID_NAVIGATOR_LAST,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(SchemeViewer::LastIsotope));
	Connect(ID_NAVIGATOR_PREV,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(SchemeViewer::PrevIsotope));
	Connect(ID_NAVIGATOR_NEXT,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(SchemeViewer::NextIsotope));
	Connect(ID_MENU_FIRST,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(SchemeViewer::FirstIsotope));
	Connect(ID_MENU_LAST,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(SchemeViewer::LastIsotope));
	Connect(ID_MENU_PREV,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(SchemeViewer::PrevIsotope));
	Connect(ID_MENU_NEXT,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(SchemeViewer::NextIsotope));
	
	SetIcon(wxIcon(wxT("resource/SchemeViewer.xpm")));
	Centre();
	
	SchemeViewer::ChangeIsotope();
	
}

void SchemeViewer::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxAboutDialogInfo info;
	info.SetName(wxT("SchemeViewer"));
	info.SetVersion(wxT("0.1"));
	info.SetDescription(wxT("Discrete Level Scheme Viewer for NSTARC"));
	info.SetCopyright(wxT("Bora CANBULA <bc.jabba@gmail.com> (C) 2013"));
	wxAboutBox(info);
}

void SchemeViewer::OnQuit(wxCommandEvent& WXUNUSED(event)) {Close(true);}

void SchemeViewer::IsotopeChanger(wxCommandEvent& WXUNUSED(event))
{
	SchemeViewer::ChangeIsotope();
}

void SchemeViewer::FirstIsotope(wxCommandEvent& WXUNUSED(event))
{
	isotopename->SetSelection(0);
	SchemeViewer::ChangeIsotope();
}

void SchemeViewer::LastIsotope(wxCommandEvent& WXUNUSED(event))
{
	int totalisotopes = isotopename->GetCount()-1;
	isotopename->SetSelection(totalisotopes);
	SchemeViewer::ChangeIsotope();
}

void SchemeViewer::PrevIsotope(wxCommandEvent& WXUNUSED(event))
{
	isotopename->SetSelection(std::max(isotopename->GetSelection()-1,0));
	SchemeViewer::ChangeIsotope();
}

void SchemeViewer::NextIsotope(wxCommandEvent& WXUNUSED(event))
{
	int totalisotopes = isotopename->GetCount()-1;
	isotopename->SetSelection(std::min(isotopename->GetSelection()+1,totalisotopes));
	SchemeViewer::ChangeIsotope();
}

void SchemeViewer::ChangeIsotope()
{
	wxString newisotopename = isotopename->GetString(isotopename->GetSelection());
	wxBitmap newimagepot1(nstarcPath+wxT("lvlsch/01/")+newisotopename+wxT(".png"),wxBITMAP_TYPE_PNG);
	wxBitmap newimagepot2(nstarcPath+wxT("lvlsch/02/")+newisotopename+wxT(".png"),wxBITMAP_TYPE_PNG);
	wxBitmap newimagepot3(nstarcPath+wxT("lvlsch/03/")+newisotopename+wxT(".png"),wxBITMAP_TYPE_PNG);
	wxBitmap newimagepot4(nstarcPath+wxT("lvlsch/04/")+newisotopename+wxT(".png"),wxBITMAP_TYPE_PNG);
	newimagepot1.SetWidth(320);
	newimagepot1.SetHeight(240);
	newimagepot2.SetWidth(320);
	newimagepot2.SetHeight(240);
	newimagepot3.SetWidth(320);
	newimagepot3.SetHeight(240);
	newimagepot4.SetWidth(320);
	newimagepot4.SetHeight(240);
	imageholder1->SetBitmap(newimagepot1);
	imageholder2->SetBitmap(newimagepot2);
	imageholder3->SetBitmap(newimagepot3);
	imageholder4->SetBitmap(newimagepot4);
}
