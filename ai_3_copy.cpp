#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]){

    //input file
    int n,m,k1,k2;
    int i,j,k,x,y;
    const char* fileName = argv[1];
    std::ifstream inputFile(fileName);

    inputFile >> n >> m >> k1 >> k2;
    vector<int> adj[n];
    for(i=0;i<n;i++){
        adj[i]=vector<int>();
    }
    for(i=0;i<m;i++){
        inputFile >> x >> y;
        adj[x-1].push_back(y-1);
        adj[y-1].push_back(x-1);
    }

    // //input
    // int n,m,k1,k2;
    // cin>>n,m,k1,k2;
    // vector<int> adj[n];
    // int i,j,k,x,y;
    // for(i=0;i<n;i++){
    //     adj[i]=vector<int>();
    // }
    // for(i=0;i<m;i++){
    //     cin>>x>>y;
    //     adj[x-1].push_back(y-1);
    //     adj[y-1].push_back(x-1);
    // }

    // Clauses
    vector<string> clauses;
    string temp,temp1,temp2;

    // Existince
    for(i=0;i<k1;i++){
        temp="";
        for(j=0;j<n;j++){
            temp+=(to_string(-1*(j*k1+i+1))+" ");
        }
        clauses.push_back(temp+"0");
    }
    for(i=0;i<k2;i++){
        temp="";
        for(j=0;j<n;j++){
            temp+=(to_string(-1*(j*k2+i+1+k1*n))+" ");
        }
        clauses.push_back(temp+"0");
    }

    // Uniqueness
    for(i=0;i<n;i++){

        // For G1 nodes
        for(j=0;j<k1;j++){
            temp1=to_string(i*k1+j+1);
            for(k=0;k<k1;k++){
                if(k>j){
                    clauses.push_back(temp1+" "+to_string(i*k1+k+1)+" 0");
                }
            }
            for(k=0;k<n;k++){
                if(k>i){
                    clauses.push_back(temp1+" "+to_string(k*k1+i+1)+" 0");
                }
            }
            for(k=0;k<k2;k++){
                clauses.push_back(temp1+" "+to_string(i*k2+k+1+n*k1)+" 0");
            }
        }

        // For G2 nodes
        for(j=0;j<k2;j++){
            temp2=to_string(k1*n+i*k2+j+1);
            for(k=0;k<k2;k++){
                if(k>j){
                    clauses.push_back(temp2+" "+to_string(k1*n+i*k2+k+1)+" 0");
                }
            }
            for(k=0;k<n;k++){
                if(k>i){
                    clauses.push_back(temp2+" "+to_string(k1*n+k*k2+i+1)+" 0");
                }
            }
            for(k=0;k<k2;k++){
                clauses.push_back(temp2+" "+to_string(i*k1+k+1)+" 0");
            }
        }
    }

    // Connectivity
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if((find(adj[i].begin(),adj[i].end(),j)==adj[j].end()) & (j>i)){
                for(k=0;k<k1;k++){
                    for(int l=0;l<k1;l++){
                        if(l>k){
                        clauses.push_back(to_string(i*k1+k+1)+" "+to_string(j*k1+l+1)+" 0");
                        }
                    }
                }
                for(k=0;k<k2;k++){
                    for(int l=0;l<k2;l++){
                        if(l>k){
                        clauses.push_back(to_string(k1*n+i*k2+k+1)+" "+to_string(k1*n+j*k2+l+1)+" 0");
                        }
                    }
                }
            }
        }
    }

    //Write to file
    std::ofstream outputFile("test.satinput");
    outputFile << "p cnf "+to_string(n*(k1+k2))+" "+to_string(clauses.size()) << std::endl;
    for (const std::string& clause : clauses) {
        outputFile << clause << std::endl;
    }
    outputFile.close();

    return 1;
}
