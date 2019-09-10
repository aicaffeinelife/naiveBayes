#include "../include/nb.h"


// init mean/variance
void NB::_init(){
  _apriori.resize(_nClasses, 0);
  for (int i = 0; i < _nClasses; ++i) {
    int ns = _dtable.get_samples(i + _label_offset);
    _apriori[i] = (float)1/ns;
  } 
}

// TERRIBLE O(N) IMPLEMENTATION WITH EXPICIT COPY!
vector<float> NB::vecSub(vector<float> &a, int b){
  vector<float> res(a.size(), 0);
  for (int i = 0; i < a.size(); ++i) {
    res[i] = a[i] - b;
  }
  return res;
}

float NB::dot(vector<float> &a, vector<float> &b){
  assert(a.size() == b.size());
  int N = (int) a.size();
  float dot = 0.0;
  for (int i =0; i < N; ++i) {
    dot = a[i] * b[i];
  }
  return dot;

}

void NB::computeClassmean(int cls_id) {
  int ns = _dtable.get_samples(cls_id + _label_offset);
  vector<int> clsRows = _dtable.getRows(cls_id + _label_offset);
  float mu = 0.f;
  for (int i = 0; i < clsRows.size(); i++) {
    int crow = clsRows[i];
    for (int j = 0; j < _dtable._data[crow].size(); j++) {
         if (_dtable._data[crow][j] != _dont_care) {
           mu += _dtable._data[crow][j];
         }
    }

  }

  mu = mu / ns;
  _mean[cls_id] = mu;

}


void NB::computeClassvar(int cls_id){
  int ns  = _dtable.get_samples(cls_id + _label_offset);
  float mu = _mean[cls_id];
  float sig = 0.0;
  vector<int> clsRows = _dtable.getRows(cls_id + _label_offset);

  for (int i = 0; i < clsRows.size(); i++) {
    int crow = clsRows[i];
    for (int j = 0;j < _dtable._data[crow].size(); j++) {
       sig += (_dtable._data[crow][j] - mu) * (_dtable._data[crow][j] - mu);
     }

  }
  sig = (float)sqrt(sig);
  _variance[cls_id] = sig;
}

float NB::evalGaussian(vector<float> &x, float mu, float sig){
  vector<float> diff = vecSub(x, mu);
  float dot_prod = dot(diff, diff);
  float gauss = exp(-(dot_prod/(2*sig*sig)));
  gauss /= 1/sqrt(2*PI*sig*sig);
  std::cout << "Gauss:: " << gauss << "\n";
  return gauss;
}


void NB::train(){
  for (int i = 0; i < _nClasses; i++) {
    computeClassmean(i);
    computeClassvar(i);
  }

}


int NB::predict(vector<float> &sample){
  vector<float> pred(_nClasses, 0.0);

  // crucial: The naive bayes assumes each attribute is separate, we're point
  // sampling the normal distribution with a dimensional mean and variance
  // scaled by a-priori bias.
  for (int i= 0; i < _nClasses; ++i) {
    pred[i] = evalGaussian(sample, _mean[i], _variance[i])*_apriori[i];
  }



  int bestPred = argmax(pred);
  return bestPred + _label_offset;

}

NB::~NB(){
  _nClasses = 0;
  _label_idx = 0;
  _label_offset = 0;
  _dont_care = 0;
  _mean.clear();
  _variance.clear();
  _apriori.clear();

}
