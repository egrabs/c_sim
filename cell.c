int overlaps(cell* cellOne, cell* cellTwo, float overlapAmnt) {
    int doesOverlaps = 0;
    if ((overlapAmnt < 0.0) || (overlapAmnt > 1.0)) {
        perror("overlap parameter must be between 0.0 and 1.0.\n");
        abort();
    }

    sphere* sphereMeshOne = cellOne->sphereMesh;
    sphere* sphereMeshTwo = cellTwo->sphereMesh;

    numSpheresOne = cellOne->numSpheres;
    numSpheresTwo = cellTwo->numSpheres;

    for (int i=0; i<numSpheresOne; i++) {
        for (int j=0; j<numSpheresTwo; j++) {
            sphere sphereOne = sphereMeshOne[i];
            sphere sphereTwo = sphereMeshTwo[j];
            vector* spherePosOne = sphereOne.pos;
            vector* spherePosTwo = sphereTwo.pos;
            vector* relativePosition = vector_subtraction(spherePosOne, spherePosTwo);
            float centerToCenterdistance = vector_magnitude(relativePosition);
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


// This function allocates memory must free it

cell* construct_cell(vector* axis, vector* pos, float length, float diameter, int generation, cell* parent) {

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
    newCell->sphereMesh->sphereArr = (sphere)

    return newCell;

}


// Frees all of the malloced memory
// associated with the data stored by a particular cell instance
void cleanup_cell(cell* cel) {
    sizeOfSphere = sizeof(sphere);
    sizeOfChild = sizeof(cel);
    sizeOfOverlap = sizeof( (cel->overlaps)[0] );
    free(cel->axis);
    free(cel->pos);

    cleanup_spheremesh(cel->sphereMesh);
    clear_array(cel->overlaps, cel->allocatedOverlaps, sizeOfOverlap);

    // Actually i don't think a cell needs to clear
    // it's own children they should get passed into
    // this function on their own eventually
    // clear_array(cel->children, cel->allocatedChildren, sizeOfChild);

    // finally free the cell itself

    free(cel);

}


void cleanup_spheremesh(sphere* sphereMesh) {
    free(sphereMesh->centerSphere);
    free(sphereMesh->fociOneSphere);
    free(sphereMesh->fociTwoSphere);
    free(sphereMesh->middleOneSphere);
    free(sphereMesh->middleTwoSphere);

    free(sphereMesh);
}


void fill_spheremesh(cell* cel) {

    sphere* centerSphere = (sphere *) malloc(sizeof(sphere));
    centerSphere->pos = cel->pos;
    centerSphere->radius = (cel->diameter / 2.0);

    sphere* fociSphereOne = malloc(sizeof(sphere));
    sphere* fociSphereTwo = malloc(sizeof(sphere));
    float fociDistance = sqrt( pow( cel->length / 2.0, 2.0 ) - pow(cel->diameter / 2.0, 2.0) );
    vector* normedCellAxis;
    norm(normedCellAxis, cel->axis);
    vector* fociOnePos = vector_add(cel->pos;
    // fociOnePos = pos + ( fociDistance * norm(self.axis) )


}

void position_foci_spheres(vector* fociOne, vector* fociTwo,)








