## Naive Bayes Classifier in C++11

This is a pure C++11 implementation of a Naive Bayesian classifier using Gaussian priors.

**Features**:
1. Pure C++11 implementation, no other pre-requisite library.
2. Data container with fast search without modifying the input data or creating new copies.
3. Easily extensible for other conditional priors.


### Brief Description 

The naive bayes classifier treats each attribute as independent of each other. If a gaussian prior is assumed i.e. the _class conditional_ probabilities are drawn from N(mu, sigma) then the posterior class given a data sample is computed as:

<img src="figs/bayes_classifier.png" />

where Z is a normalization function obtained by:

<img src="figs/lower_factor.png" />

Here p(C|x) is the posterior probability, p(Ci) is the apriori class probability and p(x|Ci) is the class conditional probability. 

### Installation and Usage

The code compiles into a single `nb` binary that requires the training and test data. You can use the provided `preprocess.py` script for splitting the data into appropriate train/test split. To build the code:

```
git clone https://github.com/aicaffeinelife/naiveBayes
mkdir build && cd build 
cmake ..
make
``` 

If everything compiles, you should be able to run the binary with your training and test files. Included in the repo is the shuttle landing dataset[1] which predicts whether to land a space shuttle in manual or auto mode.


[1]: Dataset found [here](https://archive.ics.uci.edu/ml/datasets/Shuttle+Landing+Control), Cestnik et al.
