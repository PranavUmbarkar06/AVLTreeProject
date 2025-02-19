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
    courses subjects[numsubjects];
    StudentStructure* left;
    StudentStructure* right;
    int height;
    StudentStructure(int rollNo,float cg,int numsubjects,courses subjects[]){
        this->rollNo=rollNo;
        this->cg=cg;
        this->numsubjects=numsubjects;
        for(int i=0;i<numsubjects;i++){
            this->subjects[i].courseCode=subjects[i].courseCode;
            this->subjects[i].marks=subjects[i].courseCode;
        }
    }
};
