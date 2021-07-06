//
//  Resource.cpp
//  drum-chinese
//
//  Created by lover on 2019/7/31.
//  Copyright © 2019 lover. All rights reserved.
//

#include "Resource.hpp"
#include "zen_random.h"
#include "zen_utils.h"
#include "zen_cast.h"
#include "zen_image_jpg.h"
#include "zen_image_png.h"
#include "zen_audio_wav.h"

#define TEST_FREE 1

static float _W = 900;
static float _H = 1600;

MainScene * Res::sMainScene = 0;

void Res::SetViewSize(float w, float h)
{
	_W = w;
	_H = h;
}
float Res::W()
{
	return _W;
}
float Res::H()
{
	return _H;
}
//F、9/8F、5/4F、4/3F、3/2F、5/3F、15/8F
Res::AudioRes const Res::sAudios[Res::sAudioCount] = {
	{ 1, 3.f/4,   "G", 3, 5 },
	{ 1, 5.f/6,   "A", 3, 6 },
	{ 1, 15.f/16, "B", 3, 7 },
	{ 1, 1.f,     "C", 4, 1 },
	{ 1, 9.f/8,   "D", 4, 2 },
	{ 1, 5.f/4,   "E", 4, 3 },
	{ 1, 4.f/3,   "F", 4, 4 },
	
	{ 2, 3.f/4,   "G", 4, 5 },
	{ 2, 5.f/6,   "A", 4, 6 },
	{ 2, 15.f/16, "B", 4, 7 },
	{ 2, 1.f,     "C", 5, 1 },
	{ 2, 9.f/8,   "D", 5, 2 },
	{ 2, 5.f/4,   "E", 5, 3 },
	{ 2, 4.f/3,   "F", 5, 4 },
	
	{ 4, 3.f/4,   "G", 5, 5 },
	{ 4, 5.f/6,   "A", 5, 6 },
	{ 4, 15.f/16, "B", 5, 7 },
};

Res::Config Res::sDefaultConfig;
Res::TuneConfig Res::sTuneConfig;

static inline void _FixConfigValue(int8_t & v, int min, int max)
{
	if(v < min || v >= max) v = min;
}
static void _FixDefaultConfig()
{
	auto & c = Res::sDefaultConfig;
	_FixConfigValue(c.drumStyle, 0, Res::sDrumStyleCount);
	_FixConfigValue(c.themeStyle, 0, Res::sThemeStyleCount);
	_FixConfigValue(c.padStyle, 0, Res::sPadStyleCount);
	_FixConfigValue(c.tongueStyle, 0, Res::sTongueStyleCount);
	_FixConfigValue(c.voiceStyle, 0, Res::sVoiceStyleCount);
}

static void _FixCustomKey(int8_t & v)
{
	if(v < 0 || v >= Res::sAudioCount) v = -1;
}
static void LoadCustomKeys()
{
	for(int i = 2; i < 4; ++i)
	{
		auto & v = Res::sTuneConfig.keyPads[i];
		auto & d = Res::sTuneConfig.keyPads[i%2];
		char name[] = "pad?";
		name[3] = '0' + i;
		auto data = Zen::Utils::Get()->loadDocument(name);
		if(data.size() == d.size())
		{
			v.assign(data.begin(), data.end());
			for(auto & i : v) _FixCustomKey(i);
		}
		else
		{
			v = d;
		}
	}
}

static bool sIsPro = false;

void _LoadPro()
{
#if TEST_FREE
	sIsPro = true;
	return;
#else
	auto data = Zen::Utils::Get()->loadDocument("pro");
	if(data.size() != 16) return;
	
	auto uid = Zen::Utils::Get()->getAppID();
	if(uid.size() == 0) return;
	
	int value = 0;
	for(auto i : uid)
	{
		value += i * i + i;
	}
	Zen::Random r;
	r.reset(value);
	
	for(int i = 0; i < 16; ++i)
	{
		if(r.next(256) == data[i]) continue;
		return;
	}
	sIsPro = true;
#endif
}
void _SavePro()
{
	auto uid = Zen::Utils::Get()->getAppID();
	if(uid.size() == 0) return;
	
	int value = 0;
	for(auto i : uid)
	{
		value += i * i + i;
	}
	Zen::Random r;
	r.reset(value);
	std::vector<uint8_t> data;
	for(int i = 0; i < 16; ++i)
	{
		data.push_back(r.next(256));
	}
	Zen::Utils::Get()->saveDocument("pro", data.data(), data.size());
}
void Res::LoadConfig()
{
	sTuneConfig.keyPads[0] = {
		0, 1, 4, 7, 10, 8, 5, 3, 11
	};
	sTuneConfig.keyPads[1] = {
		0, 1, 3, 5, 7, 9, 11, 10, 8, 6, 4, 2, 12
	};
	
	LoadCustomKeys();
	
	_LoadPro();
	
	auto data = Zen::Utils::Get()->loadDocument("config");
	if(data.size() == sizeof(sDefaultConfig))
	{
		::memcpy(&sDefaultConfig, data.data(), data.size());
		_FixDefaultConfig();
	}
}

void Res::SaveConfig()
{
	Zen::Utils::Get()->saveDocument("config", &sDefaultConfig, sizeof(sDefaultConfig));
}

void Res::SaveCustomKeys()
{
	if(sDefaultConfig.padStyle == 2 || sDefaultConfig.padStyle == 3)
	{
		auto & v = sTuneConfig.keyPads[sDefaultConfig.padStyle];
		char name[] = "pad?";
		name[3] = '0' + sDefaultConfig.padStyle;
		Zen::Utils::Get()->saveDocument(name, v.data(), v.size());
	}
}

