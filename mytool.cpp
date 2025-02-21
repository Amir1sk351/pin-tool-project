#include "pin.H"
#include <iostream>
#include <fstream>

std::ofstream outFile; // Output file to store memory access logs

// Function called when a memory read occurs
VOID RecordMemRead(VOID* ip, VOID* addr) {
    outFile << "Read from memory at address: " << addr << " by instruction at: " << ip << std::endl;
}

// Function called when a memory write occurs
VOID RecordMemWrite(VOID* ip, VOID* addr) {
    outFile << "Write to memory at address: " << addr << " by instruction at: " << ip << std::endl;
}

// Function to instrument each instruction
VOID Instruction(INS ins, VOID* v) {
    // Check if the instruction is a memory read (LOAD)
    if (INS_IsMemoryRead(ins)) {
        INS_InsertCall(
            ins, IPOINT_BEFORE, (AFUNPTR)RecordMemRead,
            IARG_INST_PTR,      // Address of the instruction
            IARG_MEMORYREAD_EA, // Address of the memory being read
            IARG_END
        );
    }

    // Check if the instruction is a memory write (STORE)
    if (INS_IsMemoryWrite(ins)) {
        INS_InsertCall(
            ins, IPOINT_BEFORE, (AFUNPTR)RecordMemWrite,
            IARG_INST_PTR,      // Address of the instruction
            IARG_MEMORYWRITE_EA, // Address of the memory being written
            IARG_END
        );
    }
}

// Main function for the Pin tool
int main(int argc, char* argv[]) {
    // Open the output file
    outFile.open("memtrace.out");

    // Initialize Pin
    if (PIN_Init(argc, argv)) {
        std::cerr << "This tool should not be run independently." << std::endl;
        return 1;
    }

    // Add the instrumentation function
    INS_AddInstrumentFunction(Instruction, 0);

    // Start the program
    PIN_StartProgram();

    // Close the output file
    outFile.close();

    return 0;
}
