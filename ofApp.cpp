#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(1.5);
	ofSetCircleResolution(60);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->line.clear();

	auto span = 8;
	auto radius_span = 10;
	for (auto deg = 0; deg < 360; deg += 12) {

		for (auto radius = 150; radius <= 720; radius += radius_span) {

			auto prev_location = glm::vec2((radius - radius_span) * cos(deg * DEG_TO_RAD), (radius - radius_span) * sin(deg * DEG_TO_RAD));
			auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
			auto next_location = glm::vec2((radius + radius_span) * cos(deg * DEG_TO_RAD), (radius + radius_span) * sin(deg * DEG_TO_RAD));

			auto left = glm::vec2(radius * cos((deg + span * 0.5) * DEG_TO_RAD), radius * sin((deg + span * 0.5) * DEG_TO_RAD));
			auto right = glm::vec2(radius * cos((deg - span * 0.5) * DEG_TO_RAD), radius * sin((deg - span * 0.5) * DEG_TO_RAD));
			auto next_left = glm::vec2((radius + radius_span) * cos((deg + span * 0.5) * DEG_TO_RAD), (radius + radius_span) * sin((deg + span * 0.5) * DEG_TO_RAD));
			auto next_right = glm::vec2((radius + radius_span) * cos((deg - span * 0.5) * DEG_TO_RAD), (radius + radius_span) * sin((deg - span * 0.5) * DEG_TO_RAD));

			auto prev_noise_value = ofNoise(glm::vec3(prev_location * 0.01, ofGetFrameNum() * 0.0085));
			auto noise_value = ofNoise(glm::vec3(location * 0.01, ofGetFrameNum() * 0.0085));
			auto next_noise_value = ofNoise(glm::vec3(next_location * 0.01, ofGetFrameNum() * 0.0085));
			auto threshold = 0.6;
			if (noise_value < threshold) {

				this->face.addVertex(glm::vec3(left, 0));
				this->face.addVertex(glm::vec3(next_left, 0));
				this->face.addVertex(glm::vec3(next_right, 0));
				this->face.addVertex(glm::vec3(right, 0));

				this->face.addVertex(glm::vec3(left, 150));
				this->face.addVertex(glm::vec3(next_left, 150));
				this->face.addVertex(glm::vec3(next_right, 150));
				this->face.addVertex(glm::vec3(right, 150));

				this->line.addVertex(glm::vec3(left, 0));
				this->line.addVertex(glm::vec3(next_left, 0));
				this->line.addVertex(glm::vec3(next_right, 0));
				this->line.addVertex(glm::vec3(right, 0));

				this->line.addVertex(glm::vec3(left, 150));
				this->line.addVertex(glm::vec3(next_left, 150));
				this->line.addVertex(glm::vec3(next_right, 150));
				this->line.addVertex(glm::vec3(right, 150));

				this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 2); this->face.addIndex(this->face.getNumVertices() - 3);
				this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 3); this->face.addIndex(this->face.getNumVertices() - 4);

				this->face.addIndex(this->face.getNumVertices() - 5); this->face.addIndex(this->face.getNumVertices() - 6); this->face.addIndex(this->face.getNumVertices() - 7);
				this->face.addIndex(this->face.getNumVertices() - 5); this->face.addIndex(this->face.getNumVertices() - 7); this->face.addIndex(this->face.getNumVertices() - 8);

				this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 5); this->face.addIndex(this->face.getNumVertices() - 6);
				this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 6); this->face.addIndex(this->face.getNumVertices() - 2);

				this->face.addIndex(this->face.getNumVertices() - 4); this->face.addIndex(this->face.getNumVertices() - 7); this->face.addIndex(this->face.getNumVertices() - 8);
				this->face.addIndex(this->face.getNumVertices() - 4); this->face.addIndex(this->face.getNumVertices() - 7); this->face.addIndex(this->face.getNumVertices() - 3);

				this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
				this->line.addIndex(this->line.getNumVertices() - 3); this->line.addIndex(this->line.getNumVertices() - 4);

				this->line.addIndex(this->line.getNumVertices() - 5); this->line.addIndex(this->line.getNumVertices() - 6);
				this->line.addIndex(this->line.getNumVertices() - 7); this->line.addIndex(this->line.getNumVertices() - 8);

				if (radius == 150 || prev_noise_value > threshold) {

					this->face.addIndex(this->face.getNumVertices() - 4); this->face.addIndex(this->face.getNumVertices() - 8); this->face.addIndex(this->face.getNumVertices() - 5);
					this->face.addIndex(this->face.getNumVertices() - 4); this->face.addIndex(this->face.getNumVertices() - 5); this->face.addIndex(this->face.getNumVertices() - 1);

					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 4);
					this->line.addIndex(this->line.getNumVertices() - 5); this->line.addIndex(this->line.getNumVertices() - 8);

					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 5);
					this->line.addIndex(this->line.getNumVertices() - 4); this->line.addIndex(this->line.getNumVertices() - 8);
				}
				if (radius == 360 || next_noise_value > threshold) {

					this->face.addIndex(this->face.getNumVertices() - 3); this->face.addIndex(this->face.getNumVertices() - 7); this->face.addIndex(this->face.getNumVertices() - 6);
					this->face.addIndex(this->face.getNumVertices() - 3); this->face.addIndex(this->face.getNumVertices() - 6); this->face.addIndex(this->face.getNumVertices() - 2);

					this->line.addIndex(this->line.getNumVertices() - 2); this->line.addIndex(this->line.getNumVertices() - 3);
					this->line.addIndex(this->line.getNumVertices() - 6); this->line.addIndex(this->line.getNumVertices() - 7);

					this->line.addIndex(this->line.getNumVertices() - 2); this->line.addIndex(this->line.getNumVertices() - 6);
					this->line.addIndex(this->line.getNumVertices() - 3); this->line.addIndex(this->line.getNumVertices() - 7);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(315);
	ofRotateZ(ofGetFrameNum() * 0.3333333);

	ofSetColor(0);
	ofFill();
	ofDrawCircle(glm::vec2(), 135);

	this->face.draw();

	ofSetColor(255);
	ofNoFill();
	ofDrawCircle(glm::vec2(), 135);

	this->line.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}