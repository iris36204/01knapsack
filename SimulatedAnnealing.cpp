//SA_二維
#include <iostream>
#include <algorithm>
#include <cmath>
#include <stdlib.h>
#include <time.h>
using namespace std;

int n=15,w=750,countTurn=500;
int weight[15]={70,73,77,80,82,87,90,94,98,106,110,113,115,118,120},
	value[15]={135,139,149,150,156,163,173,184,192,201,210,214,221,229,240};
int BestSolution[15]={0},//最佳解集合 
	BestValue=0,BestWeight=0,
	currentSolution[15]={0};//每輪最佳解集合 
int DP[16][751]={0};
int T0=200,Tn=200,TEnd=40,TUpdate=0.2;

void ChooseNeighbor(){
	int temp[15],Value[15]={0},Weight[15]={0},
		CurrentSolution[15][15]={0};//變化後的解集合 
	copy(BestSolution,BestSolution+15,temp);
	//此回合解的變化，記錄解的weight、value 
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			CurrentSolution[i][j]=temp[j];
		}
		//由最佳解對選擇物品做變化 
		for(int j=0;j<n;j++){
			if(i==j){
				CurrentSolution[i][j]=abs(CurrentSolution[i][j]-1);
			}
			else{
				CurrentSolution[i][j]=CurrentSolution[i][j];
			}
			Weight[i]+=weight[j]*CurrentSolution[i][j];
			Value[i]+=value[j]*CurrentSolution[i][j];
		}
	}
	//計算上一輪最佳解的值 
	int NeighborMaxValue=0,indexCurrentBestSolution=-1;
	for(int i=0;i<n;i++){
		NeighborMaxValue+=value[i]*currentSolution[i];
	}
	//currentSolutionValue當成此輪計算機率的常數 
	double currentSolutionValue=NeighborMaxValue;
	
	for(int i=0;i<n;i++){
		int k=rand()%15;
		double p=exp((double)-abs(currentSolutionValue-(double)Value[k])/(double)Tn);
		double x=(double)rand()/(RAND_MAX + 1.0);
		//若 weight<w 且 ((value大於上輪最大值或此輪目前最大值) 或  (機率大於隨機值))
		//更新最佳值 及 此輪最佳索引值 
		if(Weight[k]<=w&&(Value[k]>NeighborMaxValue||p>x)){
			NeighborMaxValue=Value[k];
			indexCurrentBestSolution=k;
		}
	}
	//更新每輪最佳解集合 
	if(indexCurrentBestSolution!=-1){
		for(int i=0;i<n;i++){
			currentSolution[i]=CurrentSolution[indexCurrentBestSolution][i];
		}
	}
	//更新最佳解集合
	if(Weight[indexCurrentBestSolution]<=w&&Value[indexCurrentBestSolution]>BestValue){
		BestValue=Value[indexCurrentBestSolution];
		BestWeight=Weight[indexCurrentBestSolution];
		for(int j=0;j<n;j++){
			BestSolution[j]=CurrentSolution[indexCurrentBestSolution][j];
		}
	}
	//更新溫度 
	if(Tn>TEnd){
		Tn-=TUpdate;
	}
	else{
		Tn=TEnd;
	}
	
	//DP
	for(int i=0;i<n;i++){
		//計算此次總重量 
		int DPWeight=0;
		for(int j=0;j<n;j++){
			DPWeight+=weight[j]*CurrentSolution[i][j];
		}
		//更新DP 
		for(int j=0;j<=w;j++){
			if(j-DPWeight<0){
				DP[i+1][j]=max(DP[i][j],DP[i+1][j]);
			}
			else{
				DP[i+1][j]=max(DP[i][j],DP[i+1][j]);
				DP[i+1][j]=max(DP[i+1][j],Value[indexCurrentBestSolution]);
			}
		}
	}
	
	for(int i=0;i<n;i++){
		cout<<currentSolution[i]<<" ";
	}
	cout<<"   Weight:"<<Weight[indexCurrentBestSolution]<<"   Value:"<<Value[indexCurrentBestSolution]<<"   DP:"<<DP[n][w]<<endl;
}

int main(){
	srand(time(NULL));
	while(countTurn>0){
		ChooseNeighbor();
		countTurn--;
	}
	
	cout<<endl;
	for(int i=0;i<n;i++){
		cout<<BestSolution[i]<<" ";
	}
	cout<<"   Weight:"<<BestWeight<<"   Value:"<<BestValue<<"   DP:"<<DP[n][w]<<endl;
}
