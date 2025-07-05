//**********************************************************************
//  Copyright (c) 2009-2025  Derell Licht
//  about_hlinks - example program - About dialog with hyperlinks
//**********************************************************************

// char const * const VerNum = "V1.07" ;
static char szClassName[] = "about_hlinks" ;

#include <windows.h>

typedef  unsigned int  uint ;

//lint -esym(715, hwnd, private_data, message, wParam, lParam)

#include "version.h"
#include "resource.h"

//*************************************************************************
static HINSTANCE g_hinst = 0;

//  about.cpp
extern BOOL CmdAbout(HWND hwnd);

//*******************************************************************
static bool do_init_dialog(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, LPVOID private_data)
{
   char msgstr[81] ;
   wsprintf(msgstr, "%s %s", szClassName, VerNum) ;
   SetWindowText(hwnd, msgstr) ;

   SendMessage(hwnd, WM_SETICON, ICON_BIG,   (LPARAM) LoadIcon(g_hinst, MAKEINTRESOURCE(IDI_APPICON)));
   SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM) LoadIcon(g_hinst, MAKEINTRESOURCE(IDI_APPICON)));

   return true ;
}

//*******************************************************************
static bool do_command(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, LPVOID private_data)
{
   DWORD cmd = HIWORD (wParam) ;
   DWORD target = LOWORD(wParam) ;
   // putf(&this_term, "WM_COMMAND: cmd=%u, target=%u", cmd, target) ;
   // If a button is clicked...
   if (cmd == BN_CLICKED) {
      switch (target) {
      case IDB_ABOUT:
         CmdAbout(hwnd);
         return true;

      case IDB_CLOSE:
         PostMessageA(hwnd, WM_CLOSE, 0, 0);
         return true;
      }  //lint !e744
   } 
   return false ;
}

//*******************************************************************
static bool do_close(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, LPVOID private_data)
{
   DestroyWindow(hwnd);
   return true ;
}

//*******************************************************************
static bool do_destroy(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, LPVOID private_data)
{
   PostQuitMessage(0);
   return true ;
}

//*******************************************************************
typedef struct winproc_table_s {
   uint win_code ;
   bool (*winproc_func)(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, LPVOID private_data) ;
} winproc_table_t ;

static winproc_table_t const winproc_table[] = {
{ WM_INITDIALOG,     do_init_dialog },
{ WM_COMMAND,        do_command },
{ WM_CLOSE,          do_close },
{ WM_DESTROY,        do_destroy },

{ 0, NULL } } ;

//*******************************************************************
static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   uint idx ;
   for (idx=0; winproc_table[idx].win_code != 0; idx++) {
      if (winproc_table[idx].win_code == message) {
         return (*winproc_table[idx].winproc_func)(hwnd, message, wParam, lParam, NULL) ;
      }
   }
   return false;
}  //lint !e715

//*********************************************************************
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
   LPSTR lpszArgument, int nFunsterStil)
{
   g_hinst = hInstance;
   //  create the main application
   HWND hwnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAIN_DIALOG), NULL, (DLGPROC) WndProc);
   if (hwnd == NULL) {
      // Notified your about the failure
      // syslog("CreateDialog (main): %s [%u]\n", get_system_message(), GetLastError()) ;
      // Set the return value
      return FALSE;
   }
   ShowWindow (hwnd, SW_SHOW) ;
   UpdateWindow(hwnd);

   MSG msg ;
   while (GetMessage (&msg, NULL, 0, 0)) {
      if (!IsDialogMessage(hwnd, &msg)) {
         TranslateMessage (&msg) ;
         DispatchMessage (&msg) ;
      }
   }
   return (int) msg.wParam ;
}  //lint !e715

