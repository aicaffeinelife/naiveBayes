#ifndef NB_H
#define NB_H
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <stdlib.h>
#include <cassert>
#define PI 3.14

#include "data_utils.h"
/*
Naive Gaussian Bayes in c++
*/
using std::vector;


// naive bayes class
class NB
{
  Table _dtable;
  float _dont_care; // the dont care number to ignore
  vector<float> _mean;
  vector<float> _variance;
  vector<float> _apriori;
  int _nClasses;
  int _label_idx;
  int _label_offset; // when labels don't start with 0.
public: 
  explicit NB(vector<vector<float> >&data,
     int nClasses,
     int label_idx,
     float dcare,
     int offset):_dtable(data, nClasses, label_idx),
                 _dont_care(dcare),
                 _nClasses(nClasses),
                 _label_idx(label_idx),
                 _label_offset(offset){
    _mean.resize(nClasses, 0);
    _variance.resize(nClasses, 0);
    _init(); // init apriori probabilities.
  }

  vector<float> getMean() const {return this->_mean;}
  vector<float> getVariance() const { return this->_variance;}
  // evaluate the mean and the variance of each class conditioned samples
  void train();

  // Given sample, and obtained mu and var we can evaluate map using Bayes rule
  // the obtained vector is a C-dim probability and the argmax indicates the class.
  int predict(vector<float>&sample);

   ~NB();

protected:
  void computeClassmean(int cls_id); // compute mean of given class starting at offset
  void computeClassvar(int cls_id);
  float evalGaussian(vector<float>& sample, float mu, float sig);
  inline int argmax(vector<float> &x){
    int idx = std::distance(x.begin(), std::max_element(x.begin(), x.end()));
    return idx;
  }

private:
  void _init();
  vector<float> vecSub(vector<float> &a, int b); // scalar subtraction
  float dot(vector<float> &a, vector<float> &b);
};






#endif /* NB_H */


