#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>


#include "vectorutils.h"



// AUTHOR: Elyes Graba




//             *****************     ALL VECTORS ARE ALWAYS LENGTH 3     ***********
//                       *******     *******************************  *************



// 
// 
//  TODO: remove callocs and mallocs from utility functions .. they should
//   instead accept a pointer to the destination vector so that mallocs happen
//   outside of utility function calls
// 
// 


// returns the real numbered dot product of 2 length-3 vectors
// 

float dotProduct(vector* vec1, vector* vec2) {

    float dotProduct = (vec1->x * vec2->x) + (vec1->y * vec2->y) + (vec1->z * vec2->z);
    return dotProduct;

}

// Returns the cross product of 2 length-3 real numbered vectors
// as another length-3 real numbered vector
// WARNING: returns malloced memory, must free

void crossProduct(vector* dstVec, vector* vec1, vector* vec2) {
    dstVec->x = ( vec1->y * vec2->z - vec1->z * vec2->y );
    dstVec->y = ( vec1->z * vec2->x - vec1->x * vec2->z );
    dstVec->z = ( vec1->x * vec2->y - vec1->y * vec2->x );
}


#include vectorutils.h

// constructs a 3D vector
void makeVector(vector* vec, float xVal, float yVal, float zVal) {
    vec->x = xVal;
    vec->y = yVal;
    vec->z = zVal;
}


// puts the result of scaleFactor * vector into dstVec
void scalarMultiply(vector* dstVec, float scaleFactor, vector* vector) {
    dstVec->x = scaleFactor * vector->x;
    dstVec->y = scaleFactor * vector->y;
    dstVec->z = scaleFactor * vector->z;
}


// compute the norm of vector (length 1.0 vector pointing in same direction as orginal)
// and store the result in the memory pointed to by dstVec
void norm(vector* dstVec, vector* vector) {
    float magnitude = vectorMagnitude(vector);
    float coefficient = 1.0 / magnitude;
    scalar_multiply(dstVec, coefficient, vector);
}


float magnitude(vector* vec) {
    float iSquared = pow(vec->x, 2.0);
    float jSquared = pow(vec->y, 2.0);
    float kSquared = pow(vec->z, 2.0);
    float sum = iSquared + jSquared + kSquared;
    float magnitude = sqrt(sum);
    return magnitude;
}


// puts the result of vec1 + vec2 in
// dstVec
void vectorAdd(vector* dstVec, vector* vec1, vector* vec2) {
    dstVec->x = vec1->x + vec2->x;
    dstVec->y = vec1->y + vec2->y;
    dstVec->z = vec1->z + vec2->z;
}


// puts the result of vec1 - vec2 into
// dstVec
void vectorSubtract(vector* dstVec, vector* vec1, vector* vec2) {
    dstVec->x = vec1->x - vec2->x;
    dstVec->y = vec1->y - vec2->y;
    dstVec->z = vec1->z - vec2->z;
}

int main(void) {

    float* vec1 = malloc(3*sizeof(float));
    float* vec2 = malloc(3*sizeof(float));
    vec1[0]= 1.0;
    vec1[1] = 2.0;
    vec1[2] = 3.0;
    vec2[0] = 4.0;
    vec2[1] = 5.0;
    vec2[2] = 6.0;
    int len1 = 3;
    int len2 = 3;
    float* new_arr  = resize_array(vec1, 3);
    long int new_len = sizeof(new_arr) / sizeof(new_arr[0]);
    printf("NEW LENGTH %lu\n", new_len);
    printf("%i\n", len1);
    float inner_product = vector_dot_product(vec1, len1, vec2, len2);
    float* crossProduct = vector_cross_product(vec1, len1, vec2, len2);
    printf("%f\n", inner_product);
    printf("%f %f %f\n", crossProduct[0], crossProduct[1], crossProduct[2]);
    return 0;
}
