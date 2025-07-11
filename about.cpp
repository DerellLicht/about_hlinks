/*-----------------------------------------------------------------------------

    This is a part of the Microsoft Source Code Samples. 
    Copyright (C) 1995 Microsoft Corporation.
    All rights reserved. 
    MODULE:   About.c

    PURPOSE:  Implement the About dialog box for the program.
-----------------------------------------------------------------------------*/

#include <windows.h>

#include "resource.h"
#include "version.h"
#include "hyperlinks.h"

//-----------------------------------------------------------------------------
//static BOOL CALLBACK AboutDlgProc(HWND hdlg, UINT uMessage, WPARAM wparam, LPARAM lparam)
static INT_PTR CALLBACK AboutDlgProc(HWND hdlg, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
   switch(uMessage) {
   case WM_INITDIALOG:
      SetWindowText(GetDlgItem(hdlg, IDC_VERNUM), VerNum) ;
      ConvertStaticToHyperlink(hdlg, IDC_WEBLINK);
      ConvertStaticToHyperlink(hdlg, IDC_WEBLINK2);
      break;

   case WM_COMMAND:
      switch (LOWORD(wparam)) {
      case IDC_WEBLINK:
         ShellExecute(hdlg, "open", "http://derelllicht.42web.io/freeware.html", "", "", SW_SHOW);
         return TRUE;
         
      case IDC_WEBLINK2:
         ShellExecute(hdlg, "open", "https://github.com/DerellLicht/about_hlinks", "", "", SW_SHOW);
         return TRUE;
         
      case IDOK:
      case IDCANCEL:
         EndDialog(hdlg, TRUE);
         return TRUE;
      }  //lint !e744  switch with no default
      break;
   }  //lint !e744  switch with no default

   return FALSE;
}  //lint !e715

/*-----------------------------------------------------------------------------
FUNCTION: CmdAbout( HWND )
PARAMETERS:
    hwnd - Owner of the window
PURPOSE: Creates the modal About dialog
-----------------------------------------------------------------------------*/
BOOL CmdAbout(HWND hwnd)
{
    DialogBox((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_ABOUT), 0, AboutDlgProc);
    return 0;
}  //lint !e715 !e818  hwnd
