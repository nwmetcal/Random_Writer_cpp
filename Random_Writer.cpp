//
//  Random_Writer.cpp
//
//  Created by Nicholas Metcalf
//

#include "Random_Writer.h"
#include <time.h>

void RandomWriter::append_result() {
  if (!this->result.length() && (k > 0)) {
    for (int i = 0; i < this->k; ++i) {
      this->result.push_back(this->seed[i]);
    }
  }
  else {
    this->result.push_back(this->seed.back());
  }
}

void RandomWriter::load_source(ifstream &infs, string filename) {
  if (open_file(infs, filename)) {
    string temp = "";
    this->source = "";
    while (getline(infs, temp)) {
      this->source.append(temp);
    }
    infs.close();
  }
}

void RandomWriter::update_next_chars() {
  this->next_chars.clear();
  int offset_k = !k;
  size_t found = this->source.find(this->seed);
  if ((found != string::npos) && (found + this->k < this->source.length())) {
    this->next_chars.push_back(source[found+this->k+offset_k]);
  }
  while ((found = this->source.find(this->seed, found+1)) != string::npos) {
    this->next_chars.push_back(source[found+this->k+offset_k]);
  }
}

void RandomWriter::get_new_seed() {
  int pos = rand()%static_cast<int>((this->source.length())-k);
  string new_seed = "";
  if (!k) {
    new_seed.append(this->source.substr(pos, 1));
  }
  else {
    new_seed.append(this->source.substr(pos, this->k));
  }
  this->seed = new_seed;
}

void RandomWriter::get_next_seed() {
  char next = '\0';
  next = next_chars[rand()%next_chars.size()];
  seed.push_back(next);
  seed.erase(0,1);
}


bool open_file(ifstream & ins, string filename) {
  if (ins.is_open()) {
    ins.close();
  }
  ins.open(filename.c_str());
  if (ins.is_open()) {
    return true;
  }
  else {
    cerr << "Error opening input file\n" << flush;
    exit(1);
    return false;
  }
}

void write_to_file(ofstream &ofs, string filename, string to_write) {
  if (ofs.is_open()) {
    ofs.close();
  }
  ofs.open(filename.c_str());
  if (ofs.is_open()) {
    ofs << to_write;
    ofs.close();
    return;
  }
  cerr << "Error opening output file\n" << flush;
  exit(1);
}
