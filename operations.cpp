#include <iostream>
#include <vector>
using namespace std;
struct courses{
    int courseCode;
    int marks;
    courses(int code, float marks){
        courseCode=code;
        this->marks=marks;
    }
};
void addnewcourse(BinaryTree*& root,int rollno,int code,float  marks){
    BinaryTree* node = root; 
    while(node!=nullptr&&node->rollNo!=rollno){
        if(rollno>node->rollNo){node=node->rightC;}
        else if(rollno<node->rollNo){node=node->leftC;}
    }
    if(rollno==node->rollNo){
      courses* newcourses=new courses[node->numSubjects+1];
      for(int i=0;i<node->numSubjects;i++){
          newcourses[i]=node->subjects[i];
      }
      newcourses[numSubjects]=new courses(code,marks);
      node->subjects=newcourses;
      node->numSubjects=node->numSubjects+1;
    }
    else return;
    
}
void modifycourses(BinaryTree*& root,int rollno,int code,float  marks){
    BinaryTree* node = root; 
    while(node!=nullptr&&node->rollNo!=rollno){
        if(rollno>node->rollNo){node=node->rightC;}
        else if(rollno<node->rollNo){node=node->leftC;}
    }
    if(rollno==node->rollNo){
     for(int i=0;i<node->numSubjects;i++){
         if(code==node->subjects[i]->courseCode){
             node->subjects[i]->marks=marks;
         }
     }
    }
    else return;
}
void deleteCourse(BinaryTree*& root,int rollno,int code){
    BinaryTree* node = root; 
    while(node!=nullptr&&node->rollNo!=rollno){
        if(rollno>node->rollNo){node=node->rightC;}
        else if(rollno<node->rollNo){node=node->leftC;}
    }
    if(rollno==node->rollNo){
      courses* newcourses=new courses[node->numSubjects-1];
      bool check = false;
      for(int i=0;i<node->numSubjects;i++){
          if(node->subjects[i]->courseCode==code){
              check = true;
          }
      }
      if(check){
          int j=0;
          for(int i=0;i<node->numSubjects;i++){
            if(node->subjects[i]->courseCode!=code){
                newcourses[j++]=node->subjects[i];
            }
          }
          node->subjects=newcourses;
          node->numSubjects=node->numSubjects-1;
      }
    }
    else return;
}
void modifycgbyrollno(BinaryTree*& root,int rollno,float newcg){
    BinaryTree* node = root; 
    while(node!=nullptr&&node->rollNo!=rollno){
        if(rollno>node->rollNo){node=node->rightC;}
        else{node=node->leftC;}
    }
    if(rollno==node->rollNo){
     node->cg=newcg;
    }
    else return;
}


void modifycgbycg(BinaryTree*& root,int rollno,float newcg){
    BinaryTree* node = root; 
    while(node!=nullptr&&node->rollNo!=rollno){
        if(rollno>node->rollNo){node=node->rightC;}
        else{node=node->leftC;}
    }
    if(rollno==node->rollNo){
        BinaryTree* temp = node;
        deletestudent(root,rollno);
        temp->cg=newcg;
        insertstudent(root,temp);
    }
    else return;
}
void deleteStudent(BinaryTree* &root, int rollNo){
    root->deleteStudentbyRoll(root,rollNo);
}
