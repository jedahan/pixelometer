#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    source.loadImage("source.tiff");
    source.update();
    buildMap(source);
    destination.allocate(source.width,source.height,OF_IMAGE_COLOR);
    destination.update();
    ofSetWindowShape(source.width*2, source.height);
}

//--------------------------------------------------------------
void testApp::update(){
}

//--------------------------------------------------------------
void testApp::draw(){
    source.draw(0,0);
    destination.draw(source.width,0);
}

//--------------------------------------------------------------
void testApp::buildMap(ofImage image) {
    // Create a list of all the colors
    for(int x=1; x<image.width-1; x++){
        for(int y=1; y<image.height-1; y++){
            ofColor c = image.getColor(x,y);
            if(findColorIndex(c)<0){
                colors.push_back(c);
            }
        }
    }

    cout << "There are " << colors.size() << " colors in this image" << endl;
    for(ofColor c:colors){
        cout << c << endl;
    }
    // Create an array of all zeros
    adjacency = new int[colors.size()*colors.size()]();

    // Populate the edges
    for(int x=1; x<image.width-1; x++){
        for(int y=1; y<image.height-1; y++){
            int from = findColorIndex(image.getColor(x,y));
            
            vector<ofPoint> neighbors;
            neighbors.push_back(ofPoint(x-1,y-1));
            neighbors.push_back(ofPoint(x-0,y-1));
            neighbors.push_back(ofPoint(x+1,y-1));
            neighbors.push_back(ofPoint(x-1,y-0));
            neighbors.push_back(ofPoint(x+1,y-0));
            neighbors.push_back(ofPoint(x-1,y+1));
            neighbors.push_back(ofPoint(x-0,y+1));
            neighbors.push_back(ofPoint(x+1,y+1));
            
            for(ofPoint neighbor : neighbors){
                int to = findColorIndex(image.getColor(neighbor.x,neighbor.y));
                adjacency[from*colors.size()+to]++;
            }
        }
    }
}

int testApp::findColorIndex(ofColor find){
    for(int i=0; i<colors.size();i++){
        if(colors[i]==find){
            return i;
        }
    }
    return -1;
}

//--------------------------------------------------------------
void testApp::makeImage(int x, int y) {
    destination.setColor(ofColor(0,0,0));
    ofColor color = source.getColor(x, y);

     for(int x=1; x<source.width-1; x++){
        for(int y=1; y<source.height-1; y++){
            int from = findColorIndex(color);
            
            int sum = 0;
            for(int to = 0;to<colors.size();to++){
                sum += adjacency[from*colors.size()+to];
            }
            
            int random = ofRandom(sum);
            int to = 0;

            for(sum = 0;to<colors.size();to++){
                sum += adjacency[from*colors.size()+to];
                if(sum >= random){ break; }
            }

            destination.setColor(x,y,colors[to]);
            color.set(colors[to]);
        }
    }
    destination.update();
}

void testApp::mousePressed(int x, int y, int button){
    makeImage(x,y);
}