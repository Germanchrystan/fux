#pragma once
#include <stdlib.h>

typedef struct {
    int voice;
    int note;
    float gravity;  // 0-1
    int code;

} Remark;
typedef struct { Remark* data; size_t size; } RemarkArray;

Remark * newRemark(int voice, int note, float gravity, int errorCode);
RemarkArray *newRemarkArray();
void freeRemarkArray(RemarkArray arr);
void addRemark(RemarkArray* arr, Remark remark);
void fuseRemarks(RemarkArray* first, RemarkArray* second);

// Gravity levels
#define GravityHigh 1.0f
#define GravityMedium 0.5f
#define GravityLow 0.1f

// Error codes
#define OutOfRegister 1
#define JumpCompensation 2
#define RepeatedNotes 3
#define TritoneInPassage 4

// Error gravity levels
#define OutOfRegisterGravity GravityHigh
#define JumpCompensationGravity GravityMedium
#define RepeatedNotesGravity GravityLow
#define TritoneInPassageGravity GravityHigh

// Remark codes for counterpoint analysis
#define REMARK_PERFECT_CONSONANCE 100
#define REMARK_DISSONANCE 101
#define REMARK_IMPERFECT_CONSONANCE 102
#define REMARK_FOURTH 103