__kernel void vector_add(__global float* A, __global float* B, __global float* C, 
						const int M, const int N, const int K) 
{
	int row = get_global_id(0); 
	int col = get_global_id(1);
 
	// value stores the element that is 
	// computed by the thread
	float value = 0.0f;
	for (int k = 0; k < K; ++k)
	{
		float elementA = A[row + k * M];
		float elementB = B[k + col * K];
		value += elementA * elementB;
	}
 
	// Write the matrix to device memory each 
	// thread writes one element
	C[col * M + row] = value;
}