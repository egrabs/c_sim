
//             *****************     ALL VECTORS ARE ALWAYS LENGTH 3     ***********
//                       *******     *******************************  *************

const int VECTORLENGTH = 3;

typedef struct _vector3D {
    float x;
    float y;
    float z;
} vector;

float dotProduct(vector* vec1, vector* vec2);

void crossProduct(vector* dstVec, vector* vec1, vector* vec2);

void makeVector(vector* vec, float val1, float val2, float val3);

void scalarMultiply(vector* dstVec, float scaleFactor, vector* vector);

void norm(vector* dstVec, vector* vector);

float magnitude(vector* vec);

void vectorAdd(vector* dstVec, vector* vec1, vector* vec2);

void vectorSubtract(vector* dstVec, vector* vec1, vector* vec2);