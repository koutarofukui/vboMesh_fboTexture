#pragma once

// tig: uncomment the following line to use programmable GL , and GLSL 150
// otherwise this example will run using OpenGL 2.0 / GLSL 1.20

#define USE_PROGRAMMABLE_GL 

// note that if you use programmable GL, a different set of shaders will be loaded.
// see testApp.cpp


#include "ofMain.h"

#define WIDTH 128
#define HEIGHT 128

class testApp : public ofBaseApp{
	
	ofVboMesh	mVboBox;
	
	ofEasyCam	mCamMain;

	ofPtr<ofShader>	mShdInstanced;
	ofTexture		mTexDepth;
    
    ofFbo fbo;
	
	bool isShaderDirty;
    
    //fbo update variables
    float size = 0;
    float color = 0;
	
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
};
