#pragma once

#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
        ofxPanel gui;
        ofxIntSlider N;
        ofxButton button;

        std::vector<ofRectangle> rects;
        std::vector<int> radixHeights;
        
		void setup();
		void update();
		void draw();

        void generateRectangles(int N);
        void rect_swap(ofRectangle& r1, ofRectangle& r2);

        void quickSort(vector<ofRectangle>& vec, int low, int high);
        int partition (vector<ofRectangle>& vec, int low, int high);

        void merge(vector<ofRectangle>& vec, int left, int mid, int right);
        void mergeSort(vector<ofRectangle>& vec, int left, int right);


        int getMax(vector<int> vec);
        void countSort(vector<int>& vec, int n, int exp);
        void radixSort(vector<ofRectangle>& vec, int n);

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
