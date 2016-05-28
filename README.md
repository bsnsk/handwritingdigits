# Handwritingdigits

An Experiment using MNIST dataset.

## Experiment Results

Classifier             |   Distance      | Prepossessing                | Correct Ratio | Error Ratio
-----------------------|-----------------|------------------------------|---------------|---------------
Baseline (random)      |                 |                              | xx.xx %       |  xx.xx %
KNN (kdtree, K=5)      | L2 (Euclidean)  | None                         | 96.90 %       |  3.10 %
KNN (kdtree, K=5)      | L3              | None                         | 97.28 %       |  2.72 %
KNN (kdtree, K=5)      | L1              | None                         | 96.26 %       |  3.74 %
KNN (kdtree, K=1)      | L2 (Euclidean)  | None                         | 96.91 %       |  3.09 %
KNN (kdtree, K=20)     | L2 (Euclidean)  | None                         | 96.27 %       |  3.73 %
KNN (kdtree, K=5)      | L2 (Euclidean)  | Binaryzation (threshold=10)  | 9x.xx %       |  x.xx %
KNN (kdtree, K=5)      | L2 (Euclidean)  | Downsample (factor=4)        | 9x.xx %       |  x.xx %
KNN (kdtree, K=5)      | L2 (Euclidean)  | Scale (factor=4)             | 9x.xx %       |  x.xx %
KNN (kdtree, K=5)      | L2 (Euclidean)  | Sum (image into scalar)      | 9x.xx %       |  x.xx %
