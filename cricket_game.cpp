/* 
Name: Chivaughn Charles

UWI ID: 815007458

Assignment # and Name: Assignment 4

The program is working only if the amount of bowlers on each team is less than 
or equal to 100.

*/

#include <iostream>
#include <fstream>
#include <time.h> 
#include <windows.h>
#include <stdlib.h>
using namespace std;

ifstream teaminput;

int chooseBowler (int x);
int BatingProb (int x);
int BowlProb (int x);
int bat ();
int bowl ();


struct Players{
	string fname;
	string lname;
	string BatStatus = "Not Out";
	int runs = 0;
	int outs = 0;
	int overs = 0;
};

Players playerTeam1[11];
Players playerTeam2[11];

int Bowlposibilities[100];

int chooseBowler (int old){
	int newBowler;
	newBowler = rand() % 11;
	while (newBowler == old)
    	newBowler = rand() % 11;
    return newBowler;
}


int BatingProb (int runs){
	int i;
	int Batposibilities[100];
	for (i;i<17;i++)
		Batposibilities[i] = 6;
	for (i;i<20;i++)
		Batposibilities[i] = 5;
	for (i;i<40;i++)
		Batposibilities[i] = 4;
	for (i;i<45;i++)
		Batposibilities[i] = 3;
	for (i;i<60;i++)
		Batposibilities[i] = 2;
	for (i;i<75;i++)
		Batposibilities[i] = 1;
	for (i;i<80;i++)
		Batposibilities[i] = 0;
	for (i;i<100;i++)
		Batposibilities[i] = 7;
	return Batposibilities[runs];
	
}

int BowlProb (int b){
	int i;
	for (i;i<5;i++)
		Bowlposibilities[i] = 1;
	for (i;i<8;i++)
		Bowlposibilities[i] = 2;
	for (i;i<100;i++)
		Bowlposibilities[i] = 3;
	return Bowlposibilities[b];
}

string HowOut (int b){
	int i;
	string out[5];
	out[0] = "Bowled Out";
	out[1] = "Caught Out";
	out[2] = "LBW";
	out[3] = "Hit Wicket";
	out[4] = "Stumped";
	return out[b];
}

string RandOut (){
	int b;
	srand(time(NULL));
	string out;
	b = rand() % 5;
	out = HowOut(b);
	return out;
}

int bat (){
	srand(time(NULL));
	int r; int runs;
	runs = rand() % 100;
	r = BatingProb(runs);
	return r;
}

int bowl (){
	int b;
	srand(time(NULL));
	int bwl;
	b = rand() % 100;
	bwl = BowlProb(b);
	return bwl;
}




