#include <stdlib.h> 
#include <stdio.h> 
#include <vector>
#include <map>
#include <algorithm>
#include <string.h>

#include "graph_extractor.h"

using namespace std;



// TODO: test ! 

void extract_points(vector<point>& points, char* file_name) {

	FILE* f;
	char line[500];
	vector<string> str_tokens;
	char buffer[50];
	int line_counter = 0;

	sprintf(buffer, "%s", file_name);
	printf("reading file_name : %s, buffer: %s \n", file_name, buffer);

	f = fopen(buffer, "r");
	if (!f) {
		printf("error: file could not be open \n");
		abort();
	}


	line_counter = 0;
	point p;
	char* cstr;
	while(getline(f, line, 1256) != EOF) {

		str_tokens.clear();
		if (! tokenize(line, &str_tokens))
			printf("tokenize did not succeed \n");

		for (unsigned int i = 0; i < str_tokens.size(); i++ ) {


			cstr = new char [str_tokens[i].size()+1];
  			strcpy (cstr, str_tokens[i].c_str());

  			if (i == 0) { p.x = atof(cstr); }
  			if (i == 1) { p.y = atof(cstr); }

			delete [] cstr;

		}

		printf("inserting point: %s \n", p.to_string());
		points.push_back(p);
		line_counter ++;
	}



}


void extract_vv_int(vv_int& graph, char* file_name) { 

	FILE* f; 
	char line[5000];
	vector<string> str_tokens;
	char buffer[500];
	int line_counter = 0;

	sprintf(buffer, "%s", file_name);
	printf("reading file_name : %s, buffer: %s \n", file_name, buffer);
	 
	
	f = fopen(buffer, "r"); 	
	if (!f) { 
		printf("error: file could not be open \n");
		abort();
	}


	line_counter = 0;
	vector<int> nlist;
	char* cstr;
	while(getline(f, line, 1256) != EOF) {  
		
		str_tokens.clear();
		if (! tokenize(line, &str_tokens))
			printf("tokenize did not succeed \n"); 


		for (unsigned int i = 0; i < str_tokens.size(); i++ ) {

			
			cstr = new char [str_tokens[i].size()+1];
  			strcpy (cstr, str_tokens[i].c_str());
		
			nlist.push_back(atoi(cstr));
			delete [] cstr; 

		}
		
		// sort (nlist.begin(), nlist.end());
		graph.push_back(nlist);
		line_counter ++; 
		nlist.clear(); 
	}	

}



bool tokenize(char* line, vector<string>* str) { 
	if (!line) { printf("error: line"); return false; } 
	if (!str) { printf("error: str"); return false; }
	
	
	string str_pointer; 
	char* res = new char[1256];
	trim(line, res);
	//char* res = trim(line);
	char* tok = NULL; 

	tok = strtok(res, " "); 
	while (tok != NULL) { 
		//str_pointer = new string(tok); 
		str_pointer.clear();
		str_pointer.append(tok);
		// printf("pushing %s \n", tok);
		str->push_back(str_pointer);
		// delete str_pointer; 
		tok = strtok(NULL," ");
		
	}

	// delete [] res; 
	return true; 
}

void trim(char* input, char* output) { 
	if (!input) return; 
	if (!output) return; 

	int r_index = 0; 
	while (*input) { 
		if (*input == '\t' || *input == ' ') { 
			output[r_index++] = ' ';
			
		} else { 
			output[r_index++] = *input; 
			
		}
		input++;
	}	
	output[r_index] = '\0';

}

int getline(FILE* f, char line[], int max)
{
	int nch = 0;
	char c;
	max = max - 1;			/* leave room for '\0' */

	while((c = fgetc(f)) != EOF)
	{
		if(c == '\n')
			break;

		if(nch < max)
		{
			line[nch] = c;
			nch = nch + 1;
		}
	}

	if(c == EOF && nch == 0)
		return EOF;

	line[nch] = '\0';
	return nch;
}


void print_vv_int(vv_int& list) {
	vector<int>::iterator jt;
	vector<vector<int> >::iterator it = list.begin();
	while (it != list.end()) {

		// jt = it->begin();
		jt = (*it).begin();
		while (jt != (*it).end()) {
			printf("%d ", *jt);
			jt ++;
		}
		printf("\n");

		it ++;
	}


}
