#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main(){
    //input
    int n,m,k1,k2;
    cin>>n,m,k1,k2;
    vector<int> adj[n];
    int i,j,k,x,y;
    for(i=0;i<n;i++){
        adj[i]=vector<int>();
    }
    for(i=0;i<m;i++){
        cin>>x>>y;
        adj[x-1].push_back(y-1);
        adj[y-1].push_back(x-1);
    }

    //clauses
    vector<string> clauses={};
    string temp;
    //existince
    for(i=0;i<k1;i++){
        temp="";
        for(j=0;j<n;j++){
            temp+=(to_string(-1*(j*k1+i))+" ");
        }
        clauses.push_back(temp+"0");
    }
    for(i=0;i<k2;i++){
        temp="";
        for(j=0;j<n;j++){
            temp+=(to_string(-1*(j*k2+i+k1*n))+" ");
        }
        clauses.push_back(temp+"0");
    }
    //uniqueness
    for(i=0;i<n;i++){
        for(j=0;j<k1;j++){
            for(k=0;k<k1;k++){
                if(k!=j){
                    clauses.push_back(to_string(i*k1+j)+" "+to_string(i*k1+k)+" 0");
                }
            }
            for(k=0;k<n;k++){
                if(i!=k){
                    clauses.push_back(to_string(i*k1+j)+" "+to_string(k*k1+i)+" 0");
                }
            }
            for(j=0;j<k2;j++){
                clauses.push_back(to_string(i*k1+j)+" "+to_string(i*k2+j+n*k1)+" 0");
            }
        }
        for(j=0;j<k2;j++){
            for(k=0;k<k2;k++){
                if(k!=j){
                    clauses.push_back(to_string(k1*n+i*k2+j)+" "+to_string(k1*n+i*k2+k)+" 0");
                }
            }
            for(k=0;k<n;k++){
                if(i!=k){
                    clauses.push_back(to_string(k1*n+i*k2+j)+" "+to_string(k1*n+k*k2+i)+" 0");
                }
            }
            for(j=0;j<k2;j++){
                clauses.push_back(to_string(k1*n+i*k2+j)+" "+to_string(i*k1+j)+" 0");
            }
        }
    }
    //connectivity
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(find(adj[i].begin(),adj[i].end(),j)==adj[j].end()){
                for(k=0;k<k1;k++){
                    for(int l=0;l<k1;l++){
                        clauses.push_back(to_string(i*k1+k)+" "+to_string(j*k1+l)+" 0");
                    }
                }
                for(k=0;k<k2;k++){
                    for(int l=0;l<k2;l++){
                        clauses.push_back(to_string(k1*n+i*k2+k)+" "+to_string(k1*n+j*k2+l)+" 0");
                    }
                }
            }
        }
    }

    //write to file
    

    return 1;
}
