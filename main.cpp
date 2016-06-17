

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

/* define Parameters for KNNClassifier */
int K = 5;
PtrCalcDistSingleDim ptrCalcDistSingleDim = calcDistEuclidSingleDim;
PtrCalcDist ptrCalcDist = calcDistEuclid;

void autopara(
        vector < DataWithLabel<DataType, LabelType> > ori_train,
        int dataSize = 1000) {
    int ori_train_size = ori_train.size();

    cerr << "[INFO] auto-choosing parameter ..." << endl;

    srand(time(0));
    set<int> S;
    vector < DataWithLabel<DataType, LabelType> > train;
    vector < Data<DataType> > testData;
    vector < Data<LabelType> > testLabels;
    for (int i=0, u; i<dataSize; i++){
        while(u = rand() % ori_train.size(), S.find(u) != S.end());
        S.insert(u);
        train.push_back(ori_train[u]);
        testData.push_back(Data<DataType>(ori_train[u].val));
        testLabels.push_back(Data<LabelType>(ori_train[u].label));
    }

    cerr << "[DEUG] Data Sample Generated of size " << dataSize << endl;

    double maxCorrectRate = 0;
    vector < pair<PtrCalcDistSingleDim, PtrCalcDist> > dists;
    dists.resize(4);
    dists[1] = make_pair(calcDistL1SingleDim, calcDistL1);
    dists[2] = make_pair(calcDistEuclidSingleDim, calcDistEuclid);
    dists[3] = make_pair(calcDistL3SingleDim, calcDistL3);

    int finalD = 1;
    for (int cK = 3; cK < 15; cK += 2)
        for (int d = 1; d <= 3; d++){
            class KNNClassifier<DataType, LabelType> knn(
                    cK,
                    dists[d].second,
                    dists[d].first,
                    labelCmp);
            double curRate = knn.test(train, testData, testLabels);
            cerr << "[DEBUG]\tK=" << cK
                    << ", Distance=L" << d
                    << ", correctRate="
                        << fixed << setprecision(4) << curRate << endl;
            if (curRate > maxCorrectRate) {
                maxCorrectRate = curRate;
                finalD = d;
                K = cK;
            }
        }

    ptrCalcDist = dists[finalD].second;
    ptrCalcDistSingleDim = dists[finalD].first;
    cerr << "[INFO] Choose K=" << K << " and Distance=L" << finalD << endl;
}

int main() {

    cerr << "started" << endl;

    /* define KNNClassifier */
    class KNNClassifier<DataType, LabelType> knn(
            K,
            ptrCalcDist,
            ptrCalcDistSingleDim,
            labelCmp);

    vector < DataWithLabel<DataType, LabelType> > train;
    vector < Data<DataType> > testData;
    vector < Data<LabelType> > testLabels;

    mnist.read(train, testData, testLabels);

    autopara(train);

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
