#pragma once

#include "Resource.hpp"
#include "Drum.hpp"
#include "Button.hpp"

class CustomLayer : public Layer
{
	Drum * mDrum;
	Button * mOK;

	Sprite * mSelector;
	Sprite * mKeysArea;
	int mSelectedKeyIndex = -1;
	Pt2 mKeyPos0;
	Pt2 mKeyDiss;

	bool mIsChange = false;
public:
	CustomLayer();

	void resetPad();

	void selectKey(int index);

	virtual Node* onTouchDown(AppTouch const & touch) override;

};
