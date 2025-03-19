#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <exception>
#include <algorithm>
#include <vector>
#include "AVLtree.hpp"
#include "operations.hpp"
using namespace std;

string removeCommas(const string& input) {
    string result = input;
    result.erase(remove(result.begin(), result.end(), ','), result.end());
    return result;
}

// Helper function: Inorder traversal that collects all nodes in the AVL tree.
void inorderTraversal(BinaryTree* root, vector<BinaryTree*>& nodes) {
    if (root != nullptr) {
        inorderTraversal(root->leftC, nodes);
        nodes.push_back(root);
        inorderTraversal(root->rightC, nodes);
    }
}

// Helper function: Store all nodes (i.e. generate output for the entire tree).
void storeAll(BinaryTree* root) {
    vector<BinaryTree*> nodes;
    inorderTraversal(root, nodes);
    displayNodes(nodes);
}

int main(){
    // Clear the output file at the start (so previous data is removed)
    ofstream clearFile("output.txt", ios::out);
    clearFile.close();

    BinaryTree* AVL = nullptr;
    ifstream fin("input_avl.txt");
    if(!fin){
        cerr << "Error opening input file." << endl;
        return 1;
    }
   
    string s;
    while(getline(fin, s)){
        if(s.empty())
            continue;
           
        s = removeCommas(s);
       
        try {
            if(s == "#1" || s == "# 1") {
                if(!getline(fin, s))
                    throw runtime_error("Unexpected end of file while reading student details.");
                s = removeCommas(s);
                stringstream ss(s);
                string rollNo, fname, lname, cg, numsubjects;
                if(!(ss >> rollNo >> fname >> lname >> cg >> numsubjects))
                    throw runtime_error("Invalid input format for student record.");
                string fullName = fname + " " + lname;
                int numSub = 0;
                try {
                    numSub = stoi(numsubjects);
                } catch(exception &e) {
                    throw runtime_error("Invalid number of subjects: " + numsubjects);
                }
                courses* subjectArr = nullptr;
                if(numSub > 0){
                    subjectArr = new courses[numSub];
                    for(int i = 0; i < numSub; i++){
                        if(!getline(fin, s))
                            throw runtime_error("Unexpected end of file while reading course details.");
                        s = removeCommas(s);
                        stringstream ssc(s);
                        int courseCode, marks;
                        if(!(ssc >> courseCode >> marks))
                            throw runtime_error("Invalid course input format.");
                        subjectArr[i] = courses{courseCode, static_cast<float>(marks)};
                    }
                }
                int rno = 0;
                float cgVal = 0.0;
                try {
                    rno = stoi(rollNo);
                    cgVal = stof(cg);
                } catch(exception &e) {
                    throw runtime_error("Conversion error for student record: " + string(e.what()));
                }
                if(AVL == nullptr){
                    AVL = new BinaryTree(rno, fullName, cgVal, numSub, subjectArr);
                }
                else{
                    AVL->insertatAVLbyRoll(AVL, rno, fullName, cgVal, numSub, subjectArr);
                }
            }
            else if(s == "#2" || s == "# 2") {
                if(!getline(fin, s))
                    throw runtime_error("Unexpected end of file for command #2.");
                s = removeCommas(s);
                stringstream ss(s);
                int rollNo;
                float newCG;
                if(!(ss >> rollNo >> newCG))
                    throw runtime_error("Invalid input for command #2.");
                modifycgbyrollno(AVL, rollNo, newCG);
            }
            else if(s == "#3" || s == "# 3") {
                if(!getline(fin, s))
                    throw runtime_error("Unexpected end of file for command #3.");
                s = removeCommas(s);
                stringstream ss(s);
                int rollNo, courseCode, marks;
                if(!(ss >> rollNo >> courseCode >> marks))
                    throw runtime_error("Invalid input for command #3.");
                addnewcourse(AVL, rollNo, courseCode, static_cast<float>(marks));
            }
            else if(s == "#4" || s == "# 4") {
                if(!getline(fin, s))
                    throw runtime_error("Unexpected end of file for command #4.");
                s = removeCommas(s);
                stringstream ss(s);
                int rollNo, courseCode, newMarks;
                if(!(ss >> rollNo >> courseCode >> newMarks))
                    throw runtime_error("Invalid input for command #4.");
                modifycourses(AVL, rollNo, courseCode, static_cast<float>(newMarks));
            }
            else if(s == "#5" || s == "# 5") {
                if(!getline(fin, s))
                    throw runtime_error("Unexpected end of file for command #5.");
                s = removeCommas(s);
                stringstream ss(s);
                int rollNo, courseCode;
                if(!(ss >> rollNo >> courseCode))
                    throw runtime_error("Invalid input for command #5.");
                deleteCourse(AVL, rollNo, courseCode);
            }
            else if(s == "#6" || s == "# 6") {
                if(!getline(fin, s))
                    throw runtime_error("Unexpected end of file for command #6.");
                s = removeCommas(s);
                int rollNo = 0;
                try {
                    rollNo = stoi(s);
                } catch(exception &e) {
                    throw runtime_error("Invalid roll number for command #6.");
                }
                deleteStudent(AVL, rollNo);
            }
            else if(s == "#7" || s == "# 7") {
                if(!getline(fin, s))
                    throw runtime_error("Unexpected end of file for command #7.");
                s = removeCommas(s);
                int rollNo = 0;
                try {
                    rollNo = stoi(s);
                } catch(exception &e) {
                    throw runtime_error("Invalid roll number for command #7.");
                }
                storeGreaterThanRollNo(AVL, rollNo);
            }
            else if(s == "#8" || s == "# 8") {
                if(!getline(fin, s))
                    throw runtime_error("Unexpected end of file for command #8.");
                s = removeCommas(s);
                int rollNo = 0;
                try {
                    rollNo = stoi(s);
                } catch(exception &e) {
                    throw runtime_error("Invalid roll number for command #8.");
                }
                storeLessThanRollNo(AVL, rollNo);
            }
            else if(s == "#9" || s == "# 9") {
                if(!getline(fin, s))
                    throw runtime_error("Unexpected end of file for command #9.");
                s = removeCommas(s);
                stringstream ss(s);
                int roll1, roll2;
                if(!(ss >> roll1 >> roll2))
                    throw runtime_error("Invalid input for command #9.");
                storeBetweenRollNos(AVL, roll1, roll2);
            }
            else if(s == "#10" || s == "# 10") {
                if(!getline(fin, s))
                    throw runtime_error("Unexpected end of file for command #10.");
                s = removeCommas(s);
                float cg = 0.0;
                try {
                    cg = stof(s);
                } catch(exception &e) {
                    throw runtime_error("Invalid CG value for command #10.");
                }
                storeGreaterThanCG(AVL, cg);
            }
            else if(s == "#11" || s == "# 11") {
                if(!getline(fin, s))
                    throw runtime_error("Unexpected end of file for command #11.");
                s = removeCommas(s);
                float cg = 0.0;
                try {
                    cg = stof(s);
                } catch(exception &e) {
                    throw runtime_error("Invalid CG value for command #11.");
                }
                storeLessThanCG(AVL, cg);
            }
            else if(s == "#12" || s == "# 12") {
                if(!getline(fin, s))
                    throw runtime_error("Unexpected end of file for command #12.");
                s = removeCommas(s);
                stringstream ss(s);
                float cg1, cg2;
                if(!(ss >> cg1 >> cg2))
                    throw runtime_error("Invalid input for command #12.");
                storeBetweenCGs(AVL, cg1, cg2);
            }
            else {
                cerr << "Unknown command: " << s << endl;
            }
        }
        catch(exception &e) {
            cerr << "Error processing command: " << e.what() << endl;
        }
    }
   
    fin.close();

    // Finally, generate output for the entire AVL tree.
    storeAll(AVL);
    
    return 0;
}
