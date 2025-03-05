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

BinaryTree* findMin(BinaryTree* node) {
    while (node->leftC != nullptr)
        node = node->leftC;
    return node;
}

void deleteStudentByRoll(BinaryTree* &root, int rollNo) {
    if (!root)
        return;
    if (rollNo < root->rollNo)
        deleteStudentByRoll(root->leftC, rollNo);
    else if (rollNo > root->rollNo)
        deleteStudentByRoll(root->rightC, rollNo);
    else {
        if (!root->leftC || !root->rightC) {
            BinaryTree* temp = root->leftC ? root->leftC : root->rightC;
            delete root;
            root = temp;
        } else {
            BinaryTree* temp = findMin(root->rightC);
            root->rollNo = temp->rollNo;
            root->name = temp->name;
            root->cg = temp->cg;
            root->numSubjects = temp->numSubjects;
            root->subjects = temp->subjects;
            deleteStudentByRoll(root->rightC, temp->rollNo);
        }
    }
    if (!root)
        return;
    int balance = root->checkBalanceFactor(root);
    if (balance > 1 && root->checkBalanceFactor(root->leftC) >= 0)
        root = root->rightRotation(root);
    else if (balance > 1 && root->checkBalanceFactor(root->leftC) < 0) {
        root->leftC = root->leftRotation(root->leftC);
        root = root->rightRotation(root);
    } else if (balance < -1 && root->checkBalanceFactor(root->rightC) <= 0)
        root = root->leftRotation(root);
    else if (balance < -1 && root->checkBalanceFactor(root->rightC) > 0) {
        root->rightC = root->rightRotation(root->rightC);
        root = root->leftRotation(root);
    }
}

};


