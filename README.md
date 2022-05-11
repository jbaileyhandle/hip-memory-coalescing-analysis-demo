# hip-memory-coalescing-analysis-demo
This is a demonstration of our AMD port of GPUDrano (https://github.com/upenn-acg/gpudrano-static-analysis_v1.0), a tool to identify uncoalesced memory accesses. The repo contains two directories. llvm-project contains llvm, which includes the uncoalesced memory pass. simple_kernel_example contains a simpel kernel and a makefile which runs the memory anlysis on the kernel when it is compiled.

# Dependencies
HIP**

** Tested to work on HIP 5.1.20531-cacfa990, but may not work on older versions (i.e. verified not to work 4.2.21155-37cb3a34 due to changes in some HIP function names)

# Instructions to build + run demonstration.

### Clone repository
git clone --recursive git@github.com:jbaileyhandle/hip-memory-coalescing-analysis-demo.git

** Important: Must include "--recursive" flag in above command or llvm-project will not be cloned!

### Build llvm
(In llvm-project subdirectory)

mkdir -p build && cd build

cmake -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_ASSERTIONS=1 -DLLVM_TARGETS_TO_BUILD="AMDGPU;X86" -DLLVM_ENABLE_PROJECTS="clang;lld;compiler-rt" ../llvm

make -j

### Configure environment so that HIP uses the version of llvm we just built
export HIP_CLANG_PATH=<Path to this repository>/llvm-project/build/bin

### Run analysis on simple kernel
(In simple_kernel_example subdirectory)

make
