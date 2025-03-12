#include<iostream>
#include <string>
#ifndef NODEOPERATION_H
#define NODEOPERATION_H
using namespace std;

struct courses{
    int courseCode;
    int marks;
    courses(int code, float marks){
        courseCode=code;
        this->marks=marks;
    }
    courses() : courseCode(0), marks(0.0f) {}
};

#endif
