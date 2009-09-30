int main(){
	asm	{pop eax
		sub eax,edx
		pop edx
		imul edx
		push eax
		mov edx,3
		pop eax
		sub eax,edx
		push eax
		mov ebx,7
		pop eax
		mov edx,0
		idiv ebx
    }

	return 0;
}
