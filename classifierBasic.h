//
// Created by Shuyang Shi on 16/5/27.
//

#ifndef HANDWRITINGDIGITS_CLASSIFIERBASIC_H
#define HANDWRITINGDIGITS_CLASSIFIERBASIC_H

#include "dataBasic.h"

/*
 * Classifier class template
 *  To be implemented by users
 *      according to its real nature.
 */
template <typename T, typename D>
class Classifier {

    virtual void train(
            vector < DataWithLabel <T, D> > dataWithLabel) = 0;

    /*
     * Classify a list of items
     *  data: data to be classified
     *  labels: vector to store classified labels
     */
    virtual void classify(
            const vector < Data <T> > &data,
            vector < Data <D> > &labels) = 0;

    /*
     * Test using training data and test data
     *  This includes:
     *      - train (or at least move data to classifier)
     *      - classify
     *      - judge and report and correct ratio (to stderr)
     */
    virtual void test(
            const vector < DataWithLabel<T, D> > &train,
            const vector < Data<T> > &testData,
            const vector < Data<D> > &testLabels) = 0;
};

#endif //HANDWRITINGDIGITS_CLASSIFIERBASIC_H
