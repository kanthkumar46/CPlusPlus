/*
 * Clock.cpp
 * 
 * Version :
 *  $Id$
 *
 * Revisions:
 *  $log$
 */

#include "Solver.h"
#include <list>
/**
 * 
 *	Sam Lloyd's Sliding Block Problem
 *  This program finds all the possible configurations in order to move all the blocks 
 *	to acheive in Intial Cong=figuration the Goal configuration in box with labelled blocks.
 *  Input : The world is a box of labelled square bolocks. The current configuration 
 * 	is the lable and position in the box. 
 * 	Output : The goal configuration or the desired configuration by moving each block once.
 * 	Note : The input may be from a text file in a proper foramt or 
 *			from a standard input . Output can be given to a file or a standard output.
 * 
 *  @author Dayanand Kanth
 *  @author Hanagal Madhusudan  
 *  @author Bharadwaj Suman
 */

/*
 * Class
 * Lloyd
 * Defines the follwoing required elements for the Lloyd program
 */
class Lloyd{
private:
	char **intialConfig;
public:
	static char **goalConfig;
	static int row, col;
	static bool standardOutput;
	ofstream outfile;

	//Method 1
	void readInputFromFile(string, Solver<char**>&);
	//Method 2
	void readInputfromConsole(Solver<char**>&);
	//Method 3
	void solve(Solver<char**>&);
	//Method 4
	bool isEqual(char** , char**);
	//Method 5
	bool hasAlreadySeen(char**, Solver<char**>&);
	//Method 6
	char** moveLeft(char**,int,int);
	//Method 7
	char** moveRight(char**,int,int);
	//Method 8
	char** moveUp(char**,int,int);
	//Method 9
	char** moveDown(char**,int,int);
	//Method 10
	void printConfiguration(Solver<char**>&);
	//Method 11
	void writeConfiguration(Solver<char**>&);
	//Method 12 
	list<char**> generateNextConfigurations(char**);
};

/*
 * Global Declarations.
 * goalConfig
 * row of the box
 * col of the box
 */
char** Lloyd::goalConfig;
int Lloyd::row;
int Lloyd::col;
bool Lloyd::standardOutput = false;

/*
 * readInputFromFile
 * This function will help in reading the input from the file which contains a standard
 * Input format :
 * Input :  Format from a txt file  
 * 		    1st line : row <space> col
 *			2nd line : matrix[row][col] : Given or Initial Configuration
 *			<space>or<newLine>
 *			3rd line : matrxi[row][col] : Desired or Goal Configuration
 * @param  inputFileName
 * @param  &solver of Solve type
 */
void Lloyd::readInputFromFile(string inputFileName, Solver<char**>& solver){
	ifstream infile(inputFileName.c_str());

	if(!infile){
		cout << "Error opening Input File !!!" << endl ;
		return;
	}

	string line;
	int lineCount =0, rowCount=0;
	char **arr;
	while(getline(infile,line)){		
		lineCount++;
		if(lineCount ==1){

			//Getting the width and height
			string width = line.substr(0,line.find(' ',0));
			string height = line.substr(line.find(' ',0)+1);
			for(int i=0;i<width.length();i++){
				if(!isdigit(width[i])){
					cout<<"invalid input "<<endl;
					exit(0);
				}
			}
			for(int i=0;i<height.length();i++){
				if(!isdigit(height[i])){
					cout<<"invalid input "<<endl;
					exit(0);
				}
			}
			col = atoi(width.c_str());
			row = atoi(height.c_str());
			intialConfig = new char*[row];
			goalConfig = new char*[row];

			//Genereate the matrix for the inital and goal configuration
			for(int i=0;i<row;i++){
				intialConfig[i] = new char[col];
				goalConfig[i] = new char[col];
			}
			arr = intialConfig;
		}
		else{

			// Checks for the invalid input , if the no of rows either in inital or goal configuration
			// are more than the given no of rows
			// Checks for the invalid input , if the no of rows either in initial or goal configuration
			// are more than the given no of columns

			if(lineCount > row*2+2){
				cout<<"invalid input "<<endl;
				exit(0);
			}
			if(line.length() == 0 && rowCount<row){
				cout<<"invalid input "<<endl;
				exit(0);
			}
			if(line.length() == col && rowCount<row){
				for(int i=0;i<line.length();i++)
					arr[rowCount][i] = line[i];
				rowCount++;
			}
			if(line.length() ==0 && rowCount == row){
				rowCount = 0;
				arr = goalConfig;
			}
			if(line.length() != 0 && line.length()!= col){
				cout<<"invalid input "<<endl;
				exit(0);
			}
		}
	}

	solver.config_queue.push_back(intialConfig);
	infile.close();
}    	

