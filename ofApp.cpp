#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	camWidth = 640;
	camHeight = 480;

	vidGrabber.setVerbose(true);
	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(10);
	vidGrabber.initGrabber(camWidth, camHeight);

	pixels.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
	finalImage.allocate(pixels);
	pixels.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
	finalImageInverted.allocate(pixels);
	ofSetFrameRate(120);

}

//--------------------------------------------------------------
void ofApp::update(){
	vidGrabber.update();
	if (counter >= 60) {
		ofPixelsRef pixelRef = vidGrabber.getPixels();
		ofImage image;
		image.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
		image.setFromPixels(pixelRef);
		images.push_back(image);
		counter = 0;
	}
	else {
		counter++;
	}

	if (images.size() > 10) {
		images.erase(images.begin());
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	vidGrabber.draw(1045, 100, -1013, 760);

	int n = images.size();
	for (int i = 0; i < n; i++) {
		images[i].draw(ofGetWindowWidth()-710, ofGetWindowHeight() /10 * i, -1280 / 10, 960 / 10);
	}

	finalImage.draw(ofGetWindowWidth() - 675, 35);

	finalImageInverted.draw(ofGetWindowWidth() - 675, 510);

	ofDrawBitmapString("MOVE!POSE!", 20, ofGetWindowHeight()- 60);
	ofDrawBitmapString("PRESS: TAB, BACKSPACE", 20, ofGetWindowHeight()-50);
	ofDrawBitmapString("it will be slow so please don't kill my computer :)", 20, ofGetWindowHeight() - 40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	int n = images.size();
	for (int x = 0; x < 640; x++) {
		for (int y = 0; y < 480; y++) {
			int r = 0, g = 0, b = 0;
			for (int i = 0; i < n; i++) {
				r += images[i].getColor(x, y).r;
				g += images[i].getColor(x, y).g;
				b += images[i].getColor(x, y).b;
			}
			//            cout << r << " " << g << " " << b << endl;
			pixels.setColor(x, y, ofColor(r / n, g / n, b / n));
		}
	}

	if (key == OF_KEY_TAB) {
		finalImage.loadData(pixels);
	}

	for (int x = 0; x < 640; x++) {
		for (int y = 0; y < 480; y++) {
			int r = 0, g = 0, b = 0;
			for (int i = 0; i < n; i++) {
				r += 255-images[i].getColor(x, y).r;
				g += 255-images[i].getColor(x, y).g;
				b += 255-images[i].getColor(x, y).b;
			}
			pixels.setColor(x, y, ofColor(r / n, g / n, b / n));
		}
	}
	if (key == OF_KEY_BACKSPACE) {
		finalImageInverted.loadData(pixels);
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
