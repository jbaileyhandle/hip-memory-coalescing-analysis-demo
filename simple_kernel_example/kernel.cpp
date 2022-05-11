#include <algorithm>
#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "hip/hip_runtime.h"

#define HIP_ASSERT(x) (assert((x)==hipSuccess))

#define VECTOR_SIZE 512
#define THREADS_PER_BLOCK 512

__global__ void kernel(int* __restrict__ input_data, int* __restrict__ output_data, long* __restrict__ big_data, int vector_size) {
  int idx = threadIdx.x;
  output_data[idx] = vector_size;
  /*
  int idx;

  // Coalesced - threadIdx.x indexes are adjacent in memory.
  idx = threadIdx.x;
  output_data[idx] = input_data[idx];

  // Unoalesced - threadIdx.x * 2 indexes are staggered in memory.
  idx = threadIdx.x * 2;
  output_data[idx] = input_data[idx];

  // Unoalesced - threadIdx.x is contiguous, but data type is too big for access to be fully coalesced.
  idx = threadIdx.x;
  big_data[idx] = 10;

  // Coalesced - Data type is too big for contiguous accesses to be fully coalesced, but we only access 1 index.
  idx = 0;
  big_data[idx] = 10;

  // Coalesced - threadIdx.y indexes are assumed constant within a wavefront.
  idx = threadIdx.y;
  output_data[idx] = input_data[idx];///////////////////////////////////////////////////////////////////////////

  // Coalesced - threadIdx.z indexes are assumed constant within a wavefront.
  idx = threadIdx.z;
  output_data[idx] = input_data[idx];

  // Coalesced - blockDim.x is a constant.
  idx = blockDim.x;
  output_data[idx] = input_data[idx];

  // Coalesced - blockDim.y is a constant.
  idx = blockDim.y;
  output_data[idx] = input_data[idx];

  // Coalesced - blockDim.z is a constant.
  idx = blockDim.z;
  output_data[idx] = input_data[idx];

  // Coalesced - blockIdx.x indexes are assumed constant within a wavefront.
  idx = blockIdx.x;
  output_data[idx] = input_data[idx];

  // Coalesced - blockIdx.y indexes are assumed constant within a wavefront.
  idx = blockIdx.y;
  output_data[idx] = input_data[idx];

  // Coalesced - blockIdx.z indexes are assumed constant within a wavefront.
  idx = blockIdx.z;
  output_data[idx] = input_data[idx];

  // Coalesced - gridDim.x is a constant.
  idx = gridDim.x;
  output_data[idx] = input_data[idx];///////////////////////////////////////////////////////////////////////////

  // Coalesced - gridDim.y is a constant.
  idx = gridDim.y;
  output_data[idx] = input_data[idx];

  // Coalesced - gridDim.z is a constant.
  idx = gridDim.z;
  output_data[idx] = input_data[idx];

  // Memcpy - Coalesced.
  int src_constant = 2;
  int dst_constant;
  memcpy(&dst_constant, &src_constant, sizeof(int));
  output_data[dst_constant] = 10;

  // Memcpy - Uncoalesced.
  int src_uncoalesced = 2 * threadIdx.x;
  int dst_uncoalesced;
  memcpy(&dst_uncoalesced, &src_uncoalesced, sizeof(int));
  output_data[dst_uncoalesced] = 10;

  constexpr int x = 2 * 4;
  */

}

int main() {

	// Init host data
	int host_data[VECTOR_SIZE];
	for(int i = 0; i < VECTOR_SIZE; ++i) {
		host_data[i] = i;
	}
	int host_result[VECTOR_SIZE];
	long host_big_data[VECTOR_SIZE];

	int expected_result[VECTOR_SIZE];
	for(int i = 0; i < VECTOR_SIZE; ++i) {
		expected_result[i] = 6*i+2;
	}
	expected_result[0] = 3;
	expected_result[VECTOR_SIZE-1] = (VECTOR_SIZE-2) + (VECTOR_SIZE-1)*2;

	int* device_data;
	int* device_result;
	long* device_big_data;

	HIP_ASSERT(hipMalloc((void**)&device_data, VECTOR_SIZE * sizeof(int)));
	HIP_ASSERT(hipMalloc((void**)&device_result, VECTOR_SIZE* sizeof(int)));
	HIP_ASSERT(hipMalloc((void**)&device_big_data, VECTOR_SIZE* sizeof(long)));

	// Transfer Input
	HIP_ASSERT(hipMemcpy(device_data, host_data, VECTOR_SIZE * sizeof(int), hipMemcpyHostToDevice));

	// Launch
	hipLaunchKernelGGL(kernel,
			dim3(VECTOR_SIZE / THREADS_PER_BLOCK),
			dim3(THREADS_PER_BLOCK),
			0, 0,
			device_data, device_result, device_big_data, VECTOR_SIZE);


	// Transfer Output
	HIP_ASSERT(hipMemcpy(host_result, device_result, VECTOR_SIZE * sizeof(int), hipMemcpyDeviceToHost));
	HIP_ASSERT(hipMemcpy(host_big_data, device_big_data, VECTOR_SIZE * sizeof(long), hipMemcpyDeviceToHost));


	// Free memory
	HIP_ASSERT(hipFree(device_data));
	HIP_ASSERT(hipFree(device_result));
	HIP_ASSERT(hipFree(device_big_data));

	return 0;
}