void Res::SetCustomKey(int key_index, int tune_index)
{
	auto & pad = sTuneConfig.keyPads[sDefaultConfig.padStyle];
	if(tune_index >= sAudioCount || tune_index < 0) tune_index = -1;
	if(key_index < pad.size())
	{
		pad[key_index] = tune_index;
	}
}

Localization Res::local;

static void _InitLocal()
{
	auto data = Zen::Utils::Get()->loadResource("font/lan.csv");
	Zen::CSVLoader csv;
	csv.decode(Zen::ToString(data));
	Res::local.initWithCSVContent(csv.getContent());
	
	auto lan = Zen::Utils::Get()->getSystemLanguage().substr(0, 2);
	if(lan == "zh")
	{
		Res::local.setLanguageIndex(1);
	}
	else
	{
		Res::local.setLanguageIndex(0);
	}
}

std::map<std::string, std::shared_ptr<FontBrush> > s_fonts;

std::shared_ptr<FontBrush> Res::GetTuneNameFont()
{
	return s_fonts["default"];
}

std::shared_ptr<FontBrush> Res::GetTextFont()
{
	if(local.getLanguageIndex() == 0)
	{
		return s_fonts["default"];
	}
	else
	{
		return s_fonts["cn"];
	}
}

void Res::LoadResource()
{
	
	Textures::Get()->setImageDecoder("jpg", std::shared_ptr<ImageDecoder>(new ImageJPGDecoder));
	Textures::Get()->setImageDecoder("png", std::shared_ptr<ImageDecoder>(new ImagePNGDecoder));
	{
		auto font = FontLibrary::Get()->createFont( Zen::Utils::Get()->loadResource("font/default.ttf"));
		s_fonts["default"] = FontBrush::Create(font, {(int)32, (int)32, 0.f, 0.f, 0.f});
	}
	{
		
		auto font = FontLibrary::Get()->createFont( Zen::Utils::Get()->loadResource("font/cn.ttf"));
		s_fonts["cn"] = FontBrush::Create(font, {32, 32});
		
	}
	
	AudioPlayer::Get()->setAudioDecoder("wav", std::shared_ptr<AudioDecoder>(new AudioWavDecoder));
	
	_InitLocal();
}

std::shared_ptr<Texture> Res::GetMainBG(int index)
{
	if(index >= sThemeStyleCount) index = 0;
	char buf[32];
	sprintf(buf, "img/bg_%d.jpg", index);
	return Textures::Get()->getTexture(buf);
}
std::shared_ptr<Texture> Res::GetDrumBG(int index)
{
	if(index >= sDrumStyleCount) index = 0;
	char buf[32];
	sprintf(buf, "img/drum_%d.png", index+1);
	return Textures::Get()->getTexture(buf);
}

std::shared_ptr<Texture> Res::GetTongueImage(int index)
{
	if(index >= sTongueStyleCount) index = 0;
	char buf[32];
	sprintf(buf, "img/tongue_%d.png", index+1);
	return Textures::Get()->getTexture(buf);
}
std::shared_ptr<Texture> Res::GetButton(std::string const & name)
{
	char buf[64];
	sprintf(buf, "img/b_%s.png", name.data());
	return Textures::Get()->getTexture(buf);
}

int Res::GetTuneIndex(int index, int style)
{
	auto & keypad = sTuneConfig.keyPads[style];
	if(keypad.size() > index) return keypad[index];
	return -1;
}

std::string Res::GetTuneName(int tune_index)
{
	if(tune_index >= sAudioCount || tune_index < 0)
	{
		return "";
	}
	auto & info = Res::sAudios[tune_index];
	char name[8];
	if(1)
	{
		if(info.high == 3)
		{
			sprintf(name, "%d\n^", info.name_no);
		}
		else if(info.high == 4)
		{
			sprintf(name, "%d", info.name_no);
		}
		else //if(info.high == 5)
		{
			sprintf(name, "-\n%d", info.name_no);
		}
		
	}
	return name;
}
void Res::Play(int key_index)
{
	auto tune = GetTuneIndex(key_index, sDefaultConfig.padStyle);
	if(tune < 0) return;
	PlayTune(tune, sDefaultConfig.voiceStyle);
}

void Res::PlayTune(int tune_index, int voice)
{
	auto & src = sAudios[tune_index];
	char buf[32];
	sprintf(buf, "snd/s_%d.wav", voice);
	//	AudioPlayer::Get()->play(buf, false);
	AudioPlayer::Get()->play(buf, false, 0.5, src.pitch *src.base);
	
}
int Res::GetKeyCount(int padStyle)
{
	if(padStyle >= sPadStyleCount) return 0;
	return (int)sTuneConfig.keyPads[padStyle].size();
}
bool Res::IsPro()
{
	return sIsPro;
}

void Res::SetPro()
{
	_SavePro();
	sIsPro = true;
}

//bool Res::IsPointIn(Pt2 p, View2d * v)
//{
//	auto size = v->getViewSize();
//	auto pos = v->getPosition();
//	auto a = figure->getAnchor();
//	pos.x -= size.w * a.x;
//	pos.y -= size.h * a.y;
//	return (p.x > pos.x && p.x < pos.x + size.w) && (p.y > pos.y && p.y < pos.y + size.h);
//}

Res::SettingRes Res::sSettings[5] = {
	{ 0, Res::sPadStyleCount, "pad", "img/setting_pad.png", },
	{ 1, Res::sVoiceStyleCount, "voice", "img/setting_voice.png", },
	{ 2, Res::sTongueStyleCount, "tongue", "img/setting_tongue.png", },
	{ 3, Res::sPadStyleCount, "drum", "img/setting_drum.png", },
	{ 4, Res::sPadStyleCount, "bg", "img/setting_bg.png", },
};


