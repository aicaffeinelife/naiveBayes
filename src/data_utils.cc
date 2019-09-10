#include "../include/data_utils.h"
#include <iostream>
DataParser::DataParser(const string &fname){
  infile.open(fname);
  if (!infile.is_open()) {
    std::cerr << "Couldn't open file!";
    exit(1);
  }
  _parse();
}

DataParser::~DataParser(){
  infile.close();
}


void DataParser::_parse(){

  string line;

  while (!std::getline(infile, line).eof()) {
    istringstream ss(line); // convert to string stream
    vector<float> tokens;
    while (!ss.eof()) {
      float tmp; // extract tokens
      ss >> tmp;
      tokens.push_back(tmp);
    }
    ss.clear();
    _data.push_back(tokens);
  }
}



void Table::_buildIndex(){
  int loop_col= _labelIdx == 0 ? 0: (int)_data[0].size()-1;
  int N = (int)_data.size();
  // samples index
  for (int i = 0; i < N; i++) {
    if (_nSamples.find(_data[i][loop_col]) == _nSamples.end()) {
      _nSamples[_data[i][loop_col]] = 1;
    } else{
      _nSamples[_data[i][loop_col]]++;
    }
  }





  // XXX: Check for possible bugs here
  for (int i = 0; i < N; i++) {
    _rowMap[_data[i][loop_col]].push_back(i);
  }

  // debug code.
  // for (auto it=_rowMap.begin(); it!=_rowMap.end(); it++) {
  //   std::cout << it->first << " " << it->second[0] << "\n";
  // }

}


vector<int> Table::getRows(int clsid){
  if (_rowMap.find((float)clsid) == _rowMap.end()) {
    return {};
  } else{
    return _rowMap[(float)clsid]; // this is really ugly.
  }
}

int Table::get_samples(int clsid){
  return _nSamples[(float)clsid];
}

Table::~Table(){
  _labelIdx = 0;
  _nclass = 0;
  for(auto d: _data){
    d.clear();
  } // empty container
}
