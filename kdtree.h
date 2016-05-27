//
// Created by Shuyang Shi on 16/5/26.
//

#ifndef HANDWRITINGDIGITS_KDTREE_H
#define HANDWRITINGDIGITS_KDTREE_H

#include "common.h"
#include "dataBasic.h"

/*
 * KDTree Node Compare (Single Dimension)
 *  Used in KD-Tree data split,
 *      and only this way.
 */
template <typename DataType>
class kdnode_cmp {
private:

    /*
     * Dimension index
     */
    int idx;

public:

    /*
     * Constructor: specify dimension index
     */
    kdnode_cmp(int _idx): idx(_idx) {}

    /*
     * Comparison using the dimension data
     */
    bool operator ()(const Data<DataType> &a,
                     const Data<DataType> &b);
};

/*
 * KD-Tree class template
 */
template <typename DataType, typename LabelType>
class KD_Tree {


    /*
     * Function type: Data2int
     *  return as an int
     *  take 2 DataType as parameters
     */
    typedef int (*Data2int) (DataType, DataType);

    /*
     * Function type: DataInt2int
     *  return as an int
     *  take 2 DataType + 1 int as parameters
     */
    typedef int (*DataInt2int) (const DataType &, const DataType &, int);

    /*
     * Calculate Data Distance (a, b)
     *  return as an integer
     */
    Data2int DataDist;

    /*
     * Calculate Data Distance(a, b, idx)
     *      of dimension idx
     *  return as an integer
     */
    DataInt2int DataDistSingleDim;

    /*
     * Node Class
     */
    struct kd_node {
        /* The dimension used to compare */
        int dir;

        /* The point data in the node */
        DataWithLabel<DataType, LabelType> data;

        /* Negative and Positive */
        kd_node *ngtv, *pstv;

        /* Constructor with direction */
        kd_node(int D=0)
                : dir(D), ngtv(0), pstv(0) {}

    };

    /*
     * Tree root node pointer
     */
    kd_node *root;

    /*
     *  Build K-D Tree according to certain point sequence
     */
    struct kd_node * build_node(
            vector < DataWithLabel<DataType, LabelType> > &points);

    /*
     * Free memory
     */
    void erase(kd_node *root);

    /*
     * Pair of distance and candidate labels
     */
    struct pair_type {

        /* Distance */
        int dist;

        /* The candidate point label */
        LabelType data;

        /* constructor */
        pair_type(int d=0, LabelType *p=0);

        /* cmp (used in priority_queue) */
        bool operator < (const pair_type &b) const;
    };

    /*
     * Candidate set with size K
     *  Used in 'query'
     */
    priority_queue < pair_type > que;

    /*
     * Query in the subtree whose root is 'root'
     *  Called recursively
     *  Result stored in 'que', as this is of type void
     */
    void query(kd_node *root, const Data<DataType> &query_point, int m);

public:

    /*
     * Empty Constructor
     */
    KD_Tree() {}

    /*
     * Configure and construct the tree
     *  Parameters:
     *      - _DataDist: distance calculation function
     *      - _DataDistSingleDim: distance calculation of one dimension
     *      - points: data points (with labels)
     */
    void construct(Data2int _DataDist,
                   DataInt2int _DataDistSingleDim,
                   vector < DataWithLabel<DataType, LabelType> > &points);

    /*
     * Destructor
     */
    ~KD_Tree();

    /*
     * Query for the M-Nearest-Neighbor of point 'query_point'
     *  Return a vector of Labels
     *  Use 'que' to store intermediate results
     */
    vector < LabelType > query(const Data<DataType> &query_point, int m);

};

/****************************************************************************/

template <typename DataType>
bool kdnode_cmp<DataType>::operator ()(const Data<DataType> &a,
                 const Data<DataType> &b){
    return a.val[idx] < b.val[idx];
}

template <typename DataType, typename LabelType>
struct KD_Tree<DataType, LabelType>::kd_node * KD_Tree<DataType, LabelType>::build_node(
        vector < DataWithLabel<DataType, LabelType> > &points) {
    if (points.empty())
        return NULL;
    kd_node *root;

    /* If there is only one point */
    if (points.size()==1){
        root = new kd_node(0);
        root->data = *points.begin();
    }
        /* Multiple points */
    else {
        int cur_dimension;
        root = new kd_node(cur_dimension =
                                   rand() % points[0].val.size());

        /* Split the vector according to the (size/2)th element */
        std::nth_element(points.begin(),
                         points.begin()+points.size()/2,
                         points.end(),
                         kdnode_cmp<DataType>(cur_dimension));

        root->data = points[points.size()/2];
        vector < DataWithLabel<DataType, LabelType> > vec_ng(
                points.begin(),
                points.begin()+points.size()/2);
        vector < DataWithLabel<DataType, LabelType> > vec_ps(
                points.begin()+points.size()/2+1,
                points.end());

        /* Build recursively */
        root->ngtv = build_node(vec_ng);
        root->pstv = build_node(vec_ps);
    }

    return root;
}

template <typename DataType, typename LabelType>
void KD_Tree<DataType, LabelType>::erase(kd_node *root){
    if (root->ngtv)
        erase(root->ngtv);
    if (root->pstv)
        erase(root->pstv);
    delete root;
}

template <typename DataType, typename LabelType>
void KD_Tree<DataType, LabelType>::construct(Data2int _DataDist,
               DataInt2int _DataDistSingleDim,
               vector < DataWithLabel<DataType, LabelType> > &points) {
    DataDist = _DataDist;
    DataDistSingleDim = _DataDistSingleDim;
    root = build_node(points);
}

template <typename DataType, typename LabelType>
KD_Tree<DataType, LabelType>::~KD_Tree(){
    erase(root);
}

template <typename DataType, typename LabelType>
vector < LabelType > KD_Tree<DataType, LabelType>::query(const Data<DataType> &query_point, int m){
    for (; !que.empty(); que.pop());
    query(root, query_point, m);
    vector < LabelType > seq;
    while (!que.empty()){
        seq.push_back(que.top().data);
        que.pop();
    }
    return seq;
}

template <typename DataType, typename LabelType>
KD_Tree<DataType, LabelType>::pair_type::pair_type(int d, LabelType *p){
    dist = d;
    if (p) data=*p;
}

template <typename DataType, typename LabelType>
bool KD_Tree<DataType, LabelType>::pair_type::operator < (const pair_type &b) const {
    return dist < b.dist;
}

template <typename DataType, typename LabelType>
void KD_Tree<DataType, LabelType>::query(kd_node *root, const Data<DataType> &query_point, int m){
    kd_node *n=root->ngtv, *p=root->pstv, *r=root;
    bool flag=0;

    pair_type cur(DataDist(query_point.val, r->data.val), &r->data.label);

    int cur_dimension = r->dir;

    if (! kdnode_cmp<DataType>(cur_dimension)(query_point, r->data))
        swap(n, p);

    /* Check in the closer subtree */
    if (n)
        query(n, query_point, m);

    /* Candidate set is not full */
    if (que.size() < m){
        que.push(cur);
        flag=1;
    }
        /* Check whether replace someone in the candidate set */
    else {
        if (cur.dist < que.top().dist){
            que.pop();
            que.push(cur);
        }
        if (DataDistSingleDim(query_point.val, r->data.val, r->dir)
            < que.top().dist)
            flag = 1;
    }

    /* Check in the farther subtree */
    if (p && flag)
        query(p, query_point, m);
}
#endif //HANDWRITINGDIGITS_KDTREE_H
