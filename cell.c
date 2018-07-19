#include <math.h>
#include <stdlib.h>

#include "cell.h"
#include "vectorutils.h"
#include "arrayutils.h"

#define newSphere (sphere*) malloc(sizeof(sphere))
#define newVector (vector*) malloc(sizeof(vector))

int overlaps(cell* cellOne,
             cell* cellTwo,
             float overlapAmnt) {

    int doesOverlaps = 0;
    if ((overlapAmnt < 0.0) || (overlapAmnt > 1.0)) {
        perror("overlap parameter must be between 0.0 and 1.0.\n");
        abort();
    }

    sphere* sphereMeshOne = cellOne->sphereMesh;
    sphere* sphereMeshTwo = cellTwo->sphereMesh;

    // int numSpheresOne = cellOne->numSpheres;
    // int numSpheresTwo = cellTwo->numSpheres;

    for (int i=0; i<numSpheresOne; i++) {
        for (int j=0; j<numSpheresTwo; j++) {
            sphere sphereOne = sphereMeshOne[i];
            sphere sphereTwo = sphereMeshTwo[j];
            vector* spherePosOne = sphereOne.pos;
            vector* spherePosTwo = sphereTwo.pos;
            vector* relativePosition = newVector;
            vectorSubtraction(relativePosition, spherePosOne, spherePosTwo);
            float centerToCenterdistance = vectorMagnitude(relativePosition);
            float radiiSum = sphereOne.radius + sphereTwo.radius;
            if ( centerToCenterdistance < overlapAmnt*(radiiSum) ) {
                return 1;
            }
            if ( centerToCenterdistance < (radiiSum) ) {
                float overlap = centerToCenterdistance / (radiiSum);
                
            }

        }
    }
}


// This function allocates memory, must free it

cell* constructCell(vector* axis,
                    vector* pos,
                    float length,
                    float diameter,
                    int generation,
                    cell* parent) {

    cell* newCell = (cell*) malloc(sizeof(newCell));
    // compiler will probably complain about this, need to ensure that it's ok to set array
    // pointer in cell to float pointer since array degrades to pointer in function call
    newCell->axis = axis;
    newCell->pos = pos;
    newCell->axisLength = 3;
    newCell->posLength = 3;
    newCell->length = length;
    newCell->diameter = diameter;
    newCell->generation = generation;
    newCell->parent = parent;
    newCell->generation = 0;
    newCell->numChildren = 0;
    newCell->numOverlaps = 0;
    newCell->failedSpawns = 0;

    newCell->sphereMesh = (sphereMesh*) malloc(sizeof(sphereMesh));
    fillSpheremesh(newCell);

    return newCell;

}


// Frees all of the malloced memory
// associated with the data stored by a particular cell instance
void cleanupCell(cell* cel) {
    int sizeOfSphere = sizeof(sphere);
    int sizeOfChild = sizeof(cel);
    int sizeOfOverlap = sizeof( (cel->overlaps)[0] );
    free(cel->axis);
    free(cel->pos);

    cleanupSpheremesh(cel->sphereMesh);
    clearArray(cel->overlaps, cel->allocatedOverlaps, sizeOfOverlap);

    // Actually i don't think a cell needs to clear
    // it's own children they should get passed into
    // this function on their own eventually

    // clear_array(cel->children, cel->allocatedChildren, sizeOfChild);

    // finally free the cell itself

    free(cel);

}


void cleanupSpheremesh(sphereMesh* sphereMesh) {
    free(sphereMesh->centerSphere);
    free(sphereMesh->fociSphereOne);
    free(sphereMesh->fociSphereTwo);
    free(sphereMesh->middleSphereOne);
    free(sphereMesh->middleSphereTwo);

    free(sphereMesh);
}


/*
  Sphere Mesh consists of one center sphere, 2 semi-axis middle sphers,
  and 2 foci spheres, all of which will live on the heap and need to be
  freed whenever a cell is sent for cleanup
*/
void fillSpheremesh(cell* cel) {

    sphere* centerSphere = (sphere *) malloc(sizeof(sphere));
    centerSphere->pos = cel->pos;
    centerSphere->radius = (cel->diameter / 2.0);

    float fociDistance = sqrt( pow( cel->length / 2.0, 2.0 ) - pow(cel->diameter / 2.0, 2.0) );
    float fociRadii = (cel->length / 2.0) - fociDistance;

    vector* normedCellAxis = newVector;
    norm(normedCellAxis, cel->axis);
    vector* fociDisp = newVector;
    scalarMultiply(fociDisp, fociDistance, normedCellAxis);


    sphere* fociSphereOne = newSphere;
    vector* fociOnePos = newVector;
    vectorAdd(fociOnePos, cel->pos, fociDisp);
    fociSphereOne->pos = fociOnePos;
    fociSphereOne->radius = fociRadii;


    sphere* fociSphereTwo = newSphere;
    vector* fociTwoPos = newVector;
    vectorSubtract(fociTwoPos, cel->pos, fociDisp);
    fociSphereTwo->pos = fociTwoPos;
    fociSphereTwo->radius = fociRadii;

    float middleDistance = fociDistance / 2;    
    float middleRadius = sqrt(1.0 - (middleDistance / pow(cel->length / 2.0, 2.0))) * (cel->diameter / 2.0);
    vector* middleDisp = newVector;
    scalarMultiply(middleDisp, middleDistance, normedCellAxis);
    
    sphere* middleSphereOne = newSphere;
    vector* middleOnePos = newVector;
    vectorAdd(middleOnePos, cel->pos, middleDisp);
    middleSphereOne->pos = middleOnePos;
    middleSphereOne->radius = middleRadius;

    sphere* middleSphereTwo = newSphere;
    vector* middleTwoPos = newVector;
    vectorSubtract(middleTwoPos, cel->pos, middleDisp);
    middleSphereTwo->pos = middleTwoPos;
    middleSphereTwo->radius = middleRadius;

    cel->sphereMesh->centerSphere = centerSphere;
    cel->sphereMesh->fociSphereOne = fociSphereOne;
    cel->sphereMesh->fociSphereTwo = fociSphereTwo;
    cel->sphereMesh->middleSphereOne = middleSphereOne;
    cel->sphereMesh->middleSphereTwo = middleSphereTwo;
}








