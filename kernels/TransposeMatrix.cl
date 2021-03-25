#define TILE_SIZE 32

__kernel void transpose(
	__global const float* input,
	__global float* output,
	int rows,
	int cols
)
{
	int col = get_global_id(0);
	int row = get_global_id(1);
	
	int local_col = get_local_id(0);
	int local_row = get_local_id(1);

	__local float buffer[TILE_SIZE][TILE_SIZE + 1];

	buffer[local_row][local_col] = input[row * cols + col]; 

	barrier(CLK_LOCAL_MEM_FENCE);

	float tmp = buffer[local_row][local_col];
	buffer[local_row][local_col] = buffer[local_col][local_row];
	buffer[local_col][local_row] = tmp;

	barrier(CLK_LOCAL_MEM_FENCE);

	output[col * rows + row] = buffer[local_col][local_row]; 
}