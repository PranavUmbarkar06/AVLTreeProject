#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <iostream>
#include <vector>
#include <fstream>
#include "AVLtree.hpp"
#include "NodeOperation.hpp"
using namespace std;

void addnewcourse(BinaryTree*& root, int rollno, int code, float marks) {
    BinaryTree* node = root; 
    while (node != nullptr && node->rollNo != rollno) {
        if (rollno > node->rollNo)
            node = node->rightC;
        else
            node = node->leftC;
    }
    if (node && node->rollNo == rollno) {
        courses* newcourses = new courses[node->numSubjects + 1];
        for (int i = 0; i < node->numSubjects; i++) {
            newcourses[i] = node->subjects[i];
        }
        newcourses[node->numSubjects] = courses(code, marks);
        node->subjects = newcourses;
        node->numSubjects++;
    }
    else return;
}

void modifycourses(BinaryTree*& root, int rollno, int code, float marks) {
    BinaryTree* node = root; 
    while (node != nullptr && node->rollNo != rollno) {
        if (rollno > node->rollNo)
            node = node->rightC;
        else
            node = node->leftC;
    }
    if (node && node->rollNo == rollno) {
        for (int i = 0; i < node->numSubjects; i++) {
            if (code == node->subjects[i].courseCode) {
                node->subjects[i].marks = marks;
            }
        }
    }
    else return;
}

void deleteCourse(BinaryTree*& root, int rollno, int code) {
    BinaryTree* node = root; 
    while (node != nullptr && node->rollNo != rollno) {
        if (rollno > node->rollNo)
            node = node->rightC;
        else
            node = node->leftC;
    }
    if (node && node->rollNo == rollno) {
        courses* newcourses = new courses[node->numSubjects - 1];
        bool check = false;
        for (int i = 0; i < node->numSubjects; i++) {
            if (node->subjects[i].courseCode == code) {
                check = true;
            }
        }
        if (check) {
            int j = 0;
            for (int i = 0; i < node->numSubjects; i++) {
                if (node->subjects[i].courseCode != code) {
                    newcourses[j++] = node->subjects[i];
                }
            }
            node->subjects = newcourses;
            node->numSubjects--;
        }
    }
    else return;
}

void modifycgbyrollno(BinaryTree*& root, int rollno, float newcg) {
    BinaryTree* node = root; 
    while (node != nullptr && node->rollNo != rollno) {
        if (rollno > node->rollNo)
            node = node->rightC;
        else
            node = node->leftC;
    }
    if (node && node->rollNo == rollno) {
        node->cg = newcg;
    }
    else return;
}

void modifycgbycg(BinaryTree*& root, int rollno, float newcg) {
    BinaryTree* node = root; 
    while (node != nullptr && node->rollNo != rollno) {
        if (rollno > node->rollNo)
            node = node->rightC;
        else
            node = node->leftC;
    }
    if (node && node->rollNo == rollno) {
        BinaryTree* temp = node;
        temp->deleteStudentByRoll(root, rollno);
        temp->cg = newcg;
        temp->insertatAVLbyRoll(root, temp->rollNo, temp->name, temp->cg, temp->numSubjects, temp->subjects);
        delete temp;
    }
}

BinaryTree* searchByRoll(BinaryTree* root, int rollno) {
    if (root == nullptr)
        return nullptr;
    if (root->rollNo == rollno)
        return root;
    BinaryTree* leftResult = searchByRoll(root->leftC, rollno);
    if (leftResult != nullptr)
        return leftResult;
    return searchByRoll(root->rightC, rollno);
}

void addNewCourseInCgTree(BinaryTree*& root, int rollno, int code, float marks) {
    BinaryTree* node = searchByRoll(root, rollno);
    if (!node)
        return;
    courses* newCourses = new courses[node->numSubjects + 1];
    for (int i = 0; i < node->numSubjects; i++) {
        newCourses[i] = node->subjects[i];
    }
    newCourses[node->numSubjects] = courses(code, marks);
    node->subjects = newCourses;
    node->numSubjects++;
}

void modifyCourseInCgTree(BinaryTree*& root, int rollno, int code, float marks) {
    BinaryTree* node = searchByRoll(root, rollno);
    if (!node)
        return;
    for (int i = 0; i < node->numSubjects; i++) {
        if (node->subjects[i].courseCode == code) {
            node->subjects[i].marks = marks;
            break;
        }
    }
}

void deleteCourseInCgTree(BinaryTree*& root, int rollno, int code) {
    BinaryTree* node = searchByRoll(root, rollno);
    if (!node)
        return;
    bool found = false;
    for (int i = 0; i < node->numSubjects; i++) {
        if (node->subjects[i].courseCode == code) {
            found = true;
            break;
        }
    }
    if (!found)
        return;
    courses* newCourses = new courses[node->numSubjects - 1];
    int j = 0;
    for (int i = 0; i < node->numSubjects; i++) {
        if (node->subjects[i].courseCode != code) {
            newCourses[j++] = node->subjects[i];
        }
    }
    node->subjects = newCourses;
    node->numSubjects--;
}

