#include <stdio.h>
#include "matrix_lib.h"
#include <immintrin.h>
#define MATRIX_MAX 256

int scalar_matrix_mult(float scalar_value, struct matrix *matrix)
{
	int i;
	float *nxt_rows;
	
	__m256 vec_scalar = _mm256_set1_ps(scalar_value);
	
	if(matrix == NULL)
	{
		return 0;
	}
	
	nxt_rows = matrix->rows;
	for( i = 0 ; i < matrix->width * matrix->height; i+=8, nxt_rows+=8)
	{	
		__m256 vec_rows = _mm256_load_ps(nxt_rows);
		
		
		__m256 vec_rows_result = _mm256_mul_ps(vec_rows,vec_scalar);
		_mm256_store_ps(nxt_rows, vec_rows_result);
	}

	return 1;
}


int matrix_matrix_mult(struct matrix *matrixA, struct matrix * matrixB, struct matrix * matrixC)
{
	int i,e,k;
	float *eleA, *eleB, *eleC, *linhaC;

	eleA = matrixA->rows;
	eleB = matrixB->rows;
	eleC = matrixC->rows;

	for ( k = 0 ; k < matrixA->height ; k+=1)
	{
		linhaC = eleC;
		eleB = matrixB->rows;
		for ( i = 0 ; i < matrixA->width ; i+=1, eleA+=1)
		{
			eleC = linhaC;
			__m256 vec_A = _mm256_load_ps(eleA);	
			for( e = 0 ; e < matrixB->width ; e+=VECTOR_SIZE, eleB+=VECTOR_SIZE, eleC+=VECTOR_SIZE)
			{
				__m256 vec_B = _mm256_load_ps(eleB);
				__m256 vec_c;

				if (j == 0) { 
	  				vec_c = _mm256_setzero_ps();
				} 
				else { 
	  				vec_c = _mm256_load_ps(nxt_c);
				}
				
				__m256 vec_result = _mm256_fmadd_ps(vec_A, vec_B, vec_C);
				_mm256_store_ps(eleC, vec_result);
			}
			
		}
		
	}
	return 1;
} 

