#pragma once

#include <vector>
#include "zen_vap.h"
#include "zen_audio_player.h"
#include "zen_localization.h"

using namespace Zen::Vap;
using namespace Zen;

class MainScene;

typedef Zen::Point2 Pt2;
class Res {
public:
	static MainScene * sMainScene;
	/**
	 * Global View Size
	 */
	static void SetViewSize(float w, float h);
	static float W();
	static float H();

	/**
	 * basic config
	 */
	static const int sThemeStyleCount = 4;
	static const int sDrumStyleCount = 4;
	static const int sTongueStyleCount = 4;
	static const int sVoiceStyleCount = 5;
	static const int sPadStyleCount = 4;

	struct Config {
		int8_t themeStyle = 0; // main bg
		int8_t drumStyle = 0; // drum bg
		int8_t tongueStyle = 0; // tongue style
		int8_t voiceStyle = 0; // sound style
		int8_t padStyle = 0;
	};
	struct TuneConfig
	{
		std::vector<int8_t> keyPads[sPadStyleCount];
	};

	static Zen::Localization local;

	static Config sDefaultConfig;
	static TuneConfig sTuneConfig;
	
	static void LoadConfig();

	static void LoadResource();

	static bool IsPro();

	static void SetPro();

	static void SaveConfig();

	static void SaveCustomKeys();

	static void SetCustomKey(int key_index, int tune_index);

	static std::shared_ptr<FontBrush> GetTuneNameFont();
	
	static std::shared_ptr<FontBrush> GetTextFont();
	/** Audio
	 */

	static const int sAudioCount = 17;

	struct AudioRes {
		int base;
		float pitch;
		const char * name;
		int high;
		int name_no;
	};

	static AudioRes const sAudios[sAudioCount];

	static std::string GetTuneName(int tune_index);

	static void Play(int key_index);

	static void PlayTune(int tune_index, int voice);

	static int GetKeyCount(int pad);

	static int GetTuneIndex(int index, int pad);

	static bool IsPointIn(Pt2 p, Pt2 pos, Size2 size) {
		return fabs(p.x - pos.x) < fabs(size.w/2) && fabs(p.y - pos.y) < fabs(size.h/2);
	}

	/** images
	 */


	static std::shared_ptr<Texture> GetMainBG(int index = 0);
	static std::shared_ptr<Texture> GetDrumBG(int index = 0);
	static std::shared_ptr<Texture> GetTongueImage(int index = 0);

	static std::shared_ptr<Texture> GetButton(std::string const & name);

	/** setting Resource */
	struct SettingRes {
		int type;
		int options_count;
		std::string name;
		std::string image;
		
	};
	static const int sSettingCount = 5;

	static SettingRes sSettings[sSettingCount];

};

//template<typename _Container>
//class Base
//{
//protected:
//	_Container * mView;
//public:
//	Base()
//	{
//		mView = _Container::Create();
//	}
//	void addTo(ContainerNode * parent)
//	{
//		parent->addChild(mView);
//	}
//	void setVisible(bool v)
//	{
//		mView->setVisible(v);
//	}
//	_Container * getView()
//	{
//		return mView;
//	}
//};
