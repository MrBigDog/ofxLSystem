#pragma once

#include "ofMain.h"
#include "ofxLSystem.h"
#include "ofParameter.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    // added only for the fakeDropdown
    //void exit();

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
    void selectedThetaChanghed(float & selectedTheta);
    void selectedDepthChanghed(int & selectedDepth);
    void fileSaved(int & file);

private:
    bool clickNotOnTheGui(int x, int y);
    void loadSettings(string filename = "first.xml");
    void readFilesDirectory();
    map<string,float> getConstants(string _constants) const;
    void startLSystem(
                      string axiom,
                      string singleRule,
                      float theta,
                      int depth,
                      ofVec3f position,
                      string constants);
    void maybeDrawGui();
    string trim(string str);
    bool drawGui = true;
    int selected;

    ofxPanel gui;
    ofParameter<bool> vSync;

    //LSystem parameters
    ofParameter<string> selectedRule;
    ofParameter<string> definedConstant;
    ofParameter<string> axiom;
    ofParameter<int>    selectedDepth;
    unsigned int oldDepth = 1;
    ofParameter<float>  selectedTheta;
    ofxColorSlider bgColor;
    ofxColorSlider treeColor;
    ofxButton addGenerationButton;

    vector<string> fileNames;
    ofDirectory dir;

    ofEasyCam        cam;
    ofLight          light;
    ofxLSystem          lsystem;
    ofPlanePrimitive plane;
    ofMaterial       material;
    ofTrueTypeFont   font;
    ofXml            settings;
};
