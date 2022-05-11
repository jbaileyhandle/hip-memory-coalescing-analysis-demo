# hip-memory-coalescing-analysis-demo

# Clone Repository
git clone --recursive git@github.com:jbaileyhandle/hip-memory-coalescing-analysis-demo.git

# Build llvm
cd llvm-project
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_ASSERTIONS=1 -DLLVM_TARGETS_TO_BUILD="AMDGPU;X86" -DLLVM_ENABLE_PROJECTS="clang;lld;compiler-rt" ../llvm
make -j

# Configure environment so that HIP uses the version of llvm we just built
export HIP_CLANG_PATH=<Path to this repository>/llvm-project/build/bin

# 
