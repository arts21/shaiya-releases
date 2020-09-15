#ifndef PCH_H
#define PCH_H

#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
//main function
void CMDFunc();
//hook function
BOOL Hook(void * pAddr, void * pNAddr, int len = 5);
//command variables
DWORD cmd_input = 0x632D07;
DWORD cmd_retn = 0x4867A6;
DWORD cmd_jmp = 0x487532;
DWORD sysmsg_uni = 0x423150;
LPCSTR szClose = "/close";
LPCSTR szMarket = "/merchant";
LPCSTR szKeeper = "/warehouse";
LPCSTR szRepair = "/blacksmith";
LPCSTR szReroll = "/recreation";
unsigned char npc_jmp[] = { 0xEB, 0x05 };
unsigned char max_sell[] = { 0x90, 0x90 };
unsigned char help_menu[] = { 0xE8, 0x0B, 0x9F, 0xFF, 0xFF };

#endif
