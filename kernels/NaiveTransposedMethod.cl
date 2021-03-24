__kernel void vector_add(
	__global const float* matrixA, __global const float* matrixB, __global float* matrixC,
	int m, int n, int k) 
{
	int row = get_global_id(0);
	int col = get_global_id(1);

	float sum = 0.0f;
	
	if (row >= m && col >= k)
		return; 

	for (int i = 0; i < n; i++) {
		int offsetA = row + i * n;
		int offsetB = i + col * k;
		
		sum += matrixA[offsetA] * matrixB[offsetB];
	}
	
	matrixC[row + col * k] = sum;
}