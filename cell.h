// Defines the representation of a cell as well as a sphere struct
// to represent the spheres placed in each cell for the purpose of computing overlap


typedef struct _sphere {

    vector* pos;
    float radius;

} sphere;


typedef struct _sphereMesh {
    sphere* centerSphere;
    sphere* fociSphereOne;
    sphere* fociSphereTwo;
    sphere* middleSphereOne;
    sphere* middleSphereTwo;
} sphereMesh;

typedef struct _cell {

    vector* axis;
    vector* pos;
    int axisLength, posLength;

    float length;
    float diameter;

    int generation;

    sphereMesh* sphereMesh;

    struct _cell** children;
    int numChildren;
    int allocatedChildren;

    struct _cell* parent;

    float* overlaps;
    int numOverlaps;
    int allocatedOverlaps;
    
    int failedSpawns;

} cell;


// a "constructor" for cell structs

cell* constructCell(vector* axis, vector* pos, float length, float diameter, int generation, cell* parent);

void fillSpheremesh(cell* cel);

void cleanupCell(cell* cel);

void cleanupSpheremesh(sphereMesh* sphereMesh);

int overlaps(cell* cellOne, cell* cellTwo, float overlapAmnt);


