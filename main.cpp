
#include<fstream>
#include<sstream>
#include <iostream>
#include<string>
#include "AVLTree.cpp"
using namespace std;
string removeCommas(const string& input) {
    string result = input; 
    result.erase(remove(result.begin(), result.end(), ','), result.end());
    return result;
}

int main(){
    BinaryTree* AVL=new BinaryTree();
    ifstream fin;
    ofstream fout;
    fout.open("Output.txt");
    fin.open("input_avl.txt");
    string s;
    while(getline(fin,s)){
        
        if(s=="# 1"){
            
            getline(fin,s);
            s=removeCommas(s);
            stringstream ss(s);
            
            string rollNo,fname,lname,cg,numsubjects;
            
            ss>>rollNo>>fname>>lname>>cg>>numsubjects;
            cout<<fname+" "+lname<<endl;
            
            
            for(int i=0;i<stoi(numsubjects);i++){
                string course;
                getline(fin,course);
                course=removeCommas(course);
                
                
            }
            AVL->insertatAVLbyRoll(AVL,stoi(rollNo),fname+" "+lname,stof(cg),stoi(numsubjects),NULL);
                
            
            
        }
    }
    fout.close();
    fin.close();
    
    
}
