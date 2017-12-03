#pragma once
#include "components.hpp"
#include <vector>
#include <jansson.h>
#include "widgets.hpp"
#include <iostream>

using namespace std;

namespace rack {

struct BidooColoredKnob : RoundKnob {
	bool focused = false;

	BidooColoredKnob() {
		setSVG(SVG::load(assetPlugin(plugin,"res/ComponentLibrary/BlackKnobBidoo.svg")));
		box.size = Vec(28, 28);
	}

	void draw(NVGcontext *vg) override {
			for (NSVGshape *shape = this->sw->svg->handle->shapes; shape != NULL; shape = shape->next) {
				std::string str(shape->id);
				if (str == "bidooKnob") {
					shape->fill.color = (((unsigned int)value*25) | ((unsigned int)0 << 8) | ((unsigned int)value*10 << 16));
					shape->fill.color |= (unsigned int)(255) << 24;
				}
			}
		RoundKnob::draw(vg);
	};

	void setValueNoEngine(float value) {
		this->value = clampf(value, fminf(minValue, maxValue), fmaxf(minValue, maxValue));
		this->dirty=true;
	};

	void onMouseDown(EventMouseDown &e) override {
		this->setValue(this->value);
		RoundKnob::onMouseDown(e);
		if (e.button == 1)
			focused = false;
	}

	void onDragMove(EventDragMove &e) override {
		RoundKnob::onDragMove(e);
		focused = true;
	}
};

struct BidooSpiralKnob : RoundKnob {
	BidooSpiralKnob() {
		setSVG(SVG::load(assetPlugin(plugin,"res/ComponentLibrary/SpiralKnobBidoo.svg")));
		box.size = Vec(28, 28);
	}
};


struct BidooColoredTrimpot : RoundKnob {
	BidooColoredTrimpot() {
		box.size = Vec(17, 17);
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		setSVG(SVG::load(assetPlugin(plugin,"res/ComponentLibrary/TrimpotBidoo.svg")));
	}

	void draw(NVGcontext *vg) override {
		for (NSVGshape *shape = this->sw->svg->handle->shapes; shape != NULL; shape = shape->next) {
			std::string str(shape->id);
			if (str == "bidooTrimPot") {
				if (value == 0) {
					shape->fill.color = (((unsigned int)128) | ((unsigned int)128 << 8) | ((unsigned int)128 << 16));
					shape->fill.color |= (unsigned int)(120) << 24;
				} else {
					shape->fill.color = (((unsigned int)255) | (((unsigned int)(205 - (value *15)))<< 8) | ((unsigned int)10 << 16));
					shape->fill.color |= ((unsigned int)255) << 24;
				}
			}
		}
		RoundKnob::draw(vg);
	};
};


struct BidooSlidePotLong : SVGSlider {
	BidooSlidePotLong() {
		snap = true;
		maxHandlePos = Vec(0, 0);
		minHandlePos = Vec(0, 84);
		background->svg = SVG::load(assetPlugin(plugin,"res/ComponentLibrary/bidooSlidePotLong.svg"));
		background->wrap();
		background->box.pos = Vec(0, 0);
		box.size = background->box.size;
		handle->svg = SVG::load(assetPlugin(plugin,"res/ComponentLibrary/bidooSlidePotHandle.svg"));
		handle->wrap();
	}

	void randomize() override {
  	setValue(roundf(rescalef(randomf(), 0.0, 1.0, minValue, maxValue)));
  }
};

struct BidooSlidePotShort : SVGSlider {
	BidooSlidePotShort() {
		snap = true;
		maxHandlePos = Vec(0, 0);
		minHandlePos = Vec(0, 60);
		background->svg = SVG::load(assetPlugin(plugin,"res/ComponentLibrary/bidooSlidePotShort.svg"));
		background->wrap();
		background->box.pos = Vec(0, 0);
		box.size = background->box.size;
		handle->svg = SVG::load(assetPlugin(plugin,"res/ComponentLibrary/bidooSlidePotHandle.svg"));
		handle->wrap();
	}

	void randomize() override {
  	setValue(roundf(rescalef(randomf(), 0.0, 1.0, minValue, maxValue)));
  }
};

struct BidooLongSlider : SVGSlider {
	bool focused = false;

	BidooLongSlider() {
		maxHandlePos = Vec(0, 0);
		minHandlePos = Vec(0, 84);
		background->svg = SVG::load(assetPlugin(plugin,"res/ComponentLibrary/bidooLongSlider.svg"));
		background->wrap();
		background->box.pos = Vec(0, 0);
		box.size = background->box.size;
		handle->svg = SVG::load(assetPlugin(plugin,"res/ComponentLibrary/bidooLongSliderHandle.svg"));
		handle->wrap();
	}

	void onMouseDown(EventMouseDown &e) override {
		SVGSlider::onMouseDown(e);
		focused = true;
	}

	void onMouseUp(EventMouseUp &e) override {
		SVGSlider::onMouseUp(e);
		focused = false;
	}

	void onDragStart(EventDragStart &e) override {
		SVGSlider::onDragStart(e);
		focused = true;
	}

	void onDragEnd(EventDragEnd &e) override {
		SVGSlider::onDragEnd(e);
		focused = false;
	}

	void onDragMove(EventDragMove &e) override {
		SVGSlider::onDragMove(e);
		focused = true;
	}
};


struct CKSS8 : SVGSwitch, ToggleSwitch {
	CKSS8() {
		addFrame(SVG::load(assetPlugin(plugin,"res/ComponentLibrary/CKSS8_0.svg")));
		addFrame(SVG::load(assetPlugin(plugin,"res/ComponentLibrary/CKSS8_1.svg")));
		addFrame(SVG::load(assetPlugin(plugin,"res/ComponentLibrary/CKSS8_2.svg")));
		addFrame(SVG::load(assetPlugin(plugin,"res/ComponentLibrary/CKSS8_3.svg")));
		addFrame(SVG::load(assetPlugin(plugin,"res/ComponentLibrary/CKSS8_4.svg")));
		addFrame(SVG::load(assetPlugin(plugin,"res/ComponentLibrary/CKSS8_5.svg")));
		addFrame(SVG::load(assetPlugin(plugin,"res/ComponentLibrary/CKSS8_6.svg")));
		addFrame(SVG::load(assetPlugin(plugin,"res/ComponentLibrary/CKSS8_7.svg")));
		sw->wrap();
		box.size = sw->box.size;
	}
};

struct CKSS4 : SVGSwitch, ToggleSwitch {
	CKSS4() {
		addFrame(SVG::load(assetPlugin(plugin,"res/ComponentLibrary/CKSS4_0.svg")));
		addFrame(SVG::load(assetPlugin(plugin,"res/ComponentLibrary/CKSS4_1.svg")));
		addFrame(SVG::load(assetPlugin(plugin,"res/ComponentLibrary/CKSS4_2.svg")));
		addFrame(SVG::load(assetPlugin(plugin,"res/ComponentLibrary/CKSS4_3.svg")));
		sw->wrap();
		box.size = sw->box.size;
	}
};

struct TinyPJ301MPort : SVGPort {
	TinyPJ301MPort() {
		background->svg = SVG::load(assetPlugin(plugin, "res/TinyPJ301M.svg"));
		background->wrap();
		box.size = background->box.size;
	}
};

struct MiniLEDButton : SVGSwitch, MomentarySwitch {
	MiniLEDButton() {
		addFrame(SVG::load(assetPlugin(plugin,"res/ComponentLibrary/miniLEDButton.svg")));
		sw->wrap();
		box.size = sw->box.size;
	}
};


} // namespace rack
