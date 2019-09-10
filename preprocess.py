import os
import argparse

"""Script to preprocess the data and split it into test/train splits"""


def read_and_process(fname,
                     missing=False,
                     schar=',',
                     dontcare='*',
                     train_split=0.8):
    with open(fname) as f:
        lines = [line.rstrip() for line in f.readlines()]

    data = []

    for line in lines:
        tokens = line.split(schar)
        tokens = [str(-1) if token == dontcare else token for token in tokens]
        print(tokens)

        dline = ' '.join(token for token in tokens)+'\n'
        data.append(dline)

    train_samples = int(len(data)*train_split)
    train = data[:train_samples]
    test = data[train_samples:]

    train_f = os.path.join(os.getcwd(), 'train.data')
    test_f = os.path.join(os.getcwd(), 'test.data')
    with open(train_f, 'w') as trfile:
        trfile.writelines(train)
    with open(test_f, 'w') as tefile:
        tefile.writelines(test)
    print('Finished preprocess')


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--data',
                        type=str,
                        required=True,
                        help='Path to data file')
    parser.add_argument('--split',
                        type=float,
                        default=0.8,
                        help='Train/Test split')
    args = parser.parse_args()
    read_and_process(args.data, train_split=args.split)



