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

#include "main.h"
#include "schemeviewer.h"

IMPLEMENT_APP(SchemeViewerApp)

bool SchemeViewerApp::OnInit()
{
	SchemeViewer *schemeviewer = new SchemeViewer(wxT("SchemeViewer - Discrete Level Scheme Viewer for NSTARC"));
	schemeviewer->Show(true);
	
	return true;
}
