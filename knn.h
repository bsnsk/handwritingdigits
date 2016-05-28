//
// Created by Shuyang Shi on 16/5/25.
//

#ifndef HANDWRITINGDIGITS_KNN_H
#define HANDWRITINGDIGITS_KNN_H

#include "common.h"
#include "classifierBasic.h"
#include "dataBasic.h"

#include "kdtree.h"

template <typename T, typename D>
class KNNClassifier: public Classifier <T, D> {
private:

    /*
     * Function type: Data2int
     *  return as an int
     *  take 2 DataType as parameters
     */
    typedef int (*Data2int) (const T &, const T &);

    /*
     * Function type: Label2int
     *  return as an int
     *  take 2 LabelType as parameters
     */
    typedef int (*Label2int) (D, D);

    /*
     * Function type: DataInt2int
     *  return as an int
     *  take 2 DataType + 1 int as parameters
     */
    typedef int (*DataInt2int) (const T &, const T &, int);

    /*
     * Calculate Data Distance (a, b) of a single dim
     *  return as a integer
     */
    DataInt2int DataDistSingleDim;

    /*
     * Calculate Data Distance (a, b)
     *  return as a integer
     */
    Data2int DataDist;

    /*
     * Compare Label (a, b)
     *  return -1 if a < b
     *  return 0 if a == b
     *  return 1 if a > b
     */
    Label2int LabelCmp;

    /*
     * K for K-Nearest-Neighbor
     */
    int K;

    /*
     * Flag used to check whether it is trianed
     *  True: trained
     *  Flase: not trianed
     */
    bool trained;

    /*
     * Private function 'classify'
     *  used to classify a single item, using K-Nearest-Neighbors
     */
    D classify(
            const Data <T> &data);

    /*
     * KD-Tree to find nearest K data
     *  Used to speed up searching process
     */
    KD_Tree < T, D> kdtree;

public:

    /*
     * KNNClassifier constructor
     *  set K
     *  set DataDist function
     *  set LabelCmp function
     *  set trained flag to False
     */
    KNNClassifier(
            int _K,
            Data2int _DataDist,
            DataInt2int _DataDistSingleDim,
            Label2int _LabelCmp);

    /*
     * KNNClassifier train
     *  Actually, it merely moves training data to its member variable,
     *      and set 'trained' flag to True
     */
    void train(
            vector < DataWithLabel <T, D> > dataWithLabel);

    /*
     * Classify a list of items
     *  data: data to be classified
     *  labels: vector to store classified labels
     */
    void classify(
            const vector < Data <T> > &data,
            vector < Data <D> > &labels);

    /*
     * Test using training data and test data
     *  This includes:
     *      - train (or at least move data to classifier)
     *      - classify
     *      - judge and report and correct ratio (to stderr)
     */
    void test(
            const vector < DataWithLabel<T, D> > &train,
            const vector < Data<T> > &testData,
            const vector < Data<D> > &testLabels);
};

/****************************************************************************/

template <typename T, typename D>
D KNNClassifier <T, D>::classify(
        const Data <T> &data) {

    vector <D> vec = kdtree.query(data, K);

    sort(vec.begin(), vec.end(), LabelCmp);

    int maxCount = 0;
    int curCount = 0;
    D label = *vec.begin();
    for (auto i = 0; i < vec.size(); i++){
        if (!i || vec[i] == vec[i-1])
            curCount++;
        else
            curCount = 1;
        if (curCount > maxCount){
            maxCount = curCount;
            label = vec[i];
        }
    }

    return label;
}


template <typename T, typename D>
KNNClassifier<T, D>::KNNClassifier(
        int _K,
        Data2int _DataDist,
        DataInt2int _DataDistSingleDim,
        Label2int _LabelCmp) {
    K = _K;
    DataDist = _DataDist;
    DataDistSingleDim = _DataDistSingleDim;
    LabelCmp = _LabelCmp;
    trained = 0;
}

template <typename T, typename D>
void KNNClassifier<T, D>::train(
        vector < DataWithLabel <T, D> > dataWithLabel) {
    kdtree.construct(DataDist,
                     DataDistSingleDim,
                     dataWithLabel);
    trained = 1;
}

template <typename T, typename D>
void KNNClassifier<T, D>::classify(
        const vector < Data <T> > &data,
        vector < Data <D> > &labels) {
    if (!trained)
        cerr << "Classifier used to classify before training!" << endl;

    labels.clear();
    for (auto i = data.begin(); i != data.end(); ++i) {
        labels.push_back(classify(*i));
    }
}

template <typename T, typename D>
void KNNClassifier<T, D>::test(
        const vector < DataWithLabel<T, D> > &train,
        const vector < Data<T> > &testData,
        const vector < Data<D> > &testLabels){

    vector < Data<D> > testResults;
    this->train(train);
    cerr << "[INFO] training finished." << endl;

    classify(testData, testResults);
    cerr << "[INFO] classification finished. " << endl;

    int tot = (int) testResults.size();
    int correct = 0;
    for (int i=0; i<tot; i++)
        if (testResults[i].val == testLabels[i].val)
            correct++;

    cerr << "[RESULT] " << correct << " of " << tot << " correct: "
    << correct * 100.0 / tot << "%" << endl;

}

#endif //HANDWRITINGDIGITS_KNN_H
