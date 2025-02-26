#include<iostream>
#include <string>
using namespace std;
struct courses{
    int courseCode;
    int marks;
};
class StudentStructure{
public:
    int rollNo;
    string name;
    float cg;
    int numsubjects;
    courses *subjects;
    StudentStructure* left;
    StudentStructure* right;
    int height;
    StudentStructure(int rollNo,string name,float cg,int numsubjects,courses *subjects){
        this->rollNo=rollNo;
        this->name=name;
        this->cg=cg;
        this->numsubjects=numsubjects;
        this->subjects=subjects;
    }
};
