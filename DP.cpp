#include <iostream>
#include <algorithm>
using namespace std;

int main(){
	int n=15,w=750;
	int weight[n]={70,73,77,80,82,87,90,94,98,106,110,113,115,118,120},
		value[n]={135,139,149,150,156,163,173,184,192,201,210,214,221,229,240};
	int DP[n+1][w+1]={0};
	
	for(int i=0;i<n;i++){
		for(int j=0;j<=w;j++){
			if(j-weight[i]<0){
				DP[i+1][j]=DP[i][j];
			}
			else{
				DP[i+1][j]=max(DP[i][j],DP[i][j-weight[i]]+value[i]);
			}	
		}
	}
	
	cout<<DP[n][w];
}
