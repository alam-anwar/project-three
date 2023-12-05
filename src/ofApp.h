#pragma once

#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <chrono>

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
        // gui elements
        ofxPanel gui;
        ofxIntSlider N;
        ofxButton gen;
        ofxButton qsButton;
        ofxButton msButton;
        ofxButton rsButton;
        ofxLabel complexity;
        ofxLabel time;

        // main structure to store rectangles
        std::vector<ofRectangle> rects;
        // container that keeps heights for convenience during radix sort
        std::vector<int> radixHeights;

        // cooldown time to prevent button from repeatedly executing on single click
        int cooldown;
        long long lastClick;

        // function to generate N randomly sized rectangles 
        void generateRectangles(int N);

        // quick sort and helper function
        void quickSort(vector<ofRectangle>& vec, int low, int high);
        int partition (vector<ofRectangle>& vec, int low, int high);

        // merge sort and helper function
        void merge(vector<ofRectangle>& vec, int left, int mid, int right);
        void mergeSort(vector<ofRectangle>& vec, int left, int right);

        // radix sort and helper functions
        int getMax(vector<int> vec);
        void countSort(vector<int>& vec, int n, int exp);
        void radixSort(vector<ofRectangle>& vec, int n);
        
        // openFrameworks native functions
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);



		
};
