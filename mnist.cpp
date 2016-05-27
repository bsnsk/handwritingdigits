//
// Created by Shuyang Shi on 16/5/26.
//

#include "mnist.h"
#include "dataBasic.h"

/*
 * Constructor
 *  configure its data path
 *      (default to './data/')
 */
MNISTReader::MNISTReader(string _path) {
    path = _path;
}

/*
 * Function to read training and test data
 *  Data to be read:
 *      - train images,
 *      - train labels,
 *      - test images (stored to 'testData'),
 *      - test labels (stored to 'testLabels').
 *  The first two are stored in 'train'.
 */
void MNISTReader::read(vector < DataWithLabel<DataType, LabelType> > &train,
                       vector < Data<DataType> > &testData,
                       vector < Data<LabelType> > &testLabels){

    train.clear();
    testData.clear();
    testLabels.clear();

    read_train_images(train, testData, testLabels);
    read_train_labels(train, testData, testLabels);
    read_test_images(train, testData, testLabels);
    read_test_labels(train, testData, testLabels);

    cerr << "[INFO] Data Set MNIST successfully read." << endl;

}

/*
 * function to read test labels
 *  called by public function 'read()'
 *  store test labels to parameter 'testLabels'
 */
void MNISTReader::read_test_labels(vector < DataWithLabel<DataType, LabelType> > &train,
                                   vector < Data<DataType> > &testData,
                                   vector < Data<LabelType> > &testLabels){
    ifstream in;
    intUnion t;

    in.open((path + "t10k-labels-idx1-ubyte"), ios::binary);

    /* check magic number */
    in.read(t.c, 4);
    int magic = t.reverse();
    assert(magic == 2049);

    /* check number of items */
    in.read(t.c, 4);
    int num = t.reverse();
    assert(num == num_test);

    /* read content */
    for (int i=0; i<num; i++) {
        in.read(t.c, 1);
        testLabels.push_back(Data<LabelType> (t.c[0]));
    }

    in.close();

    cerr << "[INFO] MNIST test labels read done." << endl;

}

/*
 * function to read test images
 *  called by public function 'read()'
 *  store test images to parameter 'testData'
 */
void MNISTReader::read_test_images(vector < DataWithLabel<DataType, LabelType> > &train,
                                   vector < Data<DataType> > &testData,
                                   vector < Data<LabelType> > &testLabels){
    ifstream in;
    intUnion t;

    in.open((path + "t10k-images-idx3-ubyte"), ios::binary);

    /* check magic number */
    in.read(t.c, 4);
    int magic = t.reverse();
    assert(magic == 2051);

    /* check number of items */
    in.read(t.c, 4);
    int num = t.reverse();
    assert(num == num_test);

    /* check number of row */
    in.read((char *)t.c, 4);
    int r = t.reverse();
    assert(r == 28);

    /* check number of column */
    in.read((char *)t.c, 4);
    int c = t.reverse();
    assert(c == 28);

    for (int i=0; i<num; i++) {

        DataType d;

        for (int j=0; j<r*c; j++){
            in.read(t.c, 1);
            d.push_back((unsigned char)t.c[0]);
        }
        testData.push_back(DataWithLabel<DataType, LabelType>(d, 0));
    }

    in.close();
    cerr << "[DEBUG] testData length " << testData.size() << endl;

    cerr << "[INFO] MNIST test images read done." << endl;
}

/*
 * function to read train labels
 *  called by public function 'read()'
 *  store train labes to parameter 'train' (label member)
 */
void MNISTReader::read_train_labels(vector < DataWithLabel<DataType, LabelType> > &train,
                                    vector < Data<DataType> > &testData,
                                    vector < Data<LabelType> > &testLabels){

    ifstream in;
    intUnion t;

    in.open((path + "train-labels-idx1-ubyte"), ios::binary);

    /* check magic number */
    in.read(t.c, 4);
    int magic = t.reverse();
    assert(magic == 2049);

    /* check number of items */
    in.read(t.c, 4);
    int num = t.reverse();
    assert(num == num_train);

    for (int i=0; i<num; i++) {
        in.read(t.c, 1);
        train[i].label = (unsigned char)t.c[0];
    }

    in.close();

    cerr << "[INFO] MNIST train labels read done." << endl;

}

/*
 * function to read train images
 *  called by public function 'read()'
 *  store train images to parameter 'train' (val member)
 */
void MNISTReader::read_train_images(vector < DataWithLabel<DataType, LabelType> > &train,
                                    vector < Data<DataType> > &testData,
                                    vector < Data<LabelType> > &testLabels){

    ifstream in;
    intUnion t;

    in.open(path + "train-images-idx3-ubyte", ios::binary);

    /* check magic number */
    in.read(t.c, 4);
    int magic = t.reverse();
    assert(magic == 2051);

    /* check number of items */
    in.read((char *)t.c, 4);
    int num = t.reverse();
    assert(num == num_train);

    /* check number of row */
    in.read((char *)t.c, 4);
    int r = t.reverse();
    assert(r == 28);

    /* check number of column */
    in.read((char *)t.c, 4);
    int c = t.reverse();
    assert(c == 28);

    for (int i=0; i<num; i++) {
        DataType d;

        for (int j=0; j<r*c; j++){
            in.read((char *)t.c, 1);
            d.push_back((unsigned char)t.c[0]);
        }
        train.push_back(DataWithLabel<DataType, LabelType>(d, 0));
    }

    in.close();

    cerr << "[INFO] MNIST train images read done." << endl;
}