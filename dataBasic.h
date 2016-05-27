//
// Created by Shuyang Shi on 16/5/27.
//

#ifndef HANDWRITINGDIGITS_DATABASIC_H
#define HANDWRITINGDIGITS_DATABASIC_H

/*
 * Data class template <DataType, LabelType>
 *      (with a constructor)
 *  val: its real content
 */
template <typename T>
class Data {
public:
    T val;
    Data(T _val): val(_val) {}
};

/*
 * DataWithLabel class template <DataType, LabelType>
 *      (with a constructor)
 *  label: label of this particular data
 */
template <typename T, typename D>
class DataWithLabel: public Data <T> {
public:
    D label;
    DataWithLabel(T _val, D _label): Data<T>(_val), label(_label) {}
};

#endif //HANDWRITINGDIGITS_DATABASIC_H