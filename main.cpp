

#include "mnist.h"

#include "distances.h"
#include "preprocess.h"

#ifdef KNN_NO_KD
#include "knn_no_kdtree.h"
#endif

#ifdef KNN
#include "knn.h"
#endif

/*
 * MNIST Data Reader
 */
MNISTReader mnist;

/*
 * DataType and Label Type definitions
 */
typedef vector <int> DataType;
typedef int LabelType;

/*
 * Label comparasion function labelCmp(a, b)
 *  return
 *      -1 if a < b,
 *      0 if a == b,
 *      1 if a > b.
 */
int labelCmp(LabelType a, LabelType b){
    return a < b ? -1 : (a == b ? 0 : 1);
}

/* define KNNClassifier */
class KNNClassifier<DataType, LabelType> knn(
        5,
        calcDistEuclid,
        calcDistEuclidSingleDim,
        labelCmp);

int main() {

    cerr << "started" << endl;

    vector < DataWithLabel<DataType, LabelType> > train;
    vector < Data<DataType> > testData;
    vector < Data<LabelType> > testLabels;

    mnist.read(train, testData, testLabels);

    // /* preprocess: binaryzation */
    // binaryzation(train);
    // binaryzation(testData);

    // /* preprocess: downsample */
    // downsample(train);
    // downsample(testData);

    // /* preprocess: sum2scalar */
    // sum2scalar(train);
    // sum2scalar(testData);

    /* preprocess: scale */
    blur(train);
    blur(testData);

    knn.test(train, testData, testLabels);

    cout << "END" << endl;
    return 0;
}
