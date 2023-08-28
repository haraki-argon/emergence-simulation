// Ant Emergence Simulator
// Based on https://www.bilibili.com/video/BV1eG411u7UJ/
// Author: Haraki

#include<bits/stdc++.h>
using namespace std;
const int MAXAnt=10000;
int type[MAXAnt]; // Type->i: 1 for Workers, 2 for Caretakers, 3 for Soldiers, 4 for Gatherers
int meetTimes[MAXAnt][4];// i,j: the other ants i_th ant have met. j for Type(1234)

int main(){
	
	// Initialize rand()
	srand((unsigned int)time(NULL));
	
	// Input the number of 4 kinds of ants.
	int antNum[4],antTotal=0;
	for(int i=0;i<4;i++){
		cin>>antNum[i];
		for(int j=0;j<antNum[i];j++) type[j+antTotal]=i+1; // Set the type.
		antTotal+=antNum[i];
	}
	
	// Start to simulate:
	int round=0;
	while(1){
		round++;
		
		// Several Meet
		int times=1000; // the 100 there can be changed.
		for(int i=1;i<=times;i++){
			int randA=rand()%antTotal;
			int randB=rand()%antTotal;
			meetTimes[randA][type[randB]-1]++;
			meetTimes[randB][type[randA]-1]++;
		}
		
		// For each ant, decide to change or not.
		for(int i=0;i<antTotal;i++){
			// Randomly change, based on meeted ants
			if(meetTimes[i][0]+meetTimes[i][1]+meetTimes[i][2]+meetTimes[i][3]<10)continue;
			int maxMeetTimes=0;  
			int pos[4]; //posibility
			int posAll=0;
			for(int j=0;j<4;j++)maxMeetTimes=max(maxMeetTimes,meetTimes[i][j]);
			for(int j=0;j<4;j++){
				pos[j]=maxMeetTimes-meetTimes[i][j];
				posAll+=pos[j];
			}
			if(posAll==0)continue;
			int rnd=rand()%posAll;
			for(int j=0;j<4;j++){
				if(rnd<pos[j]){
					type[i]=j+1;
					break;
				}
				rnd-=pos[j];
			}
			for(int j=0;j<4;j++)meetTimes[i][j]=0;
		}
		
		// Show the type of ants now
		int typeNum[4]={0,0,0,0};
		for(int i=0;i<antTotal;i++)typeNum[type[i]-1]++;
		for(int i=0;i<4;i++)cout<<typeNum[i]<<" ";
		
		// Calculate the variance
		double variance=0,average=0;
		for(int i=0;i<4;i++)average+=typeNum[i];
		average/=4;
		for(int i=0;i<4;i++)variance+=(typeNum[i]-average)*(typeNum[i]-average);
		variance/=4;
		cout<<"s^2 = "<<variance<<" "<<endl;
		system("pause>nul");
	}
}
