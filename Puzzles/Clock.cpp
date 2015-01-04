
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
 *	Fixing the Clock Problem
 *  This program to set the clcok time to actual time user wants 
 *	Input : Takes n arguments n>=3
 *			1. N hour clock
 *			2. Time where the clock has been stopped
 *			3. True time i.e. user input
 *          4. remaining argumets specify the steps the hour hand can moved.
 *  We move forward or backword to adjust the time. The path should be 
 *	the shortest path to reach the desired goal.
 * 
 * @author Dayanand Kanth
 */

/*
 * Class
 * Clock
 * Defines the follwoing required elements for the clock program
 */

class Clock
{
	int current_time;
	int forward, backward;
	Clock *parent_clock;
public:
	static int no_of_hrs, goalConfig;
	static int *steps, no_of_steps;
	Clock(int, int, int, Clock*);
	void solve(Solver<Clock>&);
	bool hasAlreadySeen(Clock, Solver<Clock>&);
	bool isEqual(Clock,int);
	list<Clock> generateNextConfigurations(Clock);
	void printResult(Clock);
	void printConfiguration(Clock);
};

/*
 * Global Declarations.
 * No of hrs
 * True time
 * no of possible configurations 
 * User specified values to generate next configurations.
 */
int Clock::no_of_hrs;
int Clock::goalConfig;
int Clock::no_of_steps;
int* Clock::steps;

/*
* Constructor to initialize all the required values
*/
Clock::Clock(int cur_Time,int f=0, int b=0, Clock *parent = NULL){
	current_time = cur_Time;
	forward = f;
	backward = b;
	parent_clock = parent;
}


/*
 * generateNextConfigurations
 * The function will help to generate the configurations and make the clock move
 * forward or backward
 * 
 * @param  current_config
 */
list<Clock> Clock::generateNextConfigurations(Clock current_config){
		list<Clock> newConfigs;
		Clock* parent = new Clock(current_config.current_time,current_config.forward,
			current_config.backward,current_config.parent_clock);

		for(int i=0;i<no_of_steps;i++){
			if(steps[i] < 0){
				if(current_config.current_time + steps[i] <= 0){
					Clock next_config (current_config.no_of_hrs + current_config.current_time + steps[i],
						current_config.forward,
						current_config.backward - steps[i], parent);
					newConfigs.push_back(next_config);
				}
				else{
					Clock next_config (current_config.current_time + steps[i],
						current_config.forward,
						current_config.backward - steps[i], parent);
					newConfigs.push_back(next_config);
				}
			}
			else{
				if(current_config.current_time + steps[i] > no_of_hrs){
					Clock next_config ((current_config.current_time + steps[i]) % current_config.no_of_hrs,
						current_config.forward + steps[i],
						current_config.backward, parent);
					newConfigs.push_back(next_config);
				}
				else{
					Clock next_config (current_config.current_time + steps[i],
						current_config.forward + steps[i],
						current_config.backward, parent);
					newConfigs.push_back(next_config);
				}
			}
		}

		return newConfigs;
}


/*
 * solve
 * This function will calculate the paths which have to be traveresed in ordered to reach
 * the desired goal Configuration. We find the shortest path.
 * 
 * @param  &solver of Solve type
 */
void Clock::solve(Solver<Clock> &solver){
	
	Clock current_config = solver.config_queue.front();
	while(!isEqual(current_config,goalConfig)){

		solver.seen_queue.push_back(current_config);
		solver.config_queue.erase(solver.config_queue.begin());

		list<Clock> newConfigs = generateNextConfigurations(current_config);
		int listSize = (int)newConfigs.size();

		for(int i=0;i<listSize;i++){
			Clock next_config = newConfigs.front();
			newConfigs.pop_front();
			if(!hasAlreadySeen(next_config,solver))
				solver.config_queue.push_back(next_config);
		}

		if((int)solver.config_queue.size() == 0){
			cout<<"\nNo possbile solutions found !!!\n"<<endl;
			exit(0);
		}

		current_config = solver.config_queue.front();

		cout<<"current configuration : ";
		printConfiguration(current_config);
		cout<<endl;
	}

}

/*
 * isEqual
 * The Function will check the current config is equal to the goal configuration
 * 
 * @param current_config
 * @param goalConfig
 */
bool Clock::isEqual(Clock current_config, int goalConfig){
	return (current_config.current_time == goalConfig) ;
}
/*
 * hasAlreadySeen
 * This function will check if the configuraton is already seen
 * If seen return true or false
 * 
 *	@param next_config of type clock
 *  @param solver of type solver
 */
bool Clock::hasAlreadySeen(Clock next_config, Solver<Clock> &solver){
	for (int i = 0; i < solver.config_queue.size(); ++i){
			//If already seen
			if(solver.config_queue[i].current_time == next_config.current_time)
				return true;
		}
		for (int i = 0; i < solver.seen_queue.size(); ++i){
			//If already seen
			if(solver.seen_queue[i].current_time == next_config.current_time)
				return true;
		}
		return false;
}

/*
 * printConfiguration
 * The Function will print the clock current time.
 * 
 * @param current_config
 */
void Clock::printConfiguration(Clock clock){
	cout<<clock.current_time<<" "<<clock.forward<<" "<<clock.backward<<" ";
}

/*
 * printResult
 * The Function will print the final result.
 * 
 * @param current_config
 */
void Clock::printResult(Clock clock){
	cout<<"\nMove the hour hand "<<clock.forward
		<<"hrs forward and ";
	cout<<"move the hour hand "<<clock.backward
		<<"hrs backward"<<endl;

	stack<int> sequence;
	sequence.push(clock.current_time);
   
    //Sequence in which hour hand of dead clock has to be moved 
    // to bring it back to show the true time.
	cout<<"sequence to follow:"<<endl;
	Clock *parent = clock.parent_clock;
	while(parent != NULL){
		sequence.push(parent->current_time);
		parent = parent->parent_clock;
	}

	while (!sequence.empty())
  	{
     cout<<sequence.top()<<"-->";
     sequence.pop();
  	}
  	cout<<endl<<"\n";
}

/*
 * printInputFormat
 * The Function will print the format, arguments has 
 * to be supplied.
 */

void printInputFormat(){
	cout<<"\nInput Format Example: .a/.out 12 2 4 . . ."<<endl;
	cout<<"12 : Clock Hours"<<endl;
	cout<<"2 : Time at which clock has stopped"<<endl;
	cout<<"4 : Time to which clock has to be adjusted\n"<<endl;
	cout<<". . . : can be 0 to any number of arguments that specifies the steps in which\n";
	cout<<"hour hand of clock can be moved. default is in steps of 1\n"<<endl;
}

/*
 * 
 * @param argc
 * @param *argv[]
 */
int main(int argc, char *argv[]){

	/* Provide the correct number of arguments in order to solve.
	 * Following are mandotary arguments
	 * Argument 1 : Number of hours on clock(N-modulo clock)
	 * Argument 2 : Current Clock time
	 * Argument 3 : True time or the user desired time
	 * Extra Arguemts : Steps in which clock hand can be moved. (default 1 -1)
	 */
	if(argc-1 < 3){
		cout<<"Invalid number of inputs"<<endl;
		printInputFormat();
		exit(0);
	}

	/*
	 * Checks for the invalid input
	 * Following are the conditions to check weather the entered argument is correct or not
	 * Condition 1: Current clcok time should be grater than 1
	 * Condition 2: Current clock time should be less than Number of hours on clock
	 * Condition 3: True time should be grater than 1
	 * Condition 4: True time should be less than Number of hours on clock
	 */
	if(atoi(argv[2]) < 1 || atoi(argv[2]) > atoi(argv[1]) ||
		atoi(argv[3]) < 1 || atoi(argv[3]) > atoi(argv[1])){
		cout<<"Invalid input"<< endl;
		printInputFormat();
		exit(0);
	}

	// Get the input. Convert the input string into integer.
	Clock::no_of_hrs = atoi(argv[1]);
	Clock::goalConfig = atoi(argv[3]);
	Clock::no_of_steps = argc - 4;

    // steps specified by the user the program can take to fix the dead clock.
	if(Clock::no_of_steps > 0){
		Clock::steps = new int[Clock::no_of_steps];
		for(int i=0;i<Clock::no_of_steps;i++)
		Clock::steps[i] = atoi(argv[i+4]);
	}

	// default steps the program can make to fix the clock (1: 1hr forward, -1: 1 hr backward)
	if(Clock::no_of_steps == 0){
		Clock::no_of_steps = 2;
		Clock::steps = new int[Clock::no_of_steps];
		Clock::steps[0] = 1;
		Clock::steps[1] = -1;
	}

	//Create a solver 
	Solver<Clock> solver;

	//Create a clock
	int currentTime = atoi(argv[2]);
	Clock clock(currentTime);
	solver.config_queue.push_back(clock);


	cout<<"initial configuration : ";
	clock.printConfiguration(solver.config_queue.front());
	cout<<endl;

	//Call the solve to process the functionality.
	clock.solve(solver);

	// Print the result
	clock.printResult(solver.config_queue.front());
}