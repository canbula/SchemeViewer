CC = g++ `wx-config --cxxflags --libs`
OS := $(shell uname)
ifeq ($(OS), Darwin)
ALLTARGET := SchemeViewer.app
INSTALLTARGET := cp -Rf SchemeViewer.app /Applications/SchemeViewer.app
UNINSTALLTARGET := rm -Rf /Applications/SchemeViewer.app
CLEANTARGET := rm -Rf SchemeViewer.app
else
ALLTARGET := SchemeViewer
INSTALLTARGET := cp -Rf ${CURDIR} /usr/share/SchemeViewer
INSTALLTARGET += ;ln -s /usr/share/SchemeViewer/SchemeViewer /bin/SchemeViewer
INSTALLTARGET += ;ln -s /usr/share/FFT/resource/SchemeViewer.xpm /usr/share/pixmaps/SchemeViewer.xpm
INSTALLTARGET += ;cp -f ${CURDIR}/resource/SchemeViewer.desktop /usr/share/applications/SchemeViewer.desktop
UNINSTALLTARGET := rm -Rf /usr/share/SchemeViewer
UNINSTALLTARGET += ;rm -f /usr/share/applications/SchemeViewer.desktop
UNINSTALLTARGET += ;rm -f /usr/share/pixmaps/SchemeViewer.xpm
UNINSTALLTARGET += ;rm -f /bin/SchemeViewer
CLEANTARGET := rm -f SchemeViewer
endif
all: $(ALLTARGET)
SchemeViewer.app: SchemeViewer
	mkdir SchemeViewer.app
	mkdir SchemeViewer.app/Contents
	mkdir SchemeViewer.app/Contents/MacOS
	mkdir SchemeViewer.app/Contents/Resources
	cp resource/Info.plist SchemeViewer.app/Contents/
	echo -n 'APPL????' > SchemeViewer.app/Contents/PkgInfo
	mv SchemeViewer SchemeViewer.app/Contents/MacOS/SchemeViewer
	cp resource/SchemeViewer.icns SchemeViewer.app/Contents/Resources/
SchemeViewer:
	$(CC) -o SchemeViewer src/main.cpp src/main.h src/schemeviewer.cpp src/schemeviewer.h src/wxlibs.h
install:
	$(INSTALLTARGET)
uninstall:
	$(UNINSTALLTARGET)
clean:
	$(CLEANTARGET)