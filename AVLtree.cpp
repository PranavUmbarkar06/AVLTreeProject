#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
struct courses{
    int courseCode;
    int marks;
};
class BinaryTree{
    public:
    int rollNo;
    string name;
    float cg;
    int numSubjects;
    courses *subjects;
    BinaryTree* parent;
    BinaryTree* leftC;
    BinaryTree* rightC;
    
    BinaryTree(int rollNo, string name, float cg, int numsubjects, courses *subjects){
        this->rollNo = rollNo;
        this->name = name;
        this->cg = cg;
        this->numSubjects = numSubjects;
        this->subjects = subjects;
        parent = nullptr;
        leftC = nullptr;
        rightC = nullptr;
    }
    BinaryTree(){
        parent = nullptr;
        leftC = nullptr;
        rightC = nullptr;
    }

    void insertatAVLbyRoll(BinaryTree* &root, int rollNo, string name, float cg, int numsubjects, courses *subjects){
        if(root ==nullptr){
            root = new BinaryTree(rollNo, name, cg, numsubjects, subjects);
            return ;
        }
    
        if(rollNo>root->rollNo){
            insertatAVLbyRoll(root->rightC, rollNo, name, cg, numsubjects, subjects);
        }
        else if(rollNo<root->rollNo) insertatAVLbyRoll(root->leftC, rollNo, name, cg, numsubjects, subjects);
        else return;
    
        int height = checkBalanceFactor(root);
    
        if(height>1 && rollNo<root->leftC->rollNo){
            root = rightRotation(root);
        }
        else if(height>1 && rollNo>root->leftC->rollNo){
            root->leftC=leftRotation(root->leftC);
            root = rightRotation(root);
        }
        else if(height<-1 && rollNo>root->rightC->rollNo){
            root = leftRotation(root);
        }
        else if(height<-1 && rollNo<root->leftC->rollNo){
            root->rightC=rightRotation(root->rightC);
            root = leftRotation(root);
        }
    }

    void insertatAVLbyCg(BinaryTree* &root, int rollNo, string name, float cg, int numsubjects, courses *subjects){
        if(root ==nullptr){
            root = new BinaryTree(rollNo, name, cg, numsubjects, subjects);
            return ;
        }
    
        if(cg>root->cg){
            insertatAVLbyCg(root->rightC, rollNo, name, cg, numsubjects, subjects);
        }
        else if(cg<root->cg) insertatAVLbyCg(root->leftC, rollNo, name, cg, numsubjects, subjects);
        else return;
    
        int height = checkBalanceFactor(root);
    
        if(height>1 && cg<root->leftC->cg){
            root = rightRotation(root);
        }
        else if(height>1 && cg>root->leftC->cg){
            root->leftC=leftRotation(root->leftC);
            root = rightRotation(root);
        }
        else if(height<-1 && cg>root->rightC->cg){
            root = leftRotation(root);
        }
        else if(height<-1 && cg<root->leftC->cg){
            root->rightC=rightRotation(root->rightC);
            root = leftRotation(root);
        }
    }


    BinaryTree* leftRotation(BinaryTree* node){
        BinaryTree* x = node;
        BinaryTree* y = x->rightC;
        BinaryTree* z = y->leftC;
        y->leftC = x;
        x->rightC = z;
        return y;
    }
    
    BinaryTree* rightRotation(BinaryTree* node){
        BinaryTree* x = node;
        BinaryTree* y = x->leftC;
        BinaryTree* z = y->rightC;
        y->rightC = x;
        x->leftC = z;
        return y;
    }
    
    int maxHeight(BinaryTree* root){
        if(root==nullptr) return 0;
        
        int heightL = maxHeight(root->leftC);
        int heightR = maxHeight(root->rightC);
        
        return 1 + max(heightR, heightL);
    }
    
    int checkBalanceFactor(BinaryTree* root){
        if(root==nullptr) return 0;
        int leftHeight = 0, rightHeight = 0;
        if(root->leftC!=nullptr) leftHeight = maxHeight(root->leftC);
        if(root->rightC!=nullptr) rightHeight = maxHeight(root->rightC);
    
        return (leftHeight-rightHeight);
    }
};


