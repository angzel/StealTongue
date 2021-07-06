#pragma once
#include "Resource.hpp"
#include "Button.hpp"
#include "Drum.hpp"

class SettingLayer : public Layer
{
	std::vector<Sprite*> mSettings;
	std::vector<Sprite*> mSelector;
	Button* mBack;
	Button* mCustom;
	Drum* mDrum;
	Sprite * mPlaying;
	std::shared_ptr<Action> mPlayingSchedule;
	Label * mTrialTips = nullptr;
	bool mIsChange = false;

public:
	SettingLayer();

	virtual Node * onTouchDown(AppTouch const & touch);
	
	virtual Node * onTouchMove(AppTouch const & touch) { return this; }
	
	virtual Node * onTouchUp(AppTouch const & touch) { return this; }
	
	virtual Node * onTouchCancel(AppTouch const & touch) { return this; }

	void changeSetting(int setting, float x);

	void moveCustomButton();

	void switchPlayDemo();
	void stopPlayDemo();

	void refresh();
	
	void onPro()
	{
		if(!mTrialTips) return;
		
		mTrialTips->remove();
		mTrialTips = nullptr;
	}
};