int main(){
	int wickets = 0; int runs = 0; int Team1runs = 0; int balls = 6; int overs;
	int old = 100; int b; int ballDelay,oversDelay,inningsDelay; int r; int current1 = 0; int current2 = 1; int Extras1 = 0;
	int newBowler; int Team1BatAmt = 2; int Team2BatAmt = 2; int Team1Bowlers[100]; int Team2Bowlers[100]; int T2 = 0; int T1 = 0;
	srand(time(NULL));
	bool team1 = true; bool team2 = false;
	bool bat1 = true; bool bat2 = false;
	cout << "T-YY Cricket Competiton" << endl << endl;
	cout << "Please enter the number of overs: ";
	cin >> overs;
	int overs2 = overs;
	cout << "Please eneter the time delay between balls (in seconds): " ;
	cin >> ballDelay;
	cout << "Please enter the time delay between overs (in seconds): " ;
	cin >> oversDelay;
	cout << "Please enter the time delay between innings (in seconds): " ;
	cin >> inningsDelay;
	cout << endl;
	teaminput.open("Teams.txt");
        if(!teaminput.is_open()){
        	cerr << "error: Teams file failure" << endl;
      	abort();
		}
	string f,l; 
	for (int i=0; i < 11;i++){
		teaminput >> f >> l;
		playerTeam1[i].fname = f;
		playerTeam1[i].lname = l;
	}
	for (int i=0; i < 11;i++){
		teaminput >> f >> l;
		playerTeam2[i].fname = f;
		playerTeam2[i].lname = l;
	}
	
	teaminput.close();
	newBowler = chooseBowler(old);
	playerTeam2[newBowler].overs++;
	Team2Bowlers[T2] = newBowler;
	T2++;
	old = newBowler;
	
	cout << "Team 1 about to bat..." << endl << endl;
	int i = 0; int j = 1;
	while (team1 && overs!=0 && wickets != 10){	
		if (bat1){
			b = bowl();
			Sleep(ballDelay*1000);
			cout << "[" << playerTeam2[newBowler].lname << " to " << playerTeam1[current1].lname << "] ";
			cout << "(" << overs << ", " << balls << ") ";
			if (b == 1) {
				Team1runs++;
				Extras1++;
				cout << "No Ball ";
			} else if (b == 2) {
				Team1runs++;
				Extras1++;
				cout << "Wide ";
			}else if (b == 3){
				balls--;
				runs = bat();
				if (runs == 7){
					cout << "Out! ";
					playerTeam1[current1].BatStatus =  RandOut();
					playerTeam2[newBowler].outs++;
					Team1BatAmt++;
					wickets++;	
					current1++;
					current2++;
					bat1 = false;
					bat2 = true;
				} else {
					if (runs == 0) cout << "No Runs ";
					else if (runs == 1) cout << "Single ";
					else if (runs == 2) cout << "Two runs ";
					else if (runs == 3) cout << "Three runs ";
					else if (runs == 4) cout << "+++ FOUR +++ ";
					else if (runs == 5) cout << "Five runs ";
					else if (runs == 6) cout << "*** SIX *** ";
					playerTeam1[current1].runs = playerTeam1[current1].runs + runs;
					Team1runs = Team1runs + runs;
					if (runs%2!=0){
						if (bat1){
							bat2 = true;
							bat1 = false;
						} else if (bat2){
							bat2 = false;
							bat1 = true;
						}
					}
				}
			} cout << "[Score: " << Team1runs << " for " << wickets << "]" << endl;			
		} else if (bat2){
			b = bowl();
			Sleep(ballDelay*1000);
			cout << "[" << playerTeam2[newBowler].lname << " to " << playerTeam1[current2].lname << "] ";
			cout << "(" << overs << ", " << balls << ") ";
			if (b == 1) {
				Team1runs++;
				Extras1++;
				cout << "No Ball ";
			} else if (b == 2) {
				Team1runs++;
				Extras1++;
				cout << "Wide ";
			}else if (b == 3){
				balls--;
				runs = bat();
				if (runs == 7){
					cout << "Out! ";
					playerTeam1[current2].BatStatus = RandOut();
					playerTeam2[newBowler].outs++;
					Team1BatAmt++;
					wickets++;	
					current1++;
					current2++;
					bat1 = false;
					bat2 = true;
				} else {
					if (runs == 0) cout << "No Runs ";
					else if (runs == 1) cout << "Single ";
					else if (runs == 2) cout << "Two runs ";
					else if (runs == 3) cout << "Three runs ";
					else if (runs == 4) cout << "+++ FOUR +++ ";
					else if (runs == 5) cout << "Five runs ";
					else if (runs == 6) cout << "*** SIX *** ";
					playerTeam1[current2].runs = playerTeam1[current2].runs + runs;
					Team1runs = Team1runs + runs;
					if (runs%2!=0){
						if (bat1){
							bat2 = true;
							bat1 = false;
						} else if (bat2){
							bat2 = false;
							bat1 = true;
						}
					}
				}
			
			}
		cout << "[Score: " << Team1runs << " for " << wickets << "]" << endl;		
		}
		if (balls == 0){
			cout << "       End of over #" << overs << endl << endl;
			overs--;
			Sleep(oversDelay*1000);
			}
		if ((balls == 0) && (overs != 0)){
			balls = 6;
			newBowler = chooseBowler(old);
			playerTeam2[newBowler].overs++;
			old = newBowler;
			Team2Bowlers[T2] = newBowler;
			T2++;
			if (bat1) {
				bat1 = false;
				bat2 = true;
			} else if (bat2){
				bat1 = true;
				bat2 = false;
			}
		}
	}
	int Team2RunsToWin = Team1runs + 1;
	cout << "End of inning." << endl;
	cout << "Team 1 scored " << Team1runs << endl;
	cout << "Team 2 must score " << Team2RunsToWin << " to win." << endl << endl;
	Sleep(inningsDelay*1000);
	newBowler = chooseBowler(old);
	playerTeam1[newBowler].overs++;
	Team1Bowlers[T1] = newBowler;
	T1++;
	old = newBowler;
	balls = 6;
	cout << "Team 2 about to bat..." << endl << endl;
	team1 = false; team2 = true;
	bat1 = true;  bat2 = false;
	current1 = 0; current2 = 1; int Extras2 = 0; int wickets2 = 0; int Team2runs = 0;
	while (team2 && overs2!=0 && wickets2 != 10 && Team2runs < Team2RunsToWin){	
		if (bat1){
			b = bowl();
			Sleep(ballDelay*1000);
			cout << "[" << playerTeam1[newBowler].lname << " to " << playerTeam2[current1].lname << "] ";
			cout << "(" << overs2 << ", " << balls << ") ";
			if (b == 1) {
				Team2runs++;
				Extras2++;
				cout << "No Ball ";
			} else if (b == 2) {
				Team2runs++;
				Extras2++;
				cout << "Wide ";
			}else if (b == 3){
				balls--;
				runs = bat();
				if (runs == 7){
					cout << "Out! ";
					playerTeam2[current1].BatStatus = RandOut();
					playerTeam1[newBowler].outs++;
					Team2BatAmt++;
					wickets2++;	
					current1++;
					current2++;
					bat1 = false;
					bat2 = true;
				} else {
					if (runs == 0) cout << "No Runs ";
					else if (runs == 1) cout << "Single ";
					else if (runs == 2) cout << "Two runs ";
					else if (runs == 3) cout << "Three runs ";
					else if (runs == 4) cout << "+++ FOUR +++ ";
					else if (runs == 5) cout << "Five runs ";
					else if (runs == 6) cout << "*** SIX *** ";
					playerTeam2[current1].runs = playerTeam2[current1].runs + runs;
					Team2runs = Team2runs + runs;
					if (runs%2!=0){
						if (bat1){
							bat2 = true;
							bat1 = false;
						} else if (bat2){
							bat2 = false;
							bat1 = true;
						}
					}
				}
			} cout << "[Score: " << Team2runs << " for " << wickets2 << "]" << endl;			
		} else if (bat2){
			b = bowl();
			Sleep(ballDelay*1000);
			cout << "[" << playerTeam1[newBowler].lname << " to " << playerTeam2[current2].lname << "] ";
			cout << "(" << overs2 << ", " << balls << ") ";
			if (b == 1) {
				Team2runs++;
				Extras2++;
				cout << "No Ball ";
			} else if (b == 2) {
				Team1runs++;
				Extras1++;
				cout << "Wide ";
			}else if (b == 3){
				balls--;
				runs = bat();
				if (runs == 7){
					cout << "Out! ";
					playerTeam2[current2].BatStatus = RandOut();
					playerTeam1[newBowler].outs++;
					Team2BatAmt++;
					wickets2++;	
					current1++;
					current2++;
					bat1 = false;
					bat2 = true;
				} else {
					if (runs == 0) cout << "No Runs ";
					else if (runs == 1) cout << "Single ";
					else if (runs == 2) cout << "Two runs ";
					else if (runs == 3) cout << "Three runs ";
					else if (runs == 4) cout << "+++ FOUR +++ ";
					else if (runs == 5) cout << "Five runs ";
					else if (runs == 6) cout << "*** SIX *** ";
					playerTeam2[current2].runs = playerTeam2[current2].runs + runs;
					Team2runs = Team2runs + runs;
					if (runs%2!=0){
						if (bat1){
							bat2 = true;
							bat1 = false;
						} else if (bat2){
							bat2 = false;
							bat1 = true;
						}
					}
				}
			
			}
		cout << "[Score: " << Team2runs << " for " << wickets2 << "]" << endl;		
		}
		if (balls == 0){
			cout << "       End of over #" << overs2 << endl << endl;
			overs2--;
			Sleep(oversDelay*1000);
			}
		if ((balls == 0) && (overs2 != 0)){
			balls = 6;
			newBowler = chooseBowler(old);
			playerTeam1[newBowler].overs++;
			Team1Bowlers[T1] = newBowler;
			T1++;
			old = newBowler;
			if (bat1) {
				bat1 = false;
				bat2 = true;
			} else if (bat2){
				bat1 = true;
				bat2 = false;
			}
		}
	}
	cout << endl;
	if (Team2runs >= Team2RunsToWin)
		cout << "Team 2 WON!" << endl << endl;
	else cout << "Team 1 WON!" << endl << endl;
		
	cout << "          SCOREBOARD" << endl << endl;
	cout << "Team 1 Batting" << endl << endl;
	for (int i = 0; i < Team1BatAmt; i++)
		cout << playerTeam1[i].fname << " " << playerTeam1[i].lname << " " << playerTeam1[i].BatStatus <<  " with " << playerTeam1[i].runs << " runs" << endl;
	cout << "Extras: " << Extras1 << endl << endl;
	
	cout << "Team 2 Bowling" << endl << endl;
	for (int i=0; i < T2; i++){
		cout << playerTeam2[Team1Bowlers[i]].fname << " " << playerTeam2[Team2Bowlers[i]].lname << " " << playerTeam2[Team2Bowlers[i]].overs <<" overs, " << playerTeam2[Team2Bowlers[i]].outs << " wickets" << endl;
	}
	cout << endl;
	cout << "Team 2 Batting" << endl << endl;
	for (int i = 0; i < Team2BatAmt; i++)
		cout << playerTeam2[i].fname << " " << playerTeam2[i].lname << " " << playerTeam2[i].BatStatus << " with " << playerTeam2[i].runs << " runs" << endl;
	cout << "Extras: " << Extras2 << endl << endl;
	
	cout << "Team 1 Bowling" << endl << endl;
	for (int i=0; i < T1; i++){
		cout << playerTeam1[Team1Bowlers[i]].fname << " " << playerTeam1[Team1Bowlers[i]].lname << " " << playerTeam1[Team1Bowlers[i]].overs <<" overs, " << playerTeam1[Team1Bowlers[i]].outs << " wickets" << endl;
	}
	
	return 0;
}
