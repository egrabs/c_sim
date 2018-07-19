
// length is the number of allocated spaces in the array
// numElems is the number of elements actually being stored in the array
// 
// i.e. cell* cellArray = calloc(6, sizeof(cell)); 
//      cellArray[0] = someCell;
// 
// creates an array with length 6 and numElems 1

char* add_to_array(void* array, int length, int numItems, void* to_add, int sizeOfItem) {
    char* newArray;
    if (length == numItems) {
        newArray = resize_array(array, length);
        newArray[numItems * sizeOfItem] = *(to_add);
    } else {
        newArray = (char *) array;
        newArray[numItems * sizeOfItem] = *(to_add);
    }
    return newArray;
}


void clear_array(void* array, int length, int sizeOfItem) {
    char* charPtrArray = (char*) array;
    for(int i=0; i<length; i++) {
        free( charPtrArray + (i*sizeOfItem) );
    }
}


static char* resize_array(void* array, int length) {
    // doubles the length of the old array
    char* new_array = (char*) calloc(2*length, sizeof(array[0]));
    char* char_ptr_arr = (char*) array;
    for (int i=0; i<length; i++) {
        new_array[i] = char_ptr_arr[i];
    }
    free(array);
    return new_array;
}