void displayNodes(const vector<BinaryTree*>& nodes) {
    ofstream outfile("output.txt", ios::out);
    if (!outfile) {
        cerr << "Error opening output file." << endl;
        return;
    }
    for (size_t i = 0; i < nodes.size(); i++) {
        BinaryTree* node = nodes[i];
        outfile << "Roll No: " << node->rollNo << "\n";
        outfile << "Name: " << node->name << "\n";
        outfile << "CGPA: " << node->cg << "\n";
        outfile << "Courses:\n";
        for (int j = 0; j < node->numSubjects; j++) {
            outfile << node->subjects[j].courseCode << ": " << node->subjects[j].marks << "\n";
        }
        if (i < nodes.size() - 1) {
            outfile << "\n";
        }
    }
    outfile.close();
}

void inorderGreaterThanRollNo(BinaryTree* root, int rollno, vector<BinaryTree*>& nodes) {
    if (root != nullptr) {
        inorderGreaterThanRollNo(root->leftC, rollno, nodes);
        if (root->rollNo > rollno) {
            nodes.push_back(root);
        }
        inorderGreaterThanRollNo(root->rightC, rollno, nodes);
    }
}

void storeGreaterThanRollNo(BinaryTree* root, int rollno) {
    vector<BinaryTree*> nodes;
    inorderGreaterThanRollNo(root, rollno, nodes);
    displayNodes(nodes);
}

void inorderLessThanRollNo(BinaryTree* root, int rollno, vector<BinaryTree*>& nodes) {
    if (root != nullptr) {
        inorderLessThanRollNo(root->leftC, rollno, nodes);
        if (root->rollNo < rollno) {
            nodes.push_back(root);
        }
        inorderLessThanRollNo(root->rightC, rollno, nodes);
    }
}

void storeLessThanRollNo(BinaryTree* root, int rollno) {
    vector<BinaryTree*> nodes;
    inorderLessThanRollNo(root, rollno, nodes);
    displayNodes(nodes);
}

void inorderBetweenRollNos(BinaryTree* root, int rollno1, int rollno2, vector<BinaryTree*>& nodes) {
    if (root != nullptr) {
        inorderBetweenRollNos(root->leftC, rollno1, rollno2, nodes);
        if (root->rollNo > rollno1 && root->rollNo < rollno2) {
            nodes.push_back(root);
        }
        inorderBetweenRollNos(root->rightC, rollno1, rollno2, nodes);
    }
}

void storeBetweenRollNos(BinaryTree* root, int rollno1, int rollno2) {
    vector<BinaryTree*> nodes;
    inorderBetweenRollNos(root, rollno1, rollno2, nodes);
    displayNodes(nodes);
}

void inorderGreaterThanCG(BinaryTree* root, float cg, vector<BinaryTree*>& nodes) {
    if (root != nullptr) {
        inorderGreaterThanCG(root->leftC, cg, nodes);
        if (root->cg > cg) {
            nodes.push_back(root);
        }
        inorderGreaterThanCG(root->rightC, cg, nodes);
    }
}

void storeGreaterThanCG(BinaryTree* root, float cg) {
    vector<BinaryTree*> nodes;
    inorderGreaterThanCG(root, cg, nodes);
    displayNodes(nodes);
}

void inorderLessThanCG(BinaryTree* root, float cg, vector<BinaryTree*>& nodes) {
    if (root != nullptr) {
        inorderLessThanCG(root->leftC, cg, nodes);
        if (root->cg < cg) {
            nodes.push_back(root);
        }
        inorderLessThanCG(root->rightC, cg, nodes);
    }
}

void storeLessThanCG(BinaryTree* root, float cg) {
    vector<BinaryTree*> nodes;
    inorderLessThanCG(root, cg, nodes);
    displayNodes(nodes);
}

void inorderBetweenCGs(BinaryTree* root, float cg1, float cg2, vector<BinaryTree*>& nodes) {
    if (root != nullptr) {
        inorderBetweenCGs(root->leftC, cg1, cg2, nodes);
        if (root->cg > cg1 && root->cg < cg2) {
            nodes.push_back(root);
        }
        inorderBetweenCGs(root->rightC, cg1, cg2, nodes);
    }
}

void storeBetweenCGs(BinaryTree* root, float cg1, float cg2) {
    vector<BinaryTree*> nodes;
    inorderBetweenCGs(root, cg1, cg2, nodes);
    displayNodes(nodes);
}

void deleteStudent(BinaryTree*& root, int rollNo) {
    root->deleteStudentByRoll(root, rollNo);
}

#endif
