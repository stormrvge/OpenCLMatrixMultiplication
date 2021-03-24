#define TS 32

__kernel void vector_add(__global float* A, __global float* B, __global float* C, 
						const int M, const int N, const int K) 
{
    const int row = get_local_id(0);
    const int col = get_local_id(1);
    const int global_row = TS * get_group_id(0) + row;
    const int global_col = TS * get_group_id(1) + col;

    __local float Aloc[TS][TS];
    __local float Bloc[TS][TS];

    float sum = 0.0f;

    const int num_tiles = K / TS;
    for (int t = 0; t < num_tiles; t++)
    {
        const int tiled_row = TS * t + row;
        const int tiled_col = TS * t + col;
        Aloc[col][row] = A[tiled_col  * M + global_row];
        Bloc[col][row] = B[global_col * K + tiled_row];

        barrier(CLK_LOCAL_MEM_FENCE);

        for (int k = 0; k < TS; k++)
        {
            sum += Aloc[k][row] * Bloc[col][k];
        }
        barrier(CLK_LOCAL_MEM_FENCE);
    }

    C[global_col * M + global_row] = sum;
}