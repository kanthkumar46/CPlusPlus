/* 
 * PatternGenerator.cpp 
 * 
 * Version: 
 *     $Id$ 
 * 
 * Revisions: 
 *     $Log$ 
 */

#include <iostream>
using namespace std;

/**
 * This program generates the below pattern recursively
 * for the number of input lines.
 *           *   
 *     	   *   *   
 *  	 *   *   *   
 *     *   *   *   *   
 *       *   *   *   
 *         *   *   
 *           *  
 *
 * @author      Kanth
 */

class PatternGenerator{
private:
	int j,k;
public:
	void generatePatternTop(int,int);
	void generatePatternBottom(int,int);
};

/**
 * function to generate the top portion of the
 * Diamond Pattern.
 * 
 * @param   n 	number of lines 
 * @param   i   counter variable
 */

void PatternGenerator::generatePatternTop(int n,int i){
	if(i==n)
		return;
	else{
		for(k=n;k>i;k--){
			cout<<"  ";
		}
		for(j=0;j<i+1;j++){
			cout<<"*"<<"   ";
		}
		cout<<endl;
		generatePatternTop(n,++i);
	}
}

/**
 * function to generate the bottom portion of the
 * Diamond Pattern.
 * 
 * @param   n 	number of lines 
 * @param   i   counter variable
 */

void PatternGenerator::generatePatternBottom(int n,int i){
	int j,k;
	if(i==0)
		return;
	else{
		for(k=i-1;k<n;k++){
			cout<<"  ";
		}
		for(j=0;j<i;j++){
			cout<<"*"<<"   ";
		}
		cout<<endl;
		generatePatternBottom(n,--i);
	}
}

/**
 * The main program.
 *
 */

int main(){
	PatternGenerator pg;
	int n;
	// Input the number of lines the pattern to be generated
	cout<<"Enter the number of lines : ";
	cin>>n;
	pg.generatePatternTop(n,0);  //generates top part of Diamond pattern
	pg.generatePatternBottom(n,n-1);  //generates bottom part of Diamond pattern
	return 0;
}
