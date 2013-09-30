#include "stdafx.h"

int __stdcall IDAP_init ( void )
{
  // Do checks here to ensure your plug-in is being used within
  // an environment it was written for. Return PLUGIN_SKIP if the
  // checks fail, otherwise return PLUGIN_KEEP.
  return ( PLUGIN.flags & PLUGIN_UNL ) ? PLUGIN_OK : PLUGIN_KEEP;
}

void __stdcall IDAP_term ( void )
{
  // Stuff to do when exiting, generally you'd put any sort
  // of clean-up jobs here.
  return;
}

void __stdcall IDAP_run ( int arg );


// There isn't much use for these yet, but I set them anyway.
char IDAP_comment[]   = "ida plug-in template";
char IDAP_help[]    = "ida plug-in template";

// The name of the plug-in displayed in the Edit->Plugins menu. It can
// be overridden in the user's plugins.cfg file.
char IDAP_name[]    = "ida plug-in template";

// The hot-key the user can use to run your plug-in.
char IDAP_hotkey[]  = "Ctrl-Alt-X";

// The all-important exported PLUGIN object
plugin_t PLUGIN =
{
  IDP_INTERFACE_VERSION,  // IDA version plug-in is written for
  PLUGIN_UNL,     // Flags (see below)
  IDAP_init,      // Initialisation function
  IDAP_term,      // Clean-up function
  IDAP_run,       // Main plug-in body
  IDAP_comment,   // Comment unused
  IDAP_help,      // As above unused
  IDAP_name,      // Plug-in name shown in
  IDAP_hotkey     // Hot key to run the plug-in
};

BOOL CALLBACK EnumIdaMainWindow ( HWND hwnd, LPARAM lParam )
{
  WINDOWINFO winInfo;
  DWORD dwIdaProcessId = * ( ( DWORD* ) lParam );
  DWORD dwProcessId;
  GetWindowThreadProcessId ( hwnd, &dwProcessId );
  winInfo.cbSize = sizeof ( WINDOWINFO );
  GetWindowInfo ( hwnd, &winInfo );
  
  if ( dwProcessId == dwIdaProcessId && GetParent ( hwnd ) == NULL
       && winInfo.dwStyle & WS_VISIBLE )
  {
    * ( ( HWND * ) lParam ) = hwnd;
    return FALSE; // stop EnumWindow()
  }
  
  return TRUE;
}

HWND GetIdaMainWindow ( void )
{
  DWORD dwIdaProcessId = GetCurrentProcessId();
  
  if ( !EnumWindows ( EnumIdaMainWindow, ( LPARAM ) &dwIdaProcessId ) )
  {
    return ( HWND ) dwIdaProcessId;
  }
  
  return NULL;
}


HWND GetIdaMainWindow ( void );

int APIENTRY _tWinMain (
  _In_ HINSTANCE hInstance,
  _In_opt_ HINSTANCE hPrevInstance,
  _In_ LPTSTR    lpCmdLine,
  _In_ int       nCmdShow );

static void __stdcall AskUsingForm ( void );

// The plugin can be passed an integer argument from the plugins.cfg
// file. This can be useful when you want the one plug-in to do
// something different depending on the hot-key pressed or menu
// item selected.
void __stdcall IDAP_run ( int arg )
{
  // The "meat" of your plug-in
  msg ( "ida plug-in run!\n" );
  HWND hIdaMainWindow = GetIdaMainWindow();
  
  if ( hIdaMainWindow == NULL )
    return;
    
  switch ( arg )
  {
    case 0:
      _tWinMain ( NULL, ( HINSTANCE ) hIdaMainWindow, ( LPWSTR ) arg, SW_SHOWNORMAL );
      break;
      
    case 1:
      AskUsingForm();
      break;
      
    default:
      break;
  }
}

static const char *dialog1 = //
  "This is the title\n\n"// dialog title
  "<##Radio Buttons##Radio 1:R>\n"
  "<Radio 2:R>>\n"//ushort* number of selected radio
  "<##Radio Buttons##Radio 1:R>\n"
  "<Radio 2:R>>\n"//ushort* number of selected radio
  "<##Check Boxes##Check 1:C>\n"
  "<Check 2:C>>\n"//ushort* bitmask of checks
  "<##Check Boxes##Check 1:C>\n"
  "<Check 2:C>>\n";//ushort* bitmask of checks

static void __stdcall AskUsingForm ( void )
{
  ushort bitMask, bitMask1 = 0;
  ushort btnIndex, bitIndex1;
  int ok = AskUsingForm_c ( dialog1, &btnIndex, &bitIndex1, &bitMask, &bitMask1 );
}

