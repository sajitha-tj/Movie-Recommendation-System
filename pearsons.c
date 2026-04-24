//Centered cosine similarity
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double pearson_correlation(double *A, double *B, unsigned int size){
    double dot_p=0.0;
    double mag_a=0.0;
    double mag_b=0.0;
    int i;
    for(i=0; i<size; i++){
        dot_p += A[i]*B[i];
        mag_a += A[i]*A[i];
        mag_b += B[i]*B[i];
    }
    return dot_p/(sqrt(mag_a)*sqrt(mag_b));
}

void calc_similarity(double *normalizeduser, double *normalized_matrix, double *similarity, int No_of_users, int No_of_movies){
	for (int i = 0; i < No_of_users; i++) {
        // Direct pointer to the i-th user's row
        double *A = &normalized_matrix[i * No_of_movies];

        similarity[i] = pearson_correlation(normalizeduser, A, No_of_movies);
    }
}
