#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "AVLtree.hpp"
#include "operations.hpp"
#include <algorithm>
using namespace std;

string removeCommas(const string& input) {
    string result = input;
    result.erase(remove(result.begin(), result.end(), ','), result.end());
    return result;
}

int main(){
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
        
        if(s == "#1" || s == "# 1") {
            getline(fin, s);
            s = removeCommas(s);
            stringstream ss(s);
            string rollNo, fname, lname, cg, numsubjects;
            ss >> rollNo >> fname >> lname >> cg >> numsubjects;
            string fullName = fname + " " + lname;
            int numSub = stoi(numsubjects);
            courses* subjectArr = nullptr;
            if(numSub > 0){
                subjectArr = new courses[numSub];
                for(int i = 0; i < numSub; i++){
                    getline(fin, s);
                    s = removeCommas(s);
                    stringstream ssc(s);
                    int courseCode, marks;
                    ssc >> courseCode >> marks;
                    subjectArr[i] = courses{courseCode, static_cast<float>(marks)};
                }
            }
            if(AVL == nullptr){
                AVL = new BinaryTree(stoi(rollNo), fullName, stof(cg), numSub, subjectArr);
            }
            else{
                AVL->insertatAVLbyRoll(AVL, stoi(rollNo), fullName, stof(cg), numSub, subjectArr);
            }
        }
        else if(s == "#2" || s == "# 2") {
            getline(fin, s);
            s = removeCommas(s);
            stringstream ss(s);
            int rollNo;
            float newCG;
            ss >> rollNo >> newCG;
            modifycgbyrollno(AVL, rollNo, newCG);
        }
        else if(s == "#3" || s == "# 3") {
            getline(fin, s);
            s = removeCommas(s);
            stringstream ss(s);
            int rollNo, courseCode, marks;
            ss >> rollNo >> courseCode >> marks;
            addnewcourse(AVL, rollNo, courseCode, static_cast<float>(marks));
        }
        else if(s == "#4" || s == "# 4") {
            getline(fin, s);
            s = removeCommas(s);
            stringstream ss(s);
            int rollNo, courseCode, newMarks;
            ss >> rollNo >> courseCode >> newMarks;
            modifycourses(AVL, rollNo, courseCode, static_cast<float>(newMarks));
        }
        else if(s == "#5" || s == "# 5") {
            getline(fin, s);
            s = removeCommas(s);
            stringstream ss(s);
            int rollNo, courseCode;
            ss >> rollNo >> courseCode;
            deleteCourse(AVL, rollNo, courseCode);
        }
        else if(s == "#6" || s == "# 6") {
            getline(fin, s);
            s = removeCommas(s);
            int rollNo = stoi(s);
            deleteStudent(AVL, rollNo);
        }
        else if(s == "#7" || s == "# 7") {
            getline(fin, s);
            s = removeCommas(s);
            int rollNo = stoi(s);
            storeGreaterThanRollNo(AVL, rollNo);
        }
        else if(s == "#8" || s == "# 8") {
            getline(fin, s);
            s = removeCommas(s);
            int rollNo = stoi(s);
            storeLessThanRollNo(AVL, rollNo);
        }
        else if(s == "#9" || s == "# 9") {
            getline(fin, s);
            s = removeCommas(s);
            stringstream ss(s);
            int roll1, roll2;
            ss >> roll1 >> roll2;
            storeBetweenRollNos(AVL, roll1, roll2);
        }
        else if(s == "#10" || s == "# 10") {
            getline(fin, s);
            s = removeCommas(s);
            float cg = stof(s);
            storeGreaterThanCG(AVL, cg);
        }
        else if(s == "#11" || s == "# 11") {
            getline(fin, s);
            s = removeCommas(s);
            float cg = stof(s);
            storeLessThanCG(AVL, cg);
        }
        else if(s == "#12" || s == "# 12") {
            getline(fin, s);
            s = removeCommas(s);
            stringstream ss(s);
            float cg1, cg2;
            ss >> cg1 >> cg2;
            storeBetweenCGs(AVL, cg1, cg2);
        }
    }
    
    fin.close();
    return 0;
}
