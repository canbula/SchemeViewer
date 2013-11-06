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
	: wxFrame(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(700,600),wxDEFAULT_FRAME_STYLE & ~ (wxRESIZE_BORDER|wxMAXIMIZE_BOX))
{
	
	for(int i=0;i<140;i++)
	{
		for(int j=0;j<350;j++)
		{
			bestpots[i][j]=0;
		}
	}
	int Z;
	int A;
	int P;
	wxString firstline;
	wxString eachline;
	wxTextFile bestpotsFile(nstarcPath+wxT("lib/bestpots.inp"));
	if(bestpotsFile.Exists())
	{
		bestpotsFile.Open();
		firstline = bestpotsFile.GetFirstLine();
		Z = wxAtoi(firstline.Mid(0,4));A = wxAtoi(firstline.Mid(4,4));P = wxAtoi(firstline.Mid(8,4));
		bestpots[Z][A]=P;
		while(!bestpotsFile.Eof())
		{
			eachline = bestpotsFile.GetNextLine();
			Z = wxAtoi(eachline.Mid(0,4));A = wxAtoi(eachline.Mid(4,4));P = wxAtoi(eachline.Mid(8,4));
			bestpots[Z][A]=P;
		}
		bestpotsFile.Close();
	}
	
	wxImage::AddHandler(new wxPNGHandler);
	wxBitmap firstButton(svPath+wxT("resource/icons/first.png"),wxBITMAP_TYPE_PNG);
	wxBitmap lastButton(svPath+wxT("resource/icons/last.png"),wxBITMAP_TYPE_PNG);
	wxBitmap prevButton(svPath+wxT("resource/icons/prev.png"),wxBITMAP_TYPE_PNG);
	wxBitmap nextButton(svPath+wxT("resource/icons/next.png"),wxBITMAP_TYPE_PNG);
	wxBitmap potHO(svPath+wxT("resource/icons/HO.png"),wxBITMAP_TYPE_PNG);
	wxBitmap potWC(svPath+wxT("resource/icons/WC.png"),wxBITMAP_TYPE_PNG);
	wxBitmap potWS(svPath+wxT("resource/icons/WS.png"),wxBITMAP_TYPE_PNG);
	wxBitmap potHOSEL(svPath+wxT("resource/icons/HOSEL.png"),wxBITMAP_TYPE_PNG);
	wxBitmap potWCSEL(svPath+wxT("resource/icons/WCSEL.png"),wxBITMAP_TYPE_PNG);
	wxBitmap potWSSEL(svPath+wxT("resource/icons/WSSEL.png"),wxBITMAP_TYPE_PNG);
	
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
	isotopenames->Sort();
	isotopename = new wxChoice(topmidpanel,ID_ISOTOPE_SELECTOR,wxPoint(-1,-1),wxSize(-1,-1),*isotopenames);
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
	
	wxPanel *leftouterpanel = new wxPanel(middlepanel,-1);
	wxBoxSizer *leftoutervbox = new wxBoxSizer(wxVERTICAL);
	potHO.SetWidth(20);
	potHO.SetHeight(240);
	imagepotHO = new wxStaticBitmap(leftouterpanel,-1,potHO);
	leftoutervbox->Add(imagepotHO,1,wxEXPAND);
	leftoutervbox->Add(new wxStaticLine(leftouterpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	potWC.SetWidth(20);
	potWC.SetHeight(240);
	imagepotHOWC = new wxStaticBitmap(leftouterpanel,-1,potWC);
	leftoutervbox->Add(imagepotHOWC,1,wxEXPAND);
	leftouterpanel->SetSizer(leftoutervbox);
	leftouterpanel->SetBackgroundColour(wxColour(255,255,255));
	middlehbox->Add(leftouterpanel,0,wxALIGN_LEFT|wxEXPAND);

	wxPanel *leftpanel = new wxPanel(middlepanel,-1);
	wxBoxSizer *leftvbox = new wxBoxSizer(wxVERTICAL);
	wxBitmap imagepot1(nstarcPath+wxT("lvlsch/01/Z011A024.png"),wxBITMAP_TYPE_PNG);
	imagepot1.SetWidth(320);
	imagepot1.SetHeight(240);
	imageholder1 = new wxStaticBitmap(leftpanel,-1,imagepot1);
	leftvbox->Add(imageholder1,1,wxEXPAND);
	leftvbox->Add(new wxStaticLine(leftpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	wxBitmap imagepot2(nstarcPath+wxT("lvlsch/02/Z011A024.png"),wxBITMAP_TYPE_PNG);
	imagepot2.SetWidth(320);
	imagepot2.SetHeight(240);
	imageholder2 = new wxStaticBitmap(leftpanel,-1,imagepot2);
	leftvbox->Add(imageholder2,1,wxEXPAND);
	leftpanel->SetSizer(leftvbox);
	leftpanel->SetBackgroundColour(wxColour(255,255,255));
	middlehbox->Add(leftpanel,1,wxALIGN_LEFT|wxEXPAND);

	middlehbox->Add(new wxStaticLine(middlepanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_VERTICAL),0,wxEXPAND);

	wxPanel *rightpanel = new wxPanel(middlepanel,-1);
	wxBoxSizer *rightvbox = new wxBoxSizer(wxVERTICAL);
	wxBitmap imagepot3(nstarcPath+wxT("lvlsch/03/Z011A024.png"),wxBITMAP_TYPE_PNG);
	imagepot3.SetWidth(320);
	imagepot3.SetHeight(240);
	imageholder3 = new wxStaticBitmap(rightpanel,-1,imagepot3);
	rightvbox->Add(imageholder3,1,wxEXPAND);
	rightvbox->Add(new wxStaticLine(rightpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	wxBitmap imagepot4(nstarcPath+wxT("lvlsch/04/Z011A024.png"),wxBITMAP_TYPE_PNG);
	imagepot4.SetWidth(320);
	imagepot4.SetHeight(240);
	imageholder4 = new wxStaticBitmap(rightpanel,-1,imagepot4);
	rightvbox->Add(imageholder4,1,wxEXPAND);
	rightpanel->SetSizer(rightvbox);
	rightpanel->SetBackgroundColour(wxColour(255,255,255));
	middlehbox->Add(rightpanel,1,wxALIGN_RIGHT|wxEXPAND);
	
	wxPanel *rightouterpanel = new wxPanel(middlepanel,-1);
	wxBoxSizer *rightoutervbox = new wxBoxSizer(wxVERTICAL);
	potWS.SetWidth(20);
	potWS.SetHeight(240);
	imagepotWS = new wxStaticBitmap(rightouterpanel,-1,potWS);
	rightoutervbox->Add(imagepotWS,1,wxEXPAND);
	rightoutervbox->Add(new wxStaticLine(rightouterpanel,-1,wxPoint(-1,-1),wxSize(-1,-1),wxLI_HORIZONTAL),0,wxEXPAND);
	potWC.SetWidth(20);
	potWC.SetHeight(240);
	imagepotWSWC = new wxStaticBitmap(rightouterpanel,-1,potWC);
	rightoutervbox->Add(imagepotWSWC,1,wxEXPAND);
	rightouterpanel->SetSizer(rightoutervbox);
	rightouterpanel->SetBackgroundColour(wxColour(255,255,255));
	middlehbox->Add(rightouterpanel,0,wxALIGN_RIGHT|wxEXPAND);
	
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
	wxImage newimgpot1 = wxImage(320,240);wxImage newimgpot2 = wxImage(320,240);wxImage newimgpot3 = wxImage(320,240);wxImage newimgpot4 = wxImage(320,240);
	newimgpot1.LoadFile(nstarcPath+wxT("lvlsch/01/")+newisotopename+wxT(".png"),wxBITMAP_TYPE_PNG);
	newimgpot2.LoadFile(nstarcPath+wxT("lvlsch/02/")+newisotopename+wxT(".png"),wxBITMAP_TYPE_PNG);
	newimgpot3.LoadFile(nstarcPath+wxT("lvlsch/03/")+newisotopename+wxT(".png"),wxBITMAP_TYPE_PNG);
	newimgpot4.LoadFile(nstarcPath+wxT("lvlsch/04/")+newisotopename+wxT(".png"),wxBITMAP_TYPE_PNG);
	newimgpot1.Rescale(320,240);newimgpot2.Rescale(320,240);newimgpot3.Rescale(320,240);newimgpot4.Rescale(320,240);
	wxBitmap newimagepot1(newimgpot1);
	wxBitmap newimagepot2(newimgpot2);
	wxBitmap newimagepot3(newimgpot3);
	wxBitmap newimagepot4(newimgpot4);
	imageholder1->SetBitmap(newimagepot1);imageholder2->SetBitmap(newimagepot2);imageholder3->SetBitmap(newimagepot3);imageholder4->SetBitmap(newimagepot4);
	wxBitmap newpotHO(svPath+wxT("resource/icons/HO.png"),wxBITMAP_TYPE_PNG);
	wxBitmap newpotHOWC(svPath+wxT("resource/icons/WC.png"),wxBITMAP_TYPE_PNG);
	wxBitmap newpotWS(svPath+wxT("resource/icons/WS.png"),wxBITMAP_TYPE_PNG);
	wxBitmap newpotWSWC(svPath+wxT("resource/icons/WC.png"),wxBITMAP_TYPE_PNG);
	wxBitmap newpotHOSEL(svPath+wxT("resource/icons/HOSEL.png"),wxBITMAP_TYPE_PNG);
	wxBitmap newpotHOWCSEL(svPath+wxT("resource/icons/WCSEL.png"),wxBITMAP_TYPE_PNG);
	wxBitmap newpotWSSEL(svPath+wxT("resource/icons/WSSEL.png"),wxBITMAP_TYPE_PNG);
	wxBitmap newpotWSWCSEL(svPath+wxT("resource/icons/WCSEL.png"),wxBITMAP_TYPE_PNG);
	newpotHO.SetWidth(20);newpotHO.SetHeight(240);
	newpotHOWC.SetWidth(20);newpotHOWC.SetHeight(240);
	newpotWS.SetWidth(20);newpotWS.SetHeight(240);
	newpotWSWC.SetWidth(20);newpotWSWC.SetHeight(240);
	newpotHOSEL.SetWidth(20);newpotHOSEL.SetHeight(240);
	newpotHOWCSEL.SetWidth(20);newpotHOWCSEL.SetHeight(240);
	newpotWSSEL.SetWidth(20);newpotWSSEL.SetHeight(240);
	newpotWSWCSEL.SetWidth(20);newpotWSWCSEL.SetHeight(240);
	imagepotHO->SetBitmap(newpotHO);imagepotHOWC->SetBitmap(newpotHOWC);imagepotWS->SetBitmap(newpotWS);imagepotWSWC->SetBitmap(newpotWSWC);
	int Z = wxAtoi(newisotopename.Mid(1,3));int A = wxAtoi(newisotopename.Mid(5,3));
	if(bestpots[Z][A]==1) imagepotHO->SetBitmap(newpotHOSEL);
	if(bestpots[Z][A]==2) imagepotHOWC->SetBitmap(newpotHOWCSEL);
	if(bestpots[Z][A]==3) imagepotWS->SetBitmap(newpotWSSEL);
	if(bestpots[Z][A]==4) imagepotWSWC->SetBitmap(newpotWSWCSEL);
}