/*
 * readInputfromConsole
 * This function will help in reading the input from the standard input
 * i.e. keyboard which contains a standard
 * Input format :
 * Input :  Format from a standard input  
 * 		    1st line : row <space> col
 *			2nd line : matrix[row][col] : Given or Initial Configuration
 *			<space>or<newLine>
 *			3rd line : matrxi[row][col] : Desired or Goal Configuration
 *
 * @param  &solver of Solve type
 */
void Lloyd::readInputfromConsole(Solver<char**>& solver){
	cout<<"Enter box width :";
	//Width or Col
	cin>>col;
	cout<<"Enter box height :";
	//Height or row
	cin>>row;

	//Create a initial configuration
	intialConfig = new char*[row];
	//Create a goal configuration
	goalConfig = new char*[row];

	//Generate the matrix for initial and goal configuration
	for(int i=0;i<row;i++){
		intialConfig[i] = new char[col];
		goalConfig[i] = new char[col];
	}
	
	string line;
	
	//Taking the Initial Configuration from the user
	cout<<"Enter Initial Configuration :"<<endl;
	for(int i=0;i<row;i++){
		cin>>line;
		if(line.length()!=col){
			cout<<"invalid input "<<endl;
			exit(0);
		}
		else{
			for(int j=0;j<line.length();j++)
				intialConfig[i][j] = line[j];
		}
	}
	
	//Taking the goal configuartion from the user
	cout<<"Enter goal Configuration :"<<endl;
	for(int i=0;i<row;i++){
		cin>>line;
		if(line.length()!=col){
			cout<<"invalid input "<<endl;
			exit(0);
		}
		else{
			for(int j=0;j<line.length();j++)
				goalConfig[i][j] = line[j];
		}
	}
	
	//Solve
	solver.config_queue.push_back(intialConfig);
}


/*
 * generateNextConfigurations
 * The configuration here in lloyd is a array
 * This function solves the puzzle to match the desired configuration
 * If the current configutation is not equal to goal configuration 
 * Move the blocks right , left , up or down to get to the desired configuration
 * If the block is to the left most boundary move right
 * If the block is to the right most boundary move left
 * If the block is to the upper most boundary move down
 * If the blcok is to the lower most boundary move up
 * Prints and writes the current configuration to the standard output or 
 * to the file
 * Prints and writes the goal configuration to the standard output or to the file.
 * Already seen configuration are not recorded.
 *
 * @param current_config
 */

list<char**> Lloyd::generateNextConfigurations(char** current_config){
	list<char**> newConfigs;

	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			if(current_config[i][j] == '.'){
				if((i==0 || i==row-1) && (j==0 || j==col-1)){

					// if left bundary move right 
					if(j==0 && col>1){
						char **next_config = moveRight(current_config,i,j);
						newConfigs.push_back(next_config);
					}

					// if right boundary move left
					else if(j==col-1 && col>1){
						char **next_config = moveLeft(current_config,i,j);
						newConfigs.push_back(next_config);
					}

					//if upper boundary move down
					if(i==0 && row>1){
						char **next_config = moveDown(current_config,i,j);
						newConfigs.push_back(next_config);
					}

					//if lower boubdary move up
					else if(i==row-1 && row>1){
						char **next_config = moveUp(current_config,i,j);
						newConfigs.push_back(next_config);
					}
				}
				else if(i>0 && i<row-1 && j>0 && j< col-1){
					//Push into the configuration if not seen.
					char **next_config = moveLeft(current_config,i,j);
					newConfigs.push_back(next_config);
					
					next_config = moveRight(current_config,i,j);
					newConfigs.push_back(next_config);
					
					next_config = moveUp(current_config,i,j);
					newConfigs.push_back(next_config);
					
					next_config = moveDown(current_config,i,j);
					newConfigs.push_back(next_config);
				}
				else{
					if(i==0 || i==row-1){

						//Push into the configuration if not seen.
						char **next_config = moveLeft(current_config,i,j);
						newConfigs.push_back(next_config);

						next_config = moveRight(current_config,i,j);
						newConfigs.push_back(next_config);

						if(i==0 && row>1){
							next_config = moveDown(current_config,i,j);
							newConfigs.push_back(next_config);
						}
						else if(i==row-1 && row>1){
							//Push into the configuration if not seen.
							next_config = moveUp(current_config,i,j);
							newConfigs.push_back(next_config);
						}
					}
					if(j==0 || j==col-1){
						//Push into the configuration if not seen.
						char **next_config = moveUp(current_config,i,j);
						newConfigs.push_back(next_config);

						next_config = moveDown(current_config,i,j);
						newConfigs.push_back(next_config);

						if(j==0 && col>1){
							next_config = moveRight(current_config,i,j);
							newConfigs.push_back(next_config);
						}
						else if(j==col-1 && col>1){
							next_config = moveLeft(current_config,i,j);
							newConfigs.push_back(next_config);
						}
					}
				}
			}
		}
	}
	return newConfigs;
}


