#ifndef __COLLECTION_CREATOR__
#define __COLLECTION_CREATOR__



#include <string>
#include <vector>
using namespace std;


#include "point.h"

// type definitions.
typedef vector<vector<int> > vv_int;


void extract_points(vector<point>&, char* filename);
void extract_vv_int(vv_int& , char* filename);
bool tokenize(char* , vector<string>* );
void trim(char* input, char* output); 
int getline(FILE* f, char line[], int max); 
void print_vv_int(vv_int& list) ;






#endif 
