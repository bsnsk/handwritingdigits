

#include "mnist.h"

#include "distances.h"

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
 * binaryzation of the image data
 *  input:
 *      vec - vector <Data> or vector <DataWithLabel>
 *  threshold:
 *      Pixels with value under threshold is set to zero,
 *      otherwise set to one.
 */
template <typename T>
void binaryzation(vector < T > &vec) {
    static int threshold = 10;
    for (auto data=vec.begin(); data!=vec.end(); data++){
        for (int i = 0; i < data->val.size(); ++i) {
            data->val[i] = (data->val[i] < threshold ? 1 : 0);
        }
    }
    cerr << "[INFO] Binaryzation finished." << endl;
}

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

//    binaryzation(train);
//    binaryzation(testData);

    knn.test(train, testData, testLabels);

    cout << "END" << endl;
    return 0;
}
