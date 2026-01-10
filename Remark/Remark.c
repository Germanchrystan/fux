#include <stdio.h>

#include <stdlib.h>
#include "Remark.h"

Remark * newRemark(int voice, int note, float gravity, int errorCode) 
{
    Remark* r = (Remark*)malloc(sizeof(Remark));
    if (r == NULL) 
    {
        fprintf(stderr, "Failed to allocate memory for remark\n");
        return NULL;
    }
    r->voice = voice;
    r->note = note;
    r->gravity = gravity;
    r->errorCode = errorCode;
    return r;
}

RemarkArray newRemarkArray(size_t size) 
{
    RemarkArray arr;
    arr.size = size;
    arr.data = (Remark*)malloc(size * sizeof(Remark));
    if (arr.data == NULL) 
    {
        fprintf(stderr, "Failed to allocate memory for remark array\n");
        arr.size = 0;
    }
    return arr;
}

void freeRemarkArray(RemarkArray arr) 
{
    if (arr.data != NULL) 
    {
        free(arr.data);
    }
}

void addRemark(RemarkArray* arr, Remark remark) 
{
    if (arr == NULL || arr->data == NULL) 
    {
        fprintf(stderr, "Invalid remark array\n");
        return;
    }
    // Resize the array to hold one more remark
    Remark* newData = (Remark*)realloc(arr->data, (arr->size + 1) * sizeof(Remark));
    if (newData == NULL) 
    {
        fprintf(stderr, "Failed to reallocate memory for remark array\n");
        return;
    }
    arr->data = newData;
    arr->data[arr->size] = remark;
    arr->size += 1;
}

void fuseRemarks(RemarkArray* firstArr, RemarkArray* secondArr)
{
    if (firstArr == NULL || secondArr == NULL || firstArr->data == NULL || secondArr->data == NULL)
    {
        fprintf(stderr, "Invalid remark arrays for fusion\n");
        return;
    }

    Remark* newData = (Remark*)realloc(firstArr->data, (firstArr->size + secondArr->size) * sizeof(Remark));
    if (newData == NULL)
    {
        fprintf(stderr, "Failed to reallocate memory for remark array fusion\n");
        return;
    }

    firstArr->data = newData;
    for (size_t i = 0; i < secondArr->size; ++i)
    {
        firstArr->data[firstArr->size + i] = secondArr->data[i];
    }

    firstArr->size += secondArr->size;
}