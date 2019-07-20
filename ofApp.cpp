#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	auto color_flag = true;
	for (auto radius = 150; radius < 720; radius += 20) {

		auto noise_deg = ofMap(ofNoise(radius * 0.1 + ofGetFrameNum() * 0.003), 0, 1, -360, 360);

		ofPushMatrix();
		ofRotate(noise_deg);

		auto small_radius = radius - 20;
		auto big_radius = radius + 20;
		vector<glm::vec2> small_circle;
		vector<glm::vec2> big_circle;
		for (auto deg = 0; deg < 360; deg += 1) {

			small_circle.push_back(glm::vec2(small_radius * cos(deg * DEG_TO_RAD), small_radius * sin(deg * DEG_TO_RAD)));
			big_circle.push_back(glm::vec2(big_radius * cos(deg * DEG_TO_RAD), big_radius * sin(deg * DEG_TO_RAD)));

			if (deg % 30 == 0) {

				auto in_radius = radius - 10;
				auto out_radius = radius + 10;
				vector<glm::vec2> in;
				vector<glm::vec2> out;
				for (auto tmp_deg = deg; tmp_deg <= deg + 30; tmp_deg += 1) {

					in.push_back(glm::vec2(in_radius * cos(tmp_deg * DEG_TO_RAD), in_radius * sin(tmp_deg * DEG_TO_RAD)));
					out.push_back(glm::vec2(out_radius * cos(tmp_deg * DEG_TO_RAD), out_radius * sin(tmp_deg * DEG_TO_RAD)));
				}

				reverse(out.begin(), out.end());

				ofFill();
				ofSetColor(color_flag ? 239 : 39);

				ofBeginShape();
				ofVertices(in);
				ofVertices(out);
				ofEndShape(true);

				ofNoFill();
				ofSetColor(color_flag ? 139 : 239);

				ofBeginShape();
				ofVertices(in);
				ofVertices(out);
				ofEndShape(true);

				color_flag = !color_flag;
			}
		}

		ofPopMatrix();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}