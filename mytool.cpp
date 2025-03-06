#include "pin.H"
#include <iostream>
#include <fstream>
#include "xed-iclass-enum.h"

std::ofstream flushLog;

VOID LogFlushFence(VOID* ip, const std::string& disasm) {
    flushLog << "Detected: " << disasm << " at address: " << ip << std::endl;
    std::cerr << "Detected: " << disasm << " at address: " << ip << std::endl;
}

VOID Instruction(INS ins, VOID* v) {
    if (INS_Opcode(ins) == XED_ICLASS_CLFLUSH || 
        INS_Opcode(ins) == XED_ICLASS_MFENCE || 
        INS_Opcode(ins) == XED_ICLASS_LFENCE || 
        INS_Opcode(ins) == XED_ICLASS_SFENCE) { 
        std::string disasm = INS_Disassemble(ins);
        INS_InsertCall(
            ins, IPOINT_BEFORE, (AFUNPTR)LogFlushFence,
            IARG_INST_PTR,
            IARG_PTR, new std::string(disasm),
            IARG_END
        );
    }
}

int main(int argc, char* argv[]) {
    flushLog.open("flushtrace.out");
    if (!flushLog.is_open()) {
        std::cerr << "Failed to open flushtrace.out!" << std::endl;
        return 1;
    }
    if (PIN_Init(argc, argv)) {
        std::cerr << "This tool should not be run independently." << std::endl;
        return 1;
    }
    INS_AddInstrumentFunction(Instruction, 0);
    PIN_StartProgram();
    flushLog.close();
    return 0;
}
