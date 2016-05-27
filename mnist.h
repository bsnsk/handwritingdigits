//
// Created by Shuyang Shi on 16/5/26.
//

#ifndef HANDWRITINGDIGITS_MNIST_H
#define HANDWRITINGDIGITS_MNIST_H

#include "common.h"
#include "dataBasic.h"

/*
 * A data reader for MNIST data
 */
class MNISTReader {

public:

    /*
     * Type definition: DataType as vector of int
     */
    typedef vector<int> DataType;

    /*
     * Type definition: LabelType as int
     */
    typedef int LabelType;

private:

    /*
     * Data set sizes
     *  acquired through its homepage
     */
    static const int num_train = 60000;
    static const int num_test = 10000;

    /*
     * Data file path
     *      be sure to have '/' at the end
     */
    string path;

    /*
     * Union of either an int or 4 char
     *  Used to convert between Big-Endian and Small-Endian
     *  The 'reverse()' function is the converter
     */
    union intUnion {
        char c[4];
        int i;
        int reverse(){
            swap(c[0], c[3]);
            swap(c[1], c[2]);
            return i;
        }
    };

    /*
     * function to read train images
     *  called by public function 'read()'
     *  store train images to parameter 'train' (val member)
     */
    void read_train_images(vector < DataWithLabel<DataType, LabelType> > &train,
                           vector < Data<DataType> > &testData,
                           vector < Data<LabelType> > &testLabels);

    /*
     * function to read train labels
     *  called by public function 'read()'
     *  store train labes to parameter 'train' (label member)
     */
    void read_train_labels(vector < DataWithLabel<DataType, LabelType> > &train,
                           vector < Data<DataType> > &testData,
                           vector < Data<LabelType> > &testLabels);

    /*
     * function to read test images
     *  called by public function 'read()'
     *  store test images to parameter 'testData'
     */
    void read_test_images(vector < DataWithLabel<DataType, LabelType> > &train,
                          vector < Data<DataType> > &testData,
                          vector < Data<LabelType> > &testLabels);

    /*
     * function to read test labels
     *  called by public function 'read()'
     *  store test labels to parameter 'testLabels'
     */
    void read_test_labels(vector < DataWithLabel<DataType, LabelType> > &train,
                          vector < Data<DataType> > &testData,
                          vector < Data<LabelType> > &testLabels);

public:

    /*
     * Constructor
     *  configure its data path
     *      (default to './data/')
     */
    MNISTReader(string _path=string("./data/"));


    /*
     * Function to read training and test data
     *  Data to be read:
     *      - train images,
     *      - train labels,
     *      - test images (stored to 'testData'),
     *      - test labels (stored to 'testLabels').
     *  The first two are stored in 'train'.
     */
    void read(vector < DataWithLabel<DataType, LabelType> > &train,
              vector < Data<DataType> > &testData,
              vector < Data<LabelType> > &testLabels);
};

#endif //HANDWRITINGDIGITS_MNIST_H
