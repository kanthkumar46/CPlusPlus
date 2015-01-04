/*
 * Solver.h
 * 
 * Version :
 *  $Id$
 *
 * Revisions:
 *  $log$
 */
#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <string>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <unistd.h>

using namespace std;

/**
 * 
 *	Class Solver
 * 	Generic Type Class
 *
 * @author Hanagal Madhusudan 
 * @author Dayanand Kanth
 * @author Bharadwaj Suman
 */



/*
 *  The Main Solver header file
 *  Generic Type Solver Class - using Template
 * 	config_queue - Configurations queue
 *  seen_queue - Already seen queue
 *	path - Map to hold all the paths.
 */
template <class T>
class Solver{
public:
	vector<T> config_queue;
	vector<T> seen_queue;
	map<T,T> path;
};