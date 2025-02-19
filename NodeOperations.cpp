#include<iostream>
using namespace std;
struct courses{
    int courseCode;
    int marks;
};
class StudentStructure{
public:
    int rollNo;
    float cg;
    int numsubjects;
    courses *subjects;
    StudentStructure* left;
    StudentStructure* right;
    int height;
    StudentStructure(int rollNo,float cg,int numsubjects,courses *subjects){
        this->rollNo=rollNo;
        this->cg=cg;
        this->numsubjects=numsubjects;
        this->subjects=subjects;
    }
};
