#ifndef DATA_UTILS_H
#define DATA_UTILS_H
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <cassert>
#include <sstream>
using std::vector;
using std::ifstream;
using std::string;
using std::map;
using std::istringstream;

class DataParser
{
  vector<vector<float> > _data;
  ifstream infile;
  string _fname;
public:
  DataParser(const string &fname);
  inline vector<vector<float> > getData() {return _data;}
  ~DataParser();
private:
  void _parse();
};



class Table
{
  map<float, int> _nSamples;
  map<float, vector<int> > _rowMap; // map of class -> row number
  int _nclass; // number of classes
  int _labelIdx;
public:
  vector<vector<float> > _data;
  Table(const vector<vector<float> >&data,
        int numClass,
        int labelIdx):_data(data),
                      _nclass(numClass),
                     _labelIdx(labelIdx){
    _buildIndex();
  }

  vector<int> getRows(int clsid);

  int get_samples(int clsid);

 ~Table();
private:
  void _buildIndex(); // fill the analysis on the table
};



#endif /* DATA_UTILS_H */
