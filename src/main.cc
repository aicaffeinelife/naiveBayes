#include "../include/data_utils.h"
#include "../include/nb.h"
#include <iostream>

int main(int argc, char *argv[])
{
  if (argc != 3) {
     std::cout << "Usage ./nb <train_file> <test_file>" << "\n";
     exit(1);
  }

  string tfile(argv[1]);
  string tefile(argv[2]);
  DataParser train(tfile);
  DataParser test(tefile);



  vector<vector<float> > train_data = train.getData();
  vector<vector<float> > test_data = test.getData();

  NB nb(train_data,
        2,
        0,
        -1,
        1);

  nb.train();

  int pred = nb.predict(test_data[1]);
  std::cout << "best prediction:: " << pred <<"\n";
   
  return 0;
}

