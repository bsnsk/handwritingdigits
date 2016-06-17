//
// Created by Shuyang Shi on 16/6/16.
//

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
 * Downsample the image data
 *  input:
 *      vec - vector <Data> or vector <DataWithLabel>
 *  factor:
 *      Number of pixels out of which one pixel
 *      remains after the processing.
 */
template <typename T>
void downsample(vector <T> &vec) {
    static int factor = 2;
    for (auto data=vec.begin(); data!=vec.end(); data++){
        typename T::DataType newData;
        for (int i = data->val.size()-1; i >= 0; i--)
            if (i % factor == 0)
                newData.push_back(data->val[i]);
        data->val = newData;
    }
}

/*
 * Scale the image data
 *  input:
 *      vec - vector <Data> or vector <DataWithLabel>
 *      width - image data width
 *          (used to determine neighboring pixels)
 *  factor:
 *      Number of pixels out of which one pixel
        mains after the processing.
 */
template <typename T>
void blur(vector <T> &vec, int width = 28) {
    static int factor = 2;
    for (auto data=vec.begin(); data!=vec.end(); data++){
        typename T::DataType newData;
        int height = data->val.size() / width;
        for (int x = factor - 1; x <= height - factor; x++)
            for (int y = factor - 1; y <= width - factor; y++){
                int sum = 0;
                for (int dx = 1 - factor; dx < factor; dx++)
                    for (int dy = 1 - factor; dy < factor; dy++)
                        sum += data->val[(x + dx) * width + (y + dy)];
                newData.push_back(sum / (factor * 2 - 1) * (factor * 2 - 1));
            }
        data->val = newData;
    }
}

/*
 * Sum the image data into a scalar
 *  input:
 *      vec - vector <Data> or vector <DataWithLabel>
 */
template <typename T>
void sum2scalar(vector <T> &vec) {
    for (auto data=vec.begin(); data!=vec.end(); data++){
        int sum = 0;
        for (int i = data->val.size()-1; i >= 0; i--)
            sum += data->val[i];
        data->val.clear();
        data->val.push_back(sum);
    }
}
