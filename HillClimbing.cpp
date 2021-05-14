//爬山演算法_一維
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int n=15,w=750,countTurn=500,Judge;
int weight[15]={70,73,77,80,82,87,90,94,98,106,110,113,115,118,120},
	value[15]={135,139,149,150,156,163,173,184,192,201,210,214,221,229,240};
int BestSolution[15]={0},//最佳解集合 
	BestValue=0,BestWeight=0;
int DP[16][751]={0};

void ChooseNeighbor(){
	int temp[15];
	Judge=0;
	copy(BestSolution,BestSolution+15,temp);
	for(int i=0;i<n;i++){
		int Value=0,Weight=0,CurrentSolution[15];
		copy(temp,temp+15,CurrentSolution);
		//由最佳解對選擇物品做變化 
		for(int j=0;j<n;j++){
			if(i==j){
				CurrentSolution[j]=abs(CurrentSolution[j]-1);
			}
			else{
				CurrentSolution[j]=CurrentSolution[j];
			}
			if(Weight+weight[j]*CurrentSolution[j]>=w){
				break;
			}
			else{
				Weight+=weight[j]*CurrentSolution[j];
				Value+=value[j]*CurrentSolution[j];
			}
		}
		//計算此次總重量 
		int DPWeight=0;
		for(int j=0;j<n;j++){
			DPWeight+=weight[j]*CurrentSolution[j];
		}
		//更新DP 
		for(int j=0;j<=w;j++){
			if(j-DPWeight<0){
				DP[i+1][j]=max(DP[i][j],DP[i+1][j]);
			}
			else{
				DP[i+1][j]=max(DP[i][j],DP[i+1][j]);
				DP[i+1][j]=max(DP[i+1][j],Value);
			}
		}
		//更新最佳解 
		if(Weight<=w&&Value>BestValue){
			BestValue=Value;
			BestWeight=Weight;
			copy(CurrentSolution,CurrentSolution+15,BestSolution);
			Judge=1;
		}
	}
}

int main(){
	while(countTurn>0){
		ChooseNeighbor();
		if(Judge==0){
			break;
		}
		countTurn--;
		for(int i=0;i<n;i++){
			cout<<BestSolution[i]<<" ";
		}
		cout<<"   Weight:"<<BestWeight<<"   Value:"<<BestValue<<"   DP:"<<DP[n][w]<<endl;
	}
}
