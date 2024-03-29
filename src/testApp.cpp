#include "testApp.h"

/**
 * tig: This example shows how to draw instanced geometry using 
 * ofVboMesh.drawInstanced() and matching GLSL shader code.
 * The most interesting things will happen in the shader files, 
 * and in the draw() method, where everything is set up properly 
 * to allow instanced rendering.
 *
 * Note that you can feed any ofVboMesh to the instanced draw method.
 *
 */

//--------------------------------------------------------------
void testApp::setup(){
    
    fbo.allocate(WIDTH, HEIGHT, GL_RGBA);
	
	// initialize variables:
	
	isShaderDirty = true;  // this flag will tell us whether to reload our shader from disk.
						   // this allows you to change your shaders without having to restart
						   // your app. we'll set it up so that pressing the SPACE key on your
						   // keyboard will reload the shader.
	
	// initialize screen, lock framerate to vsync:

	ofSetFrameRate(0);
	ofSetVerticalSync(true);

	
	// generate a box vboMesh from a primitive.
	
	ofBoxPrimitive tmpBox;
	// set the size to be 2 units.
	tmpBox.set(1);
	
	mVboBox = tmpBox.getMesh();
	

	mCamMain.setupPerspective(false,60,0,10000);
	
}

//--------------------------------------------------------------
void testApp::update(){
    //fbo update data
    if (size < 60 ) {
        size += 0.25;
        if(color < 255)
        {
            color += 1;
        }else{
            color = 255;
        }
    }else{
        size = 0;
        color = 0;
    }
    
    
    //shading
	if (isShaderDirty){
		
		// only reload the shader if it is 'dirty', i.e. the user has either requested reloading
		// or the 'isShaderDirty' flag has been initialized to true in setup()
		
		// Since we are using an ofPtr around the shader, the old shader will get destroyed
		// automatically as soon as we assign a new shader object to our mShdInstanced.
		
		ofLogNotice() << "Reloading Shader.";
		mShdInstanced = ofPtr<ofShader>(new ofShader());
		// most of the instanced drawing magic happens in the shaders:
#ifdef USE_PROGRAMMABLE_GL
        
		// if we are using programmable GL, we load the GLSL version 150 shader pair.
		mShdInstanced->load("shaders/instanced.vert", "shaders/instanced.frag");
#else
		// if we are using fixed function GL, we load the GLSL version 120 shader pair.
		mShdInstanced->load("shaders/instanced_120.vert", "shaders/instanced_120.frag");
#endif
		GLint err = glGetError();
		if (err != GL_NO_ERROR){
			ofLogNotice() << "Load Shader came back with GL error:	" << err;
		}
		
		isShaderDirty = false;
	}
	
	ofSetWindowTitle(ofToString(ofGetFrameRate(), 2));
	
}

//--------------------------------------------------------------
void testApp::draw(){

	ofEnableDepthTest();
	// we don't care about alpha blending in this example, and by default alpha blending is on in openFrameworks > 0.8.0
	// so we de-activate it for now.
	//ofDisableAlphaBlending();
    //ofDisableArbTex();

        //texture FBO
        fbo.begin();
            ofClear(0);
            ofBackground(0);
            ofSetColor(color);
            ofFill();
            ofCircle(WIDTH/2, HEIGHT/2, size);
        fbo.end();
    
    //ofEnableArbTex();
    
	ofBackgroundGradient(ofColor(18,33,54), ofColor(18,22,28));
	
	ofSetColor(255, 255, 255, 127);
    
    //fbo.getTextureReference().bind();
	mCamMain.begin();
    
        // bind the shader
        mShdInstanced->begin();
            // give the shader access to our texture
            mShdInstanced->setUniformTexture("tex0", fbo, fbo.getTextureReference().getTextureData().textureID);

            // we only want to see triangles facing the camera.
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);

            // let's draw 128 * 128 == 16384 boxes !
            mVboBox.drawInstanced(OF_MESH_FILL, 128*128);

            glDisable(GL_CULL_FACE);
        mShdInstanced->end();
        
	mCamMain.end();
    //fbo.getTextureReference().unbind();

	ofDisableDepthTest();
    
    //display fbo texture
    ofDisableAlphaBlending();
    
    fbo.draw(0, 0);

	ofSetColor(ofColor::white);
	ofDrawBitmapString("Use mouse to move camera.\nPress 'f' to toggle fullscreen;\nSPACEBAR to reload shader.", 10, 20);
	
	ofEnableAlphaBlending();
	
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
	switch (key) {
		case ' ':
			isShaderDirty = true;
			// mark the shader as dirty - this will reload the shader.
			break;
		case 'f':
			ofToggleFullscreen();
			break;
		default:
			break;
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
	
}
