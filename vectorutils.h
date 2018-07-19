
//             *****************     ALL VECTORS ARE ALWAYS LENGTH 3     ***********
//                       *******     *******************************  *************

const int VECTORLENGTH = 3;

typedef struct _vector3D {
    float x;
    float y;
    float z;
} vector;

float dot_product(vector* vec1, vector* vec2);

void cross_product(vector* dstVec, vector* vec1, vector* vec2);

void vector(vector* vec, float val1, float val2, float val3);

void scalar_multiply(vector* dstVec, float scaleFactor, vector* vector);

void norm(vector* dstVec, vector* vector);

float magnitude(vector* vec);

void vector_add(vector* dstVec, vector* vec1, vector* vec2);

void vector_subtract(vector* dstVec, vector* vec1, vector* vec2);