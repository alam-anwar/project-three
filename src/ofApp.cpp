#include "ofApp.h"

using namespace std;
using namespace std::chrono;

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup();

    gui.add(N.setup("N", 50, 1, 100));
    gui.add(gen.setup("Randomly Generate"));
    gui.add(qsButton.setup("Quick Sort"));
    gui.add(msButton.setup("Merge Sort"));
    gui.add(rsButton.setup("Radix Sort"));
    gui.add(complexity.setup("complexity", ""));
    gui.add(time.setup("time", ""));

    generateRectangles(N);

    cooldown = 1000;
    lastClick = 0;

}

//--------------------------------------------------------------
void ofApp::update(){
        if (qsButton){
            auto start = high_resolution_clock::now();

            quickSort(rects, 0, rects.size() - 1);

            auto stop = high_resolution_clock::now();
            auto dur = duration_cast<microseconds>(stop - start);

            complexity.setup("complexity", "O(n*logn)");
            time.setup("time", to_string(dur.count()) + " ms");
        }
        else if (rsButton) {
            auto start = high_resolution_clock::now();

            radixSort(rects, rects.size());

            auto stop = high_resolution_clock::now();
            auto dur = duration_cast<microseconds>(stop - start);

            complexity.setup("complexity", "O(n*d)");
            time.setup("time", to_string(dur.count()) + " ms");
        }
        else if (msButton) {
            auto start = high_resolution_clock::now();

            mergeSort(rects, 0, rects.size() - 1);

            auto stop = high_resolution_clock::now();
            auto dur = duration_cast<microseconds>(stop - start);

            complexity.setup("complexity", "O(n*logn)");
            time.setup("time", to_string(dur.count()) + " ms");
        }
        else if (gen) {
            generateRectangles(N);
            complexity.setup("complexity", "");
            time.setup("time", "");
        }
}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();

    
    ofFill();
    ofSetColor(255,255,0);
    
    for (const auto& rect : rects) {
        ofDrawRectangle(rect);
    }
}

void ofApp::generateRectangles(int N) {
    rects.clear();

    float y = ofGetHeight() - 10;

    for (int i = 0; i < N; i++) {
        int height = (int)ofRandom(ofGetHeight() - 200);
        ofRectangle rect(i*15, y, 10, -height);
        rects.push_back(rect);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'q'){
        quickSort(rects, 0, rects.size() - 1);
    }
    else if (key == 'r') {
        radixSort(rects, rects.size());
    }
    else if (key == 'm') {
        mergeSort(rects, 0, rects.size() - 1);
    }
    else if (key == 'g'){
        generateRectangles(N);
    }
}

void ofApp::merge(vector<ofRectangle>& vec, int left, int mid, int right) {
    vector<int> mix;
    int i = left;
    int j = mid + 1;

    // mixing the two sides together.
    while (i <= mid && j <= right) {
        if ((int)vec[i].getHeight() <= (int)vec[j].getHeight()) {
            mix.push_back((int)vec[i].getHeight());
            i++;
        } else {
            mix.push_back((int)vec[j].getHeight());
            j++;
        }
    }

    // once one side is complete, add the rest of the other side to mix.
    while (i <= mid) {
        mix.push_back((int)vec[i].getHeight());
        i++;
    }
    while (j <= right) {
        mix.push_back((int)vec[j].getHeight());
        j++;
    }

    for (int k = left; k <= right; k++) {
        vec[k].setHeight(mix[k - left]);
    }
}

void ofApp::mergeSort(vector<ofRectangle>& vec, int left, int right) {
    auto start = high_resolution_clock::now();

    if(left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);
        merge(vec, left, mid, right);
    }

    auto stop = high_resolution_clock::now();
    auto dur = duration_cast<microseconds>(stop - start);
}


int ofApp::partition (vector<ofRectangle>& vec, int low, int high)
{
    int pivot = (int)vec[high].getHeight();
    int i = (low - 1);

    for (int j = low; j < high; j++)
    {
        if ((int)vec[j].getHeight() <= pivot)
        {
            i++;
            int iH = vec[i].getHeight();
            vec[i].setHeight(vec[j].getHeight());
            vec[j].setHeight(iH);
        }
    }
    int iH = vec[i+1].getHeight();
    vec[i+1].setHeight(vec[high].getHeight());
    vec[high].setHeight(iH);
    return (i + 1);
}

void ofApp::quickSort(vector<ofRectangle>& vec, int low, int high)
{
    auto start = high_resolution_clock::now();

    if (low < high)
    {
        int pivot = partition(rects, low, high);
        quickSort(rects, low, pivot - 1);
        quickSort(rects, pivot + 1, high);
    }

    auto stop = high_resolution_clock::now();
    auto dur = duration_cast<microseconds>(stop - start);
}

int ofApp::getMax(vector<int> vec)
{
    int max = vec[0];
    for (int num : vec)
        if (num > max)
            max = num;
    return max;
}

void ofApp::countSort(vector<int>& vec, int n, int exp)
{
    vector<int> result(n);
    vector<int> count(10, 0);

    for (int i = 0; i < n; ++i)
        count[(vec[i] / exp) % 10]++;

    for (int i = 1; i < 10; ++i)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; --i) {
        result[count[(vec[i] / exp) % 10] - 1] = vec[i];
        --count[(vec[i] / exp) % 10];
    }

    for (int i = 0; i < n; ++i)
        vec[i] = result[i];
}


void ofApp::radixSort(vector<ofRectangle>& vec, int n)
{
    vector<int> heights;

    for (const auto& rect : vec) {
        heights.push_back(-rect.getHeight());
    }

    auto start = high_resolution_clock::now();

    int max = getMax(heights);

    for (int exp = 1; max / exp > 0; exp *= 10)
        countSort(heights, n, exp);

    auto stop = high_resolution_clock::now();
    auto dur = duration_cast<microseconds>(stop - start);

    rects.clear();

    float y = ofGetHeight() - 10;

    for (int i = 0; i < heights.size(); i++) {
        int height = heights[heights.size()-1-i];
        ofRectangle rect(i*15, y, 10, -height);
        rects.push_back(rect);
    }
}
