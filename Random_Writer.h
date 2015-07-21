//
//  Random_Writer.h
//  Sorting Project
//
//  Created by Nicholas Metcalf on 1/6/15.
//  Copyright (c) 2015 Nick Metcalf. All rights reserved.
//

#include <vector>
#include <deque>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cassert>
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

struct RandomWriter {
  int k;
  int length;
  string result;
  string source;
  string seed;
  vector<char> next_chars;
  
  RandomWriter(int k_in, int len_in)
    : k(k_in), length(len_in), source(""), seed(""), next_chars(){};
  
  void load_source(ifstream &infs, string filename); //Load source from file into string
  void get_new_seed();
  void get_next_seed();
  void update_next_chars(); // returns vector of chars after each occurence of seed
  void append_result();
};

class inputError {
};

class negativeError {
};

class lessThanError {
};

class FileError {
};

bool open_file(ifstream & ins, string filename);

void write_to_file(ofstream &ofs, string filename, string to_write);
