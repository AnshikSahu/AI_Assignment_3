#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    //input file
    int n,m,k1,k2;
    int i,j,k,x,y;
    const char* fileName = argv[1];
    std::ifstream inputFile(fileName);

    inputFile >> n >> m >> k1 >> k2;
    const char* fileName2="test.satoutput";
    std::ifstream inputFile2(fileName2);
    string line;
    const char* fileName3="test.mapping";
    std::ofstream outputFile(fileName3);
    getline(inputFile2,line);
    if(line=="UNSAT"){
        outputFile<<"0";
        return 0;
    }
    getline(inputFile2,line);
    //get list from line
    int output[n*k1+k2*n];
    int index=0;
    string temp="";
    for(i=0;i<line.length();i++){
        if(line[i]==' '){
            output[index]=stoi(temp);
            index++;
            temp="";
        }
        else{
            temp+=line[i];
        }
    }
    outputFile<<"#1\n";
    for(i=0;i<n;i++){
        for(j=0;j<k1;j++){
            if(output[i*k1+j]<0){
                outputFile<<i+1<<" ";
            }
        }
    }
    outputFile<<"\n#2\n";
    for(i=0;i<n;i++){
        for(j=0;j<k2;j++){
            if(output[i*k2+j+n*k1]<0){
                outputFile<<i+1<<" ";
            }
        }
    }  
    outputFile.close();
    inputFile.close();
    inputFile2.close();
    return 0; 
}

