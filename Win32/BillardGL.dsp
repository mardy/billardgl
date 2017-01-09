# Microsoft Developer Studio Project File - Name="BillardGL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=BillardGL - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "BillardGL.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "BillardGL.mak" CFG="BillardGL - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "BillardGL - Win32 Release" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE "BillardGL - Win32 Debug" (basierend auf  "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BillardGL - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".."
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /profile /machine:I386

!ELSEIF  "$(CFG)" == "BillardGL - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /profile /debug /machine:I386

!ENDIF 

# Begin Target

# Name "BillardGL - Win32 Release"
# Name "BillardGL - Win32 Debug"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\Anzeige.cpp
# End Source File
# Begin Source File

SOURCE=..\Beleuchtung.cpp
# End Source File
# Begin Source File

SOURCE=..\Benutzerschnittstelle.cpp
# End Source File
# Begin Source File

SOURCE=..\BillardGL.cpp
# End Source File
# Begin Source File

SOURCE=..\bmp.cpp
# End Source File
# Begin Source File

SOURCE=..\createTexture.cpp
# End Source File
# Begin Source File

SOURCE=..\Einsetzen.cpp
# End Source File
# Begin Source File

SOURCE=..\Handling.cpp
# End Source File
# Begin Source File

SOURCE=..\Kamera.cpp
# End Source File
# Begin Source File

SOURCE=..\KommandoZeilenParameter.cpp
# End Source File
# Begin Source File

SOURCE=..\Kugel.cpp
# End Source File
# Begin Source File

SOURCE=..\kugeltabellen.cpp
# End Source File
# Begin Source File

SOURCE=..\LA.cpp
# End Source File
# Begin Source File

SOURCE=..\LadeScreen.cpp
# End Source File
# Begin Source File

SOURCE=..\Menu.cpp
# End Source File
# Begin Source File

SOURCE=..\Netzwerk.cpp
# End Source File
# Begin Source File

SOURCE=..\Physik.cpp
# End Source File
# Begin Source File

SOURCE=..\SchattenKreis.cpp
# End Source File
# Begin Source File

SOURCE=..\Schiedsrichter.cpp
# End Source File
# Begin Source File

SOURCE=..\Schild.cpp
# End Source File
# Begin Source File

SOURCE=..\SpielfeldAufbau.cpp
# End Source File
# Begin Source File

SOURCE=..\Textfeld.cpp
# End Source File
# Begin Source File

SOURCE=..\Tisch.cpp
# End Source File
# Begin Source File

SOURCE=..\Tischfunktionen.cpp
# End Source File
# Begin Source File

SOURCE=..\viertelLoch.cpp
# End Source File
# Begin Source File

SOURCE=..\Zeit.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\Anzeige.h
# End Source File
# Begin Source File

SOURCE=..\Beleuchtung.h
# End Source File
# Begin Source File

SOURCE=..\Benutzerschnittstelle.h
# End Source File
# Begin Source File

SOURCE=..\BillardGL.h
# End Source File
# Begin Source File

SOURCE=..\bmp.h
# End Source File
# Begin Source File

SOURCE=..\createTexture.h
# End Source File
# Begin Source File

SOURCE=..\Einsetzen.h
# End Source File
# Begin Source File

SOURCE=..\Handling.h
# End Source File
# Begin Source File

SOURCE=..\Kamera.h
# End Source File
# Begin Source File

SOURCE=..\KommandoZeilenParameter.h
# End Source File
# Begin Source File

SOURCE=..\Kugel.h
# End Source File
# Begin Source File

SOURCE=..\kugeltabellen.h
# End Source File
# Begin Source File

SOURCE=..\LA.h
# End Source File
# Begin Source File

SOURCE=..\LadeScreen.h
# End Source File
# Begin Source File

SOURCE=..\Menu.h
# End Source File
# Begin Source File

SOURCE=..\Namen.h
# End Source File
# Begin Source File

SOURCE=..\Netzwerk.h
# End Source File
# Begin Source File

SOURCE=..\Physik.h
# End Source File
# Begin Source File

SOURCE=..\SchattenKreis.h
# End Source File
# Begin Source File

SOURCE=..\Schiedsrichter.h
# End Source File
# Begin Source File

SOURCE=..\Schild.h
# End Source File
# Begin Source File

SOURCE=..\SpielfeldAufbau.h
# End Source File
# Begin Source File

SOURCE=..\sprache.h
# End Source File
# Begin Source File

SOURCE=..\Textfeld.h
# End Source File
# Begin Source File

SOURCE=..\Tisch.h
# End Source File
# Begin Source File

SOURCE=..\Tischfunktionen.h
# End Source File
# Begin Source File

SOURCE=..\viertelLoch.h
# End Source File
# Begin Source File

SOURCE=..\Zeit.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
