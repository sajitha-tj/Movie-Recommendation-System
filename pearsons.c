//Centered cosine similarity
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double pearson_correlation(const double * restrict A, const double * restrict B, unsigned int size) {
    double dot_p = 0.0;
    double mag_a = 0.0;
    double mag_b = 0.0;

    unsigned int i = 0;

    // Loop unrolling for better instruction-level parallelism
    for (; i + 3 < size; i += 4) {
        double a0 = A[i],     b0 = B[i];
        double a1 = A[i + 1], b1 = B[i + 1];
        double a2 = A[i + 2], b2 = B[i + 2];
        double a3 = A[i + 3], b3 = B[i + 3];

        dot_p += a0*b0 + a1*b1 + a2*b2 + a3*b3;
        mag_a += a0*a0 + a1*a1 + a2*a2 + a3*a3;
        mag_b += b0*b0 + b1*b1 + b2*b2 + b3*b3;
    }

    // Handle remaining elements
    for (; i < size; i++) {
        double a = A[i];
        double b = B[i];
        dot_p += a * b;
        mag_a += a * a;
        mag_b += b * b;
    }

    // Avoid repeated sqrt
    double denom = sqrt(mag_a * mag_b);
    return dot_p / denom;
}

void calc_similarity(double *normalizeduser, double *normalized_matrix, double *similarity, int No_of_users, int No_of_movies){
	for (int i = 0; i < No_of_users; i++) {
        // Direct pointer to the i-th user's row
        double *A = &normalized_matrix[i * No_of_movies];

        similarity[i] = pearson_correlation(normalizeduser, A, No_of_movies);
    }
}
