# Handwritingdigits

An Experiment using MNIST dataset.

## Manual Experiment Results

Classifier             |   Distance      | Prepossessing                | Correct Ratio | Error Ratio
-----------------------|-----------------|------------------------------|---------------|---------------
Baseline (random)      |                 |                              | xx.xx %       |  xx.xx %
KNN (kdtree, K=5)      | L2 (Euclidean)  | None                         | 96.90 %       |  3.10 %
KNN (kdtree, K=5)      | L3              | None                         | 97.28 %       |  2.72 %
KNN (kdtree, K=5)      | L1              | None                         | 96.26 %       |  3.74 %
KNN (kdtree, K=1)      | L2 (Euclidean)  | None                         | 96.91 %       |  3.09 %
KNN (kdtree, K=20)     | L2 (Euclidean)  | None                         | 96.27 %       |  3.73 %
KNN (kdtree, K=5)      | L2 (Euclidean)  | Binaryzation (threshold=10)  | 96.63 %       |  3.37 %
KNN (kdtree, K=5)      | L2 (Euclidean)  | Downsample (factor=2)        | 96.60 %       |  3.40 %
KNN (kdtree, K=5)      | L2 (Euclidean)  | Downsample (factor=4)        | 93.21 %       |  6.79 %
KNN (kdtree, K=5)      | L2 (Euclidean)  | Blur (factor=2)              | 97.58 %       |  2.42 %
KNN (kdtree, K=5)      | L2 (Euclidean)  | Sum (image into scalar)      | 18.33 %       | 81.67 %

## AutoParam

Use a random-chosen subset of training data as sample to choose
the best parameter `K` for our KNN Classifier. The result is

- Choose Distance: L3
- Choose K=3
- Result: Correct Ratio = 97.58%, Error Ratio = 2.42%
