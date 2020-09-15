#include "pch.h"

/*
struct TownTeleportScroll {
unsigned short opcode = 0x055A;
unsigned char bag;
unsigned char slot;
unsigned char location;
};
*/

/*
struct SendViewAction {
unsigned short opcode = 0x0221;
unsigned int charid;
};
*/

//hook CUser::PacketPC
void __declspec(naked) packet_hook() {
	__asm {
		movzx eax,word ptr[ebp+0x0]
		cmp eax,0x055A // opcode
		je _town
		add eax,-0x501
		jmp packet_retn

		_town:
		//save the packet in memory
		push eax
		push edx
		mov eax,dword ptr[ebp+0x0]
		mov dl,byte ptr[ebp+0x4]
		mov dword ptr[tele_packet],eax
		mov byte ptr[tele_packet+0x4],dl 
		pop edx
		pop eax

		//send the packet back
		push ecx //user = ecx
		push offset tele_packet
		push 0x5
		call send_packet_player

		//error checking
		jmp error_check 

		//author: Cups
		send_packet_player:
		push ebp
		mov ebp,esp

		mov edx,[ebp+0x8]
		mov eax,[ebp+0xC]
		mov edi,[ebp+0x10]

		push ecx
		mov ecx,edi

		push ecx //user
		push edx //length
		push eax //packet
		call SConnectionSend

		pop ecx

		mov esp,ebp
		pop ebp
		retn 0xC
	}
}

