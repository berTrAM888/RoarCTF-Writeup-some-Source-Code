def patch_nop(start,end):
    for i in range(start,end):
        PatchByte(i, 0x90)

def next_instr(addr):
    return addr+ItemSize(addr)
    
st = 0x0000000000401117
end = 0x0000000000402144

addr = st
while(addr<end):
    next = next_instr(addr)
    if "ds:dword_603054" in GetDisasm(addr):
        while(True):
            addr = next
            next = next_instr(addr)
            if "jnz" in GetDisasm(addr):
                dest = GetOperandValue(addr, 0)
                PatchByte(addr, 0xe9)
                PatchByte(addr+5, 0x90) 
                offset = dest - (addr + 5)
                PatchDword(addr + 1, offset)
                print("patch bcf: 0x%x"%addr)
                addr = next
                break
    else:
        addr = next