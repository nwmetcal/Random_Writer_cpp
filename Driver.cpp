//
//  Main.cpp
//  Sorting Project
//
//  Created by Nicholas Metcalf on 1/7/15.
//  Copyright (c) 2015 Nick Metcalf. All rights reserved.
//

#include "Random_Writer.h"

static inputError inp_Err;
static negativeError neg_Err;
static lessThanError less_Err;
static FileError file_Err;

int main(int argc, char *argv[]) {
  try {
    if (argc != 5) {
      throw  inp_Err;
    }
    if ((atoi(argv[1]) < 0) || (atoi(argv[2]) < 0)) {
      throw neg_Err;
    }
    if (atoi(argv[1]) > atoi(argv[2])) {
      throw less_Err;
    }
  }
  catch (inputError) {
    cerr << "Please enter as valid number of inputs" << endl;
    exit(1);
  }
  catch (negativeError) {
    cerr << "Please enter non-negative values for k and length" << endl;
    exit(1);
  }
  catch (lessThanError) {
    cerr << "Please enter a length value greater than k" << endl;
    exit(1);
  }
  
  RandomWriter rw(atoi(argv[1]), atoi(argv[2]));
  ifstream infs;
  ofstream ofs;
  
  infs.open(argv[3]);
  ofs.open(argv[4]);
 
  try {
    if (!infs.is_open()) {
      throw file_Err;
    }
    if (!ofs.is_open()) {
      throw file_Err;
    }
  }
  catch (FileError) {
    cerr << "Error in opening Input/Output file\n" << flush;
    exit(1);
  }
  
  infs.close();
  ofs.close();
  
  rw.load_source(infs, argv[3]);
  rw.get_new_seed();
  rw.append_result();
  
  while (rw.result.length() < rw.length) {
    rw.update_next_chars();
    if (rw.next_chars.empty()) {
      rw.get_new_seed();
    }
    else {
      rw.get_next_seed();
    }
    rw.append_result();
  }
  
  write_to_file(ofs, argv[4], rw.result);
  
  return 0;
}