//hook CUser::ItemUse
void __declspec(naked) effect_hook() {
	__asm {
		movzx ecx,byte ptr[eax+0x46]
		cmp ecx,0x68 //effect 104
		je _item
		cmp ecx,0x4A
		ja _fail
		jmp effect_retn

		_fail:
		jmp effect_fail

		_teleport:
		mov ecx,[esp+0x18]
		add ecx,0x1388 //delay time
		//save the type and delay
		mov dword ptr[ebp+0x58B4],0x1
		mov dword ptr[ebp+0x58B8],ecx
			
		//send the action view
		mov eax,[ebp+0xDC] //charid
		mov edx,0x0221 //opcode
		push 0x6 //length
		lea ecx,[esp+0x20]
		mov word ptr[esp+0x20],dx
		mov dword ptr[esp+0x22],eax
		push ecx //packet
		xor edx,edx
		mov eax,ebp //user = ebp
		call PSendViewAction

		//consume the item
		mov edx,[esp+0xB5C]
		push 0x0 //move map bool
		mov eax,edi
		push edx //slot
		push eax //bag
		mov ecx,ebp //user = ebp
		call ItemUseNSend
		jmp effect_jump

		//check which item was used
		_item:
		cmp dword ptr[eax],0x18AEE
                je _101102
		cmp dword ptr[eax],0x18AEF
		je _101103
		cmp dword ptr[eax],0x18AF0
		je _101104
		cmp dword ptr[eax],0x18AF1
		je _101105
		cmp dword ptr[eax],0x18AF2
		je _101106
		cmp dword ptr[eax],0x18AF3
		je _101107
		cmp dword ptr[eax],0x18AF4
		je _101108
		cmp dword ptr[eax],0x18AF5
		je _101109
		jmp effect_jump

		/*compare the last packet byte to
		determine the teleport location*/
		_101102:
		cmp byte ptr[tele_packet+0x4],0x0
		je _pantanasa
		jmp effect_jump

		_101103:
		cmp byte ptr[tele_packet+0x4],0x0
		je _theodores
		jmp effect_jump

		_101104:
		cmp byte ptr[tele_packet+0x4],0x0
		je _beika
		cmp byte ptr[tele_packet+0x4],0x1
		je _aelbeageu
		cmp byte ptr[tele_packet+0x4],0x2
		je _keolloseu
		jmp effect_jump

		_101105:
		cmp byte ptr[tele_packet+0x4],0x0
		je _haldeck
		cmp byte ptr[tele_packet+0x4],0x1
		je _arktuis
		cmp byte ptr[tele_packet+0x4],0x2
		je _elaste
		jmp effect_jump

		_101106:
		cmp byte ptr[tele_packet+0x4],0x0
		je _silvaren
		cmp byte ptr[tele_packet+0x4],0x1
		je _whitesand
		cmp byte ptr[tele_packet+0x4],0x2
		je _willieoseu
		jmp effect_jump

		_101107:
		cmp byte ptr[tele_packet+0x4],0x0
		je _suteron
		cmp byte ptr[tele_packet+0x4],0x1
		je _gliter
		cmp byte ptr[tele_packet+0x4],0x2
		je _aridon
		jmp effect_jump

		_101108:
		cmp byte ptr[tele_packet+0x4],0x0
		je _aumeros
		cmp byte ptr[tele_packet+0x4],0x1
		je _aruma
		cmp byte ptr[tele_packet+0x4],0x2
		je _starfumos
		jmp effect_jump

		_101109:
		cmp byte ptr[tele_packet+0x4],0x0
		je _warune
		cmp byte ptr[tele_packet+0x4],0x1
		je _fotamion
		cmp byte ptr[tele_packet+0x4],0x2
		je _meteora
		jmp effect_jump

		//save the teleport map and positions
		_pantanasa:
		mov dword ptr[ebp+0x58BC],0x4B //map
		mov dword ptr[ebp+0x58C0],0x44E62000 //posx
		mov dword ptr[ebp+0x58C4],0x4029999A //posy
		mov dword ptr[ebp+0x58C8],0x44E32000 //posz
		jmp _teleport

		_theodores:
		mov dword ptr[ebp+0x58BC],0x4C
		mov dword ptr[ebp+0x58C0],0x44EA8000
		mov dword ptr[ebp+0x58C4],0x40500000
		mov dword ptr[ebp+0x58C8],0x43280000
		jmp _teleport

		_beika:
		mov dword ptr[ebp+0x58BC],0x1
		mov dword ptr[ebp+0x58C0],0x44114000
		mov dword ptr[ebp+0x58C4],0x429D0000
		mov dword ptr[ebp+0x58C8],0x44DC4000
		jmp _teleport

		_aelbeageu:
		mov dword ptr[ebp+0x58BC],0x1
		mov dword ptr[ebp+0x58C0],0x44BF4000
		mov dword ptr[ebp+0x58C4],0x428BE7F0
		mov dword ptr[ebp+0x58C8],0x44E4C000
		jmp _teleport

		_keolloseu:
		mov dword ptr[ebp+0x58BC],0x1
		mov dword ptr[ebp+0x58C0],0x447A0000
		mov dword ptr[ebp+0x58C4],0x415A8F5C
		mov dword ptr[ebp+0x58C8],0x44420000
		jmp _teleport

		_haldeck:
		mov dword ptr[ebp+0x58BC],0x13
		mov dword ptr[ebp+0x58C0],0x44CAE000
		mov dword ptr[ebp+0x58C4],0x41B26873
		mov dword ptr[ebp+0x58C8],0x44D4A000
		jmp _teleport

		_arktuis:
		mov dword ptr[ebp+0x58BC],0x13
		mov dword ptr[ebp+0x58C0],0x441D8000
		mov dword ptr[ebp+0x58C4],0x41076042
		mov dword ptr[ebp+0x58C8],0x44EB0000
		jmp _teleport

		_elaste:
		mov dword ptr[ebp+0x58BC],0x13
		mov dword ptr[ebp+0x58C0],0x44C76000
		mov dword ptr[ebp+0x58C4],0x4109BE77
		mov dword ptr[ebp+0x58C8],0x447E8000
		jmp _teleport

		_silvaren:
		mov dword ptr[ebp+0x58BC],0x13
		mov dword ptr[ebp+0x58C0],0x44B24000
		mov dword ptr[ebp+0x58C4],0x41EC6666
		mov dword ptr[ebp+0x58C8],0x43520000
		jmp _teleport

		_whitesand:
		mov dword ptr[ebp+0x58BC],0x13
		mov dword ptr[ebp+0x58C0],0x440EC000
		mov dword ptr[ebp+0x58C4],0x413F999A
		mov dword ptr[ebp+0x58C8],0x449E2000
		jmp _teleport

		_willieoseu:
		mov dword ptr[ebp+0x58BC],0x13
		mov dword ptr[ebp+0x58C0],0x449BA000
		mov dword ptr[ebp+0x58C4],0x41540000
		mov dword ptr[ebp+0x58C8],0x441CC000
		jmp _teleport

		_suteron:
		mov dword ptr[ebp+0x58BC],0x2
		mov dword ptr[ebp+0x58C0],0x44DE2000
		mov dword ptr[ebp+0x58C4],0x42FD147B
		mov dword ptr[ebp+0x58C8],0x438A8000
		jmp _teleport

		_gliter:
		mov dword ptr[ebp+0x58BC],0x2
		mov dword ptr[ebp+0x58C0],0x4485C000
		mov dword ptr[ebp+0x58C4],0x4260999A
		mov dword ptr[ebp+0x58C8],0x44830000
		jmp _teleport

		_aridon:
		mov dword ptr[ebp+0x58BC],0x2
		mov dword ptr[ebp+0x58C0],0x43760000
		mov dword ptr[ebp+0x58C4],0x42D86666
		mov dword ptr[ebp+0x58C8],0x434F0000
		jmp _teleport

		_aumeros:
		mov dword ptr[ebp+0x58BC],0x14
		mov dword ptr[ebp+0x58C0],0x44B3E000
		mov dword ptr[ebp+0x58C4],0x3FC1EB85
		mov dword ptr[ebp+0x58C8],0x447B8000
		jmp _teleport

		_aruma:
		mov dword ptr[ebp+0x58BC],0x14
		mov dword ptr[ebp+0x58C0],0x44B2E000
		mov dword ptr[ebp+0x58C4],0x4180BA5E
		mov dword ptr[ebp+0x58C8],0x44C00000
		jmp _teleport

		_starfumos:
		mov dword ptr[ebp+0x58BC],0x14
		mov dword ptr[ebp+0x58C0],0x44144000
		mov dword ptr[ebp+0x58C4],0x412C0000
		mov dword ptr[ebp+0x58C8],0x44856000
		jmp _teleport

		_warune:
		mov dword ptr[ebp+0x58BC],0x14
		mov dword ptr[ebp+0x58C0],0x445EC000
		mov dword ptr[ebp+0x58C4],0x40839DB2
		mov dword ptr[ebp+0x58C8],0x44C32000
		jmp _teleport

		_fotamion:
		mov dword ptr[ebp+0x58BC],0x14
		mov dword ptr[ebp+0x58C0],0x443A8000
		mov dword ptr[ebp+0x58C4],0x4069999A
		mov dword ptr[ebp+0x58C8],0x43F28000
		jmp _teleport

		_meteora:
		mov dword ptr[ebp+0x58BC],0x14
		mov dword ptr[ebp+0x58C0],0x44338000
		mov dword ptr[ebp+0x58C4],0x41C051EC
		mov dword ptr[ebp+0x58C8],0x44E58000
		jmp _teleport
	}
}

//hook CUser::CancelMove
void __declspec(naked) cancel_hook() {
	__asm {
		cmp eax,0x2
		jl _check
		_cancel:
		jmp cancel_retn

		//check if the user canceled
		_check:
		cmp dword ptr[eax+0x58B8],0x0
		jne _cancel
                jmp cancel_fail
	}
}

void TownFunc() {
	Hook((void*)0x4784D2, packet_hook, 9);
	Hook((void*)0x473163, effect_hook, 13);
	Hook((void*)0x49AE61, cancel_hook, 5);
}
