//
//  Driver.cpp
//
//  Created by Nicholas Metcalf
//

#include "Random_Writer.h"
#include <stdlib.h>
#include <string>
#include <getopt.h>

static inputError inp_Err;
static negativeError neg_Err;
static lessThanError less_Err;
static FileError file_Err;

int main(int argc, char *argv[]) {

  int length = 0;
  int seed = 0;
  string input_file = "";
  string output_file = "";
  
  static struct option longopts[] = {
    {"length",  required_argument,  nullptr, 'l'},
    {"seed",    required_argument,  nullptr, 's'},
    {"output",  required_argument,  nullptr, 'o'},
    {"input",   required_argument,  nullptr, 'i'},
    {"help",    no_argument,        nullptr, 'h'}
  };
  
  opterr = false;
  
  int idx = 0;
  int c;
  
  while ((c = getopt_long(argc, argv, "s:l:o:i:h", longopts, &idx)) != -1) {
    switch (c) {
      case 'l': {
        length = atoi(optarg);
        break;
      }
      case 's': {
        seed = atoi(optarg);
        break;
      }
      case 'i': {
        input_file = optarg;
        break;
      }
      case 'o': {
        output_file = optarg;
        break;
      }
      case 'h': {
        cout << "Usage...\n"
        << "./<executable> -l <output lenght> -s <seed length>"
        << "-i <input fil name> -o <output file name>\n" << flush;
        exit(0);
        break;
      }
      default: {
        cout << "Error! Unrecognized command! Use -h or --help for usage\n";
        exit(1);
        break;
      }
    }
  }
  try {
    if (argc != 9) {
      throw  inp_Err;
    }
    if ((length < 0) || (seed < 0)) {
      throw neg_Err;
    }
    if (seed > length) {
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
  
  RandomWriter rw(seed, length);
  srand((unsigned int)time(nullptr));

  ifstream infs;
  ofstream ofs;

  infs.open(input_file.c_str());
  ofs.open(output_file.c_str());
 
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
  
  rw.load_source(infs, input_file.c_str());
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
  
  write_to_file(ofs, output_file.c_str(), rw.result);
  
  return 0;
}

