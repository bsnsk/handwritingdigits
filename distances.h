//
// Created by Shuyang Shi on 16/5/28.
//

#ifndef HANDWRITINGDIGITS_DISTANCES_H
#define HANDWRITINGDIGITS_DISTANCES_H

/*
 * DataType and Label Type definitions
 */
typedef vector <int> DataType;
typedef int LabelType;

/*
 * Distance Calculation Function Types
 */
 typedef int (*PtrCalcDistSingleDim)(const DataType &, const DataType &, int);
 typedef int (*PtrCalcDist)(const DataType &, const DataType &);

/*
 * Calculate image distance using
 *      Euclid distance (L2)
 */
int calcDistEuclidSingleDim(const DataType &a, const DataType &b, int i);
int calcDistEuclid(const DataType &a, const DataType &b);


/*
 * Calculate image distance using
 *      L3 distance
 */
int calcDistL3SingleDim(const DataType &a, const DataType &b, int i);
int calcDistL3(const DataType &a, const DataType &b);

/*
 * Calculate image distance using
 *      L1 distance
 */
int calcDistL1SingleDim(const DataType &a, const DataType &b, int i);
int calcDistL1(const DataType &a, const DataType &b);

#endif //HANDWRITINGDIGITS_DISTANCES_H
