#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // set the size of the window
    ofSetWindowShape(window_w, window_h);

    size = window_w;
    position = (float *)malloc(sizeof(float)*size);
    velocity = (float *)malloc(sizeof(float)*size);
    sand_positions = (int *)malloc(sizeof(int)*size);

    for(int x = 0; x < size; x++)
    {
        position[x] = window_h/2;
        velocity[x] = 0.0;//10*ofRandomf();

        if(x < size/2)
        {
            sand_positions[x] = window_h/3;
        }
        else
        {
            sand_positions[x] = 0;
        }

    }

}

//--------------------------------------------------------------
void ofApp::update()
{

    for(int i = 0; i < 8; i++)
    {
        simulationStep();
    }



}

void ofApp::simulationStep()
{

     // Update Velocities.
    for(int x = 0; x < size; x++)
    {
        int xP = max(x - 1, 0);
        int xN = min(x + 1, size - 1);
        velocity[x] += (position[xN] + sand_positions[xN] + position[xP] + sand_positions[xP])/2.0 - position[x] - sand_positions[x];

        // Damping.
        velocity[x] *= 0.999;
    }

    // Update Positions.
    for(int x = 0; x < size; x++)
    {
        position[x] += velocity[x];

    }

    // Update the sand positions.
    for(int x = 1; x < size; x += 2)
    {
        int xN = min(x + 1, size - 1);

        if(sand_positions[x - 1] > sand_positions[x] + 1)
        {
            int diff = sand_positions[x - 1] - sand_positions[x];
            sand_positions[x] += diff/2;
            sand_positions[x - 1] -= diff/2;
        }

        if(sand_positions[xN] > sand_positions[x] + 1)
        {
            int diff = sand_positions[xN] - sand_positions[x];
            sand_positions[x]  += diff/2;
            sand_positions[xN] -= diff/2;
        }

        if(sand_positions[x - 1] + 1 < sand_positions[x])
        {
            int diff = sand_positions[x] - sand_positions[x - 1];
            sand_positions[x] -= diff;
            sand_positions[x - 1] += diff;
        }

        if(sand_positions[xN] + 1 < sand_positions[x])
        {
            int diff = sand_positions[x] - sand_positions[xN];
            sand_positions[x] -= diff/2;
            sand_positions[xN]+= diff/2;
        }

    }

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);
    ofSetColor(100, 100, 255);
    for(int x = 0; x < size; x++)
    {
        int sand_h = sand_positions[x];
        int water_y = position[x];
        ofLine(x, window_h - sand_h, x, window_h - sand_h - position[x]);
    }

    // Draw the sand.
    ofSetColor(255, 100, 100);
    for(int x = 0; x < size; x++)
    {
        int sand_h = sand_positions[x];
        ofLine(x, window_h, x, window_h - sand_h);
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

    position[x] -= y;
    position[x - 1] -= y/2;
    position[x + 1] -= y/2;

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