/*
 * solve
 * This function Prints and writes the goal configuration to 
 * the standard output or to the file
 * Prints Initial Configuration
 * Writes the goal Configuration
 * If queue is empty then no possible solution are found
 * Already seen configuration are not recorded.
 *
 * @param  &solver of Solve type
 */
void  Lloyd::solve(Solver<char**>& solver){
	if(standardOutput){
		cout<<"Initial Configuration :"<<endl;
		printConfiguration(solver);
	}
	else{
		outfile << "Initial Configuration :\n";
		writeConfiguration(solver);
	}

	char** current_config = solver.config_queue.front();
	while(!isEqual(current_config,goalConfig)){

		solver.seen_queue.push_back(current_config);
		solver.config_queue.erase(solver.config_queue.begin());

		list<char**> newConfigs = generateNextConfigurations(current_config);
		int listSize = (int)newConfigs.size();

		for(int i=0;i<listSize;i++){
			char** next_config = newConfigs.front();
			newConfigs.pop_front();
			if(!hasAlreadySeen(next_config,solver))
				solver.config_queue.push_back(next_config);
		}

		if((int)solver.config_queue.size() == 0){
			cout<<"\n No possbile solutions found !!!"<<endl;
			exit(0);
		}

		current_config = solver.config_queue.front();
		
		if(standardOutput){
			//Print the current configuration
			cout<<"current Configuration :"<<endl;
			printConfiguration(solver);
		}
		else{
			//Write the current configuration to the file
			outfile << "current Configuration :\n";
			writeConfiguration(solver);
		}
	}
	if(standardOutput){
		//Print the goal configuration
		cout<<"goal Configuration :"<<endl;
		printConfiguration(solver);
	}
	else{
		//Write the goal configuration to the file
		outfile << "goal Configuration :\n";
		writeConfiguration(solver);
	}
}

/*
 * printConfiguration
 * This function prints the goal configuration onto standard output or screen
 *
 * @param  &solver of Solve type
 */
void Lloyd::printConfiguration(Solver<char**>& solver){
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			cout<<solver.config_queue.front()[i][j]<<" ";
		}
		cout<<endl;
	}
}

/*
 * writeConfiguration
 * This function prints the goal configuration to a file
 *
 * @param  &solver of Solve type
 */
void Lloyd::writeConfiguration(Solver<char**>& solver){
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			outfile<<solver.config_queue.front()[i][j]<<" ";
		}
		outfile<<"\n";
	}
}

/*
 * moveLeft
 * This function helps to move the blocks to left
 *
 * @param   current_config
 * @param   m,n positon of . or blank
 */
char** Lloyd::moveLeft(char** current_config,int m, int n){
	char **next_config;
	next_config = new char*[row];
	for(int i=0;i<row;i++)
		next_config[i] = new char[col];
	for(int i=0;i<row;i++)
		for(int j=0;j<col;j++){
			next_config[i][j] = current_config[i][j];
	}
	next_config[m][n] = next_config[m][n-1];
	next_config[m][n-1] = '.';
	return next_config;
}

/*
 * moveRight
 * This function helps to move the blocks to right
 *
 * @param   current_config
 * @param   m,n positon of . or blank
 */
char** Lloyd::moveRight(char** current_config,int m, int n){
	char **next_config;
	next_config = new char*[row];
	for(int i=0;i<row;i++)
		next_config[i] = new char[col];
	for(int i=0;i<row;i++)
		for(int j=0;j<col;j++){
			next_config[i][j] = current_config[i][j];
	}
	next_config[m][n] = next_config[m][n+1];
	next_config[m][n+1] = '.';
	return next_config;
}


/*
 * moveUp
 * This function helps to move the blocks up
 *
 * @param   current_config
 *@param   m,n positon of . or blank
 */
char** Lloyd::moveUp(char** current_config,int m, int n){
	char **next_config;
	next_config = new char*[row];
	for(int i=0;i<row;i++)
		next_config[i] = new char[col];
	for(int i=0;i<row;i++)
		for(int j=0;j<col;j++){
			next_config[i][j] = current_config[i][j];
	}
	next_config[m][n] = next_config[m-1][n];
	next_config[m-1][n] = '.';
	return next_config;
}


/*
 * moveDown
 * This function helps to move the blocks down
 *
 * @param   current_config
 * @param   m,n positon of . or blank
 */
char** Lloyd::moveDown(char** current_config,int m, int n){
	char **next_config;
	next_config = new char*[row];
	for(int i=0;i<row;i++)
		next_config[i] = new char[col];
	for(int i=0;i<row;i++)
		for(int j=0;j<col;j++){
			next_config[i][j] = current_config[i][j];
	}
	next_config[m][n] = next_config[m+1][n];
	next_config[m+1][n] = '.';
	return next_config;
}

/*
 * isEqual
 * This function helps to check weather each block of 
 * initial configuration is equal to the desired confiuration. 
 * Checks weather we have achieved the desired or goal configuration
 *
 * @param   current_config
 * @param   goalConfig
 */
bool Lloyd::isEqual(char** current_config, char** goalConfig){
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			if(current_config[i][j] != goalConfig[i][j])
				return false;
		}
	}
	return true;
}

/*
 * hasAlreadySeen
 * This function will check if the configuraton is already seen
 * If seen return true or false
 * 
 *	@param next_config of type clock
 *  @param solver of type solver
 */
bool Lloyd::hasAlreadySeen(char** next_config, Solver<char**>& solver){
	for (int i = 0; i < solver.config_queue.size(); ++i){
		if(isEqual(solver.config_queue[i], next_config))
			return true;
	}
	for (int i = 0; i < solver.seen_queue.size(); ++i){
		if(isEqual(solver.seen_queue[i], next_config))
			return true;
	}
	return false;
}

/*
 * printInputFormat
 * The Function will print the format, arguments has 
 * to be supplied.
 */

void printInputFormat(){
	cout<<"\nInput Format Example: .a/.out file.txt -"<<endl;
	cout<<"file.txt : Input file containing the puzzle to be solved"<<endl;
	cout<<"- :  Output will be displayed on console"<<endl;
	cout<<"\nNote, if - is given as argument instead of input file then"<<endl;
	cout<<"input has to be supplied from console"<<endl;
    cout<<"\nNote, if filename is specified as argument instead of - then"<<endl;
	cout<<"output will be written to the file specified\n"<<endl;
}

/*
 * 
 * @param argc
 * @param *argv[]
 */
int main(int argc, char *argv[]){

	Lloyd llyod;
	
	//Create a solver
	Solver<char**> solver; 

	/*
	 * Checking weather the entered arguments are correct or not.
	 * Condition : if number of arguments is less than 3 then invalid
	 */
	if(argc == 3){
		string inputFileName = argv[1];
		string outputFileName = argv[2];

		// If the input or arguments is "-" we have to take the input from the
		//	standard input
		if(inputFileName=="-")
			llyod.readInputfromConsole(solver);
		else
			llyod.readInputFromFile(inputFileName, solver);

		if(outputFileName=="-")
			Lloyd::standardOutput = true;
		else{

			llyod.outfile.open(outputFileName.c_str());
			
			// Check for error in opening a file
			if(!llyod.outfile){
				cout << "Error opening output file !!!" << endl ;
				return 0;
			}
		}

		llyod.solve(solver);
		llyod.outfile.close();
    }
    else{
    	cout << "invalid number of Arguments ! "<<endl;
    	printInputFormat();
    }

	return 0;
}