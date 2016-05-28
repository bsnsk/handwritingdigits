//
// Created by Shuyang Shi on 16/5/28.
//

#include "common.h"
#include "dataBasic.h"

#include "distances.h"

/*
 * Calculate image distance using
 *      Euclid distance (single dim)
 */
int calcDistEuclidSingleDim(const DataType &a, const DataType &b, int i){
    return ((a[i] - b[i]) * (a[i] - b[i]));
}

/*
 * Calculate image distance
 *      Euclid distance
 */
int calcDistEuclid(const DataType &a, const DataType &b){
    int re(0);
    for (int i=0; i<a.size(); i++)
        re += calcDistEuclidSingleDim(a, b, i);
    return re;
}

/*****************************************************************************/

/*
 * Calculate image distance using
 *      L3 distance (single dim)
 */
int calcDistL3SingleDim(const DataType &a, const DataType &b, int i){
    return ((a[i] - b[i]) * (a[i] - b[i]) * abs(a[i] - b[i]));
}

/*
 * Calculate image distance
 *      L3 distance
 */
int calcDistL3(const DataType &a, const DataType &b){
    int re(0);
    for (int i=0; i<a.size(); i++)
        re += calcDistL3SingleDim(a, b, i);
    return re < 0 ? 2147483647LL : re;
}

/*****************************************************************************/

/*
 * Calculate image distance using
 *      L1 distance (single dim)
 */
int calcDistL1SingleDim(const DataType &a, const DataType &b, int i){
    return (abs(a[i] - b[i]));
}

/*
 * Calculate image distance
 *      L1 distance
 */
int calcDistL1(const DataType &a, const DataType &b){
    int re(0);
    for (int i=0; i<a.size(); i++)
        re += calcDistL1SingleDim(a, b, i);
    return re < 0 ? 2147483647LL : re;
}
