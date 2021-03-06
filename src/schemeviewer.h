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

#include "wxlibs.h"

class SchemeViewer : public wxFrame
{
public:
	SchemeViewer(const wxString& title);
	
	enum
	{
		ID_ISOTOPE_SELECTOR = wxID_HIGHEST + 1,
		ID_NAVIGATOR_FIRST,
		ID_NAVIGATOR_LAST,
		ID_NAVIGATOR_PREV,
		ID_NAVIGATOR_NEXT,
		ID_MENU_FIRST,
		ID_MENU_LAST,
		ID_MENU_PREV,
		ID_MENU_NEXT
	};
	
	int bestpots[140][350];
	wxArrayString *isotopenames;
	wxChoice *isotopename;
	wxStaticBitmap *imageholder1;
	wxStaticBitmap *imageholder2;
	wxStaticBitmap *imageholder3;
	wxStaticBitmap *imageholder4;
	wxStaticBitmap *imagepotHO;
	wxStaticBitmap *imagepotHOWC;
	wxStaticBitmap *imagepotWS;
	wxStaticBitmap *imagepotWSWC;

	void OnQuit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void IsotopeChanger(wxCommandEvent& event);
	void FirstIsotope(wxCommandEvent& event);
	void LastIsotope(wxCommandEvent& event);
	void PrevIsotope(wxCommandEvent& event);
	void NextIsotope(wxCommandEvent& event);
	void ChangeIsotope();

};
