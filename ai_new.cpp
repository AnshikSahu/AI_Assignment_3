#include <vector>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]){

    //input file
    int n,m,k1,k2;
    int i,j;
    const char* fileName = argv[1];
    std::ifstream inputFile(fileName);

    inputFile >> n >> m >> k1 >> k2;
    vector<vector<int>> adj(n, vector<int>(n, 0));
    vector<int> degree(n, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        inputFile >> u >> v;
        adj[u][v] = 1;
        adj[v][u] = 1;
        degree[u]++;
        degree[v]++;
    }
    int num_variables = n+n*k1+n+n*k2;
    vector<string> clauses=vector<string>();
    clauses.push_back(to_string(-1)+" "+to_string(-1*(n+1))+" 0");
    clauses.push_back(to_string(1)+" "+to_string(n+1)+" 0");
    clauses.push_back(to_string(-1*(n+n*k1+1))+" "+to_string(-1*(n+n*k1+n+1))+" 0");
    clauses.push_back(to_string(n+n*k1+1)+" "+to_string(n+n*k1+n+1)+" 0");
    for(i=0;i<n;i++){
        clauses.push_back(to_string(i+1)+" "+to_string(i+1+n+n*k1)+" 0");
        if(degree[i]<k1){
            clauses.push_back(to_string((i+1))+" 0");
        }
        if(degree[i]<k2){
            clauses.push_back(to_string((i+1+n+n*k1))+" 0");
        }
        for(j=i+1;j<n;j++){
            if(adj[i][j]==0){
                clauses.push_back(to_string(i+1)+" "+to_string(j+1)+" 0");
                clauses.push_back(to_string(i+1+n+n*k1)+" "+to_string(j+1+n+n*k1)+" 0");
            }
        }
        for(j=0;j<k1;j++){
            if(j>i){
                clauses.push_back(to_string(-1*(n+j+1+i*k1))+" 0");
            }
            else if(i!=0 and j!=0){
                if(j>0){
                    clauses.push_back(to_string(-1*(n+j+1+i*k1))+" "+to_string(n+1+j+(i-1)*k1)+" "+to_string(n+j+(i-1)*k1)+" 0");
                }
                clauses.push_back(to_string(-1*(n+j+1+i*k1))+" "+to_string(n+1+j+(i-1)*k1)+" "+to_string(-1*(i+1))+" 0");
                clauses.push_back(to_string(n+j+1+i*k1)+" "+to_string(-1*(n+1+j+(i-1)*k1))+" 0");
                if(j>0){
                    clauses.push_back(to_string(n+j+1+i*k1)+" "+to_string(-1*(n+j+(i-1)*k1))+" "+to_string(i+1)+" 0");
                }
                else{
                    clauses.push_back(to_string(n+j+1+i*k1)+" "+to_string(i+1)+" 0");
                }
            }
        }
        for(j=0;j<k2;j++){
            if(j>i){
                clauses.push_back(to_string(-1*(n+j+1+i*k2+n+n*k1))+" 0");
            }
            else if(i!=0 and j!=0){
                if(j>0){
                    clauses.push_back(to_string(-1*(n+j+1+i*k2+n+n*k1))+" "+to_string(n+1+j+(i-1)*k2+n+n*k1)+" "+to_string(n+j+(i-1)*k2+n+n*k1)+" 0");
                }
                clauses.push_back(to_string(-1*(n+j+1+i*k2+n+n*k1))+" "+to_string(n+1+j+(i-1)*k2+n+n*k1)+" "+to_string(-1*(i+1+n+n*k1))+" 0");
                clauses.push_back(to_string(n+j+1+i*k2+n+n*k1)+" "+to_string(-1*(n+1+j+(i-1)*k2+n+n*k1))+" 0");
                if(j>0){
                    clauses.push_back(to_string(n+j+1+i*k2+n+n*k1)+" "+to_string(-1*(n+j+(i-1)*k2+n+n*k1))+" "+to_string(i+1+n+n*k1)+" 0");
                }
                else{
                    clauses.push_back(to_string(n+j+1+i*k2+n+n*k1)+" "+to_string(i+1+n+n*k1)+" 0");
                }
            }
        }
    }
    clauses.push_back(to_string(n+n*k1)+" 0");
    clauses.push_back(to_string(n+n*k1+n+n*k2)+" 0");

    //Write to file
    std::ofstream outputFile("test.satinput");
    outputFile << "p cnf "+to_string(n*(k1+k2))+" "+to_string(clauses.size()) << std::endl;
    for (const std::string& clause : clauses) {
        outputFile << clause << std::endl;
    }
    outputFile.close();

    return 1;
}