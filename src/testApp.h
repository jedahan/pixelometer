#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void mousePressed(int x, int y, int button);

		ofImage source, destination;
		vector<ofColor> colors;
		int *adjacency;

		void makeImage(int x, int y);
		void buildMap(ofImage image);
		int findColorIndex(ofColor find);
};
