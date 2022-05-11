SOURCES=kernel.cpp
EXECUTABLE=./kernel.exe

HIPCC=hipcc
MEMORY_COALESCING_ANALYSIS_FLAGS= -g -flegacy-pass-manager -Xclang -load -Xclang $(HIP_CLANG_PATH)/../lib/LLVMUncoalescedAnalysis.so -debug

all:
	$(HIPCC) $(MEMORY_COALESCING_ANALYSIS_FLAGS) $(SOURCES) -o $(EXECUTABLE)

clean:
	-rm $(EXECUTABLE)

