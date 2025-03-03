#include "pin.H"
#include <iostream>
#include <fstream>
#include <sys/syscall.h>

std::ofstream syscallLog;

VOID LogSyscall(THREADID tid, CONTEXT* ctx, SYSCALL_STANDARD std, VOID* v) {
    ADDRINT syscallNum = PIN_GetSyscallNumber(ctx, std);
    syscallLog << "Syscall #" << syscallNum << " detected (TID: " << tid << ")" << std::endl;
    std::cerr << "Syscall #" << syscallNum << " detected (TID: " << tid << ")" << std::endl;
}

int main(int argc, char* argv[]) {
    syscallLog.open("syscall_trace.out");
    if (!syscallLog.is_open()) {
        std::cerr << "Failed to open syscall_trace.out!" << std::endl;
        return 1;
    }
    if (PIN_Init(argc, argv)) {
        std::cerr << "This tool should not be run independently." << std::endl;
        return 1;
    }
    PIN_AddSyscallEntryFunction(LogSyscall, NULL);
    PIN_StartProgram();
    syscallLog.close();
    return 0;
}
