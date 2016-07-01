#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableAlphaBlending();
    ofEnableDepthTest();

    light.setup();
    light.enable();
    light.setPosition(ofVec3f(400,300,200));
    light.lookAt(ofVec3f(0,0,0));

    map<string, float> constants;
    constants.insert(make_pair("R", 1.456));

    // tree on which it will be applied a texture
    tree.setAxiom("A(100)");
    tree.setRules({"A(s) -> F(s)[+A(s/R)][-A(s/R)]"});
    tree.setRandomYRotation(true);
    tree.setConstants(constants);
    tree.setStep(8);
    tree.setScaleWidth(true);
    tree.setStepWidth(50.5);
    tree.setStepLength(200);
    tree.build();
    uResolution = ofVec3f(ofGetWidth(), ofGetHeight());

    if(ofIsGLProgrammableRenderer()){
        //I'm using opengl 4.1 that support the programmable pipeline
        //shader.load("shaders_gl3/noise.vert", "shaders_gl3/noise.frag");
        shader.load("shaders_gl3/colors.vert", "shaders_gl3/colors.frag");
    }

    gui.setup();
    gui.add(scale.set("scale", 10.f, 1.f, 20.f));
    gui.add(lightPos.set("lightPosition",
                         ofVec3f(400,300,200), ofVec3f(-800,-800,-800), ofVec3f(800,800,800)));
    gui.add(materialColor.setup("material color",
                                ofColor(0, 255, 0), ofColor(0, 0), ofColor(255, 255)));
    ofSetVerticalSync(true);
    tree.computeBoundingBox();
    float treeWidth = abs(tree.getBoundingBox().min.x) + tree.getBoundingBox().max.x;
    float treeHeight = abs(tree.getBoundingBox().min.y) + tree.getBoundingBox().max.y;
    uTreeResolution = ofVec2f(treeWidth, treeHeight);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();

    shader.begin();
    shader.setUniform1f("uTime", ofGetElapsedTimef());
    shader.setUniform2f("mouse", mouseX - ofGetWidth()/2, ofGetHeight()/2-mouseY );
    shader.setUniform3f("uLightPosition", lightPos);
    shader.setUniform4f("uMaterialColor", ofColor(materialColor));
    shader.setUniform2f("uResolution", uResolution );
    shader.setUniform2f("uTreeResolution", uTreeResolution );

    tree.draw();

    shader.end();
    cam.end();

    maybeDrawGui();
}

void ofApp::maybeDrawGui(){
    if(drawGui){
        ofDisableDepthTest();
        gui.draw();
        ofEnableDepthTest();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'g'){
        drawGui = !drawGui;
    }
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

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
