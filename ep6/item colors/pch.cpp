#include "pch.h"

//finds fire items
//param  = item id array
bool fire_res(int val) {
	auto res = std::find(std::begin(fire_arr), std::end(fire_arr), val);
	if (res != std::end(fire_arr)) {
		return true;
	}
	else {
		return false;
	}
}

//finds water items
//param  = item id array
bool water_res(int val) {
	auto res = std::find(std::begin(water_arr), std::end(water_arr), val);
	if (res != std::end(water_arr)) {
		return true;
	}
	else {
		return false;
	}
}

//finds earth items
//param  = item id array
bool earth_res(int val) {
	auto res = std::find(std::begin(earth_arr), std::end(earth_arr), val);
	if (res != std::end(earth_arr)) {
		return true;
	}
	else {
		return false;
	}
}

//finds wind items
//param  = item id array
bool wind_res(int val) {
	auto res = std::find(std::begin(wind_arr), std::end(wind_arr), val);
	if (res != std::end(wind_arr)) {
		return true;
	}
	else {
		return false;
	}
}

//asm hook for bag items
void __declspec(naked) bag_hook() {
	__asm {
		pushad
		//move all the types into ecx
		movzx ecx,byte ptr[eax+0x90E2F9]
		//multiply the types by 1000
		imul ecx,0x3E8
		//move all the type ids into edx
		movzx edx,byte ptr[eax+0x90E2FA]
		//add the type ids to the types
		add ecx,edx
		//store the item ids in an array
		mov[eax+bag_arr],ecx
		//save the item id array in ebx
		mov ebx,[eax+bag_arr]
		push ebx
		call fire_res
		add esp,0x4
		test al,al
		jne _fire
		push ebx
		call water_res
		add esp,0x4
		test al,al
		jne _water
		push ebx
		call earth_res
		add esp,0x4
		test al,al
		jne _earth
		push ebx
		call wind_res
		add esp,0x4
		test al,al
		jne _wind
		popad
		//original code
		mov edx,dword ptr ss:[esp+0x1C]
		mov eax,dword ptr ss:[esp+0x10]
		jmp bag_retn

		_fire: //red
		popad
		mov edx,dword ptr ss:[esp+0x1C]
		mov eax,dword ptr ss:[esp+0x10]
		push 0x1
		push 0x0
		push edx
		push ebx
		push edi
		push eax
		push ebp
		push ecx
		lea ecx,dword ptr ds:[esi+0x30]
		call icon_render
		mov ecx,dword ptr ss:[esp+0x10]
		push 0x20 //icon size
		push 0x20 //icon size
		push ecx //position
		push ebp //position
		push 0x50FF0000 //overlay color
		call over_render
		add esp,0x14
		jmp bag_jump

		_water: //blue
		popad
		mov edx,dword ptr ss:[esp+0x1C]
		mov eax,dword ptr ss:[esp+0x10]
		push 0x1
		push 0x0
		push edx
		push ebx
		push edi
		push eax
		push ebp
		push ecx
		lea ecx,dword ptr ds:[esi+0x30]
		call icon_render
		mov ecx,dword ptr ss:[esp+0x10]
		push 0x20
		push 0x20
		push ecx
		push ebp
		push 0x5000FFFF
		call over_render
		add esp,0x14
		jmp bag_jump

		_earth: //green
		popad
		mov edx,dword ptr ss:[esp+0x1C]
		mov eax,dword ptr ss:[esp+0x10]
		push 0x1
		push 0x0
		push edx
		push ebx
		push edi
		push eax
		push ebp
		push ecx
		lea ecx,dword ptr ds:[esi+0x30]
		call icon_render
		mov ecx,dword ptr ss:[esp+0x10]
		push 0x20
		push 0x20
		push ecx
		push ebp
		push 0x5000FF00
		call over_render
		add esp,0x14
		jmp bag_jump

		_wind: //white
		popad
		mov edx,dword ptr ss:[esp+0x1C]
		mov eax,dword ptr ss:[esp+0x10]
		push 0x1
		push 0x0
		push edx
		push ebx
		push edi
		push eax
		push ebp
		push ecx
		lea ecx,dword ptr ds:[esi+0x30]
		call icon_render
		mov ecx,dword ptr ss:[esp+0x10]
		push 0x20
		push 0x20
		push ecx
		push ebp
		push 0x50FFFFFF
		call over_render
		add esp,0x14
		jmp bag_jump
	}
}

//asm hook for skill bar items
void __declspec(naked) bar_hook() {
	__asm {
		pushad
		//move all the types into ecx
		movzx ecx,byte ptr[esi+0x90E2F9]
		//multiply the types by 1000
		imul ecx,0x3E8
		//move all the type ids into edx
		movzx edx,byte ptr[esi+0x90E2FA]
		//add the type ids to the types
		add ecx,edx
		//store the item ids in an array
		mov[esi+bar_arr],ecx
		//save the item id array in ebx
		mov ebx,[esi+bar_arr]
		push ebx
		call fire_res
		add esp,0x4
		test al,al
		jne _fire
		push ebx
		call water_res
		add esp,0x4
		test al,al
		jne _water
		push ebx
		call earth_res
		add esp,0x4
		test al,al
		jne _earth
		push ebx
		call wind_res
		add esp,0x4
		test al,al
		jne _wind
		popad
		//original code
		push 0x1
		push 0x0
		push eax
		jmp bar_retn

		_fire: //red
		popad
		push 0x1
		push 0x0
		push eax
		push ebx
		push ebp
		push ecx
		mov ecx,dword ptr ss:[esp+0x28]
		push edx
		push -0x1
		call icon_render
		//move the positions
		mov eax,dword ptr ss:[esp+0x18]
		mov ecx,dword ptr ss:[esp+0x1C]
		push 0x20 //icon size
		push 0x20 //icon size
		push eax //position
		push ecx //position
		push 0x50FF0000 //overlay color
		call over_render
		add esp,0x14
		jmp bar_jump

		_water: //blue
		popad
		push 0x1
		push 0x0
		push eax
		push ebx
		push ebp
		push ecx
		mov ecx,dword ptr ss:[esp+0x28]
		push edx
		push -0x1
		call icon_render
		mov eax,dword ptr ss:[esp+0x18]
		mov ecx,dword ptr ss:[esp+0x1C]
		push 0x20
		push 0x20
		push eax
		push ecx
		push 0x5000FFFF
		call over_render
		add esp,0x14
		jmp bar_jump

		_earth: //green
		popad
		push 0x1
		push 0x0
		push eax
		push ebx
		push ebp
		push ecx
		mov ecx,dword ptr ss:[esp+0x28]
		push edx
		push -0x1
		call icon_render
		mov eax,dword ptr ss:[esp+0x18]
		mov ecx,dword ptr ss:[esp+0x1C]
		push 0x20
		push 0x20
		push eax
		push ecx
		push 0x5000FF00
		call over_render
		add esp,0x14
		jmp bar_jump

		_wind: //white
		popad
		push 0x1
		push 0x0
		push eax
		push ebx
		push ebp
		push ecx
		mov ecx,dword ptr ss:[esp+0x28]
		push edx
		push -0x1
		call icon_render
		mov eax,dword ptr ss:[esp+0x18]
		mov ecx,dword ptr ss:[esp+0x1C]
		push 0x20
		push 0x20
		push eax
		push ecx
		push 0x50FFFFFF
		call over_render
		add esp,0x14
		jmp bar_jump
	}
}

//main function
void item_color() {
	//asm hook addresses
	Hook((void*)0x51826D, bag_hook, 8);
	Hook((void*)0x4FFCE3, bar_hook, 5);
}
