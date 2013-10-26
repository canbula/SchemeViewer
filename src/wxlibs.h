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

#ifndef _WXLIBS_H
#define _WXLIBS_H

#include <iostream>
#include <algorithm>
#include <wx/wx.h>
#include <wx/aboutdlg.h>
#include <wx/app.h>
#include <wx/arrstr.h>
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/bmpbuttn.h>
#include <wx/busyinfo.h>
#include <wx/calctrl.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/colour.h>
#include <wx/datectrl.h>
#include <wx/datetime.h>
#include <wx/dialog.h>
#include <wx/dir.h>
#include <wx/dnd.h>
#include <wx/event.h>
#include <wx/file.h>
#include <wx/filefn.h>
#include <wx/filename.h>
#include <wx/filepicker.h>
#include <wx/gdicmn.h>
#include <wx/grid.h>
#include <wx/imaglist.h>
#include <wx/listctrl.h>
#include <wx/menu.h>
#include <wx/menuitem.h>
#include <wx/mimetype.h>
#include <wx/notebook.h>
#include <wx/regex.h>
#include <wx/scrolwin.h>
#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/splitter.h>
#include <wx/srchctrl.h>
#include <wx/statbmp.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/stdpaths.h>
#include <wx/stream.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/textfile.h>
#include <wx/tokenzr.h>
#include <wx/toolbar.h>
#include <wx/utils.h>
#include <wx/wxhtml.h>

const wxString svPath = wxGetHomeDir()+wxT("/Codes/SchemeViewer/");
const wxString nstarcPath = wxGetHomeDir()+wxT("/Codes/nstarc/");

#ifdef __APPLE__
const wxString platform = wxT("apple");
#endif

#ifdef __LINUX__
const wxString platform = wxT("linux");
#endif

#endif
