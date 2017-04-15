// Win32Project2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>

using namespace std;

typedef struct btb_type {
	unsigned long tag;
	int age;
};
btb_type btb[0x3FFF];
struct btb_type *bptr = &btb[0x3FFF];

void get_branch(unsigned long &pc, string &outcome, ifstream &my_file, double &bcount);

int get_prediction(string &outcome, int *table, unsigned long &a);

void check_prediction(int &prediction, string &outcome, double &rights, double &wrongs, int *table, unsigned long &pc);

void check_btb(unsigned long &pc);

void store_in_btb(unsigned long pc, struct btb_type *bptr);

int main()
{
	string outcome = "t";
	double branchcount = 0;
	double *bcount = 0;
	bcount = &branchcount;
	double rights = 0;
	double wrongs = 0;

	int prediction = 2;
	int a = 0;
	int decision = 0;
	int mask = 0x3FFF;
	unsigned long pc = 0;
	int table[0x3FFF];
	for (int i = 0x00; i < 0x3FFF; i++) {
		table[i] = 2;
	}

	ifstream my_file("trace_gcc.txt");
	get_branch(pc, outcome, my_file, branchcount);
	a = pc >> 2;
	pc = pc & mask; //to limit pc to 0x3fff max value
	prediction = get_prediction(outcome, table, pc);
	cout << prediction << endl;

	for (unsigned long i = 0x3FFF; i < 0; i++) {
		if (btb[i] == pc) {
			check_prediction(prediction, outcome, rights, wrongs, table, pc);
			prediction = get_prediction(outcome, table, pc);
			cout << prediction << endl;
			cout << "Rights: " << rights << endl;
			cout << "Wrongs: " << wrongs << endl;
		}
		else {
			prediction = 0;
			cout << prediction << endl;
			cout << "Rights: " << rights << endl;
			cout << "Wrongs: " << wrongs << endl;
			store_in_btb(pc, &btb);
		}
			

	}

	
	system("pause");
	return 0;
}

void get_branch(unsigned long &pc, string &outcome, ifstream &my_file, double &bcount) {
	if (!my_file) {
		cerr << "System Error!";
	}
	else {
		my_file >> hex >> pc;
		my_file >> outcome;
	}
	bcount++;
}

int get_prediction(string &outcome, int *table, unsigned long &a) {
	int b = 0;
	b = table[a];
	return b;
}

void check_prediction(int &prediction, string &outcome, double &rights, double &wrongs, int *table, unsigned long &pc) {
	switch (prediction) {
	case 0: 
		if (outcome == "n") {
			rights++;
			break;
		}
		else {
			wrongs++;
			table[pc]++;
			break;
		}
	case 1: 
		if (outcome == "n") {
			rights++;
			table[pc]--;
			break;
		}
		else {
			wrongs++;
			table[pc]++;
			break;
		}
	case 2: 
		if (outcome == "n") {
			wrongs++;
			table[pc]--;
			break;
		}
		else {
			rights++;
			table[pc]++;
			break;
		}
	case 3: 
		if (outcome == "n") {
			wrongs++;
			table[pc]--;
			break;
		}
		else {
			rights++;
			break;
		}

	}
}

void check_btb(unsigned long &pc) {

}

void store_in_btb(unsigned long pc, btb_type *first_ptr)
{
	btb_type *last_ptr = first_ptr + 16383;
	//Implementing LRU by calculating minimum age.

	//put a for loop to know the exact address of invalid
	for(int l=)

	btb_type *invalid_ptr = first_ptr + invalid;
	invalid_ptr->tag = pc;
}
