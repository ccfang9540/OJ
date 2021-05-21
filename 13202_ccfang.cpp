#include <iostream>
#include <iomanip>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WEIGHT 1000000

using namespace std;

int weight[101][101];
int graph[101][101];
int nextNode[101][101];
int nodeNumber;

void compare_path(int i, int j, int k){

    int s=i, t=j;
    int w1=s,w2=s;
    while( true ){
        w1=nextNode[w1][t];
        w2=nextNode[w2][k];
        if(w1>w2){
            nextNode[i][j] = nextNode[i][k];
            break;
        } else if(w1<w2) {
            break;
        } else {

        }
    }
}

void solve(){
    for(int k=0; k<nodeNumber; k++){
        for(int i=0; i<nodeNumber; i++){
            for(int j=0; j<nodeNumber; j++){
                if( graph[i][k] + graph[k][j] < graph[i][j] ){
                    graph[i][j] = graph[i][k] + graph[k][j];
                    nextNode[i][j] = nextNode[i][k];
                } else if (graph[i][k] + graph[k][j] == graph[i][j]){ //  Equal length
                    if( k!=i && k!=j )
                        compare_path(i,j,k);
                } else {
                    // nothing
                }

            }
        }
    }
}


void find_path(int s, int t)
{
    for (int i=s; i!=t; i=nextNode[i][t])
        cout << i<<"->";
    cout << t << endl;
}


void printOutput(){

    for(int i=0; i<nodeNumber; i++){
        for(int j=0; j<nodeNumber; j++){
            if( i!=j && graph[i][j]<MAX_WEIGHT ){
                cout << "Path(" << i << ',' << j << "):";
                find_path(i,j);
                cout << "Difficulty:" << graph[i][j] << endl;

            }
        }
    }

    double num;
    for(int i=0; i<nodeNumber; i++){
        double cen=0;
        for(int j=0; j<nodeNumber; j++){
            if(graph[j][i]!=0 && graph[j][i]<MAX_WEIGHT){
                num=1.0/graph[j][i];
                cen+=num;
            }
        }
        cout << "Centrality(" << i << "):";
        cout << fixed << showpoint;
        cout << setprecision(3);
        cout << cen << endl;
    }

}

int main()
{

    #ifndef ONLINE_JUDGE
	freopen ("13202_sampleIn.txt","r",stdin);
	freopen ("output.txt","w",stdout);
	#endif

    int value;
    cin >> nodeNumber;

    for(int i=0; i<nodeNumber; i++){
        for(int j=0; j<nodeNumber; j++){
            cin >> value;
            if( value == 0 && i!=j )
                weight[i][j] = MAX_WEIGHT;
            else if( value == 0 && i!=j )
                weight[i][j] = 0;
            else
                weight[i][j] = value;
        }
    }

    for(int i=0; i<nodeNumber; i++){
        for(int j=0; j<nodeNumber; j++){
            graph[i][j] = weight[i][j];
            nextNode[i][j] = j;
        }
    }

    solve();
    printOutput();


    return 0;
}
