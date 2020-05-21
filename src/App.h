#pragma once
#include <Siv3D.hpp>
#include <HamFramework.hpp>

namespace GameInfo
{
	enum class GameMode {
		Time,
		OneShot,
		ManyShot,
	};

	const int32 FPS = 30;

    const bool isFullScreen = true;

	const int32 WINDOW_WIDTH = isFullScreen ? 1920 : 1680;
	const int32 WINDOW_HEIGHT = isFullScreen ? 1080 : 980;

	const String TITLE = U"Visicn Test";
	const String VERSION = U"Version 0.1";
	const String TWEET_HEAD = U"Vision Test をプレイしたよ！私の視力は ";
	const String TWEET_TAIL = U" VP #VisionTest";
	const String SAVE_FILE_PATH = U"saves/score.dat";

	const int32 MAX_SAVE_RANKING_SCORE = 9;

	const int32 TITLE_FONT_SIZE = 80;
	const int32 MENU_FONT_SIZE = 30;

	/*
	const String MENU_SINGLE_PLAY = U"シングルプレイ";
	const String MENU_MULTI_PLAY = U"マルチプレイ";
	const String MENU_SCORE = U"スコア";
	*/
	const String MENU_TIME = U"時間制(30秒)";
	const String MENU_MANY_SHOT = U"回数制(30回)";
	const String MENU_ONE_SHOT = U"一発勝負";
	const String MENU_RANKING = U"ランキング";
	const String MENU_EXIT = U"終了";

	const int BOTTOM_LABEL_HEIGHT = 140;
}

struct GameData
{
	GameInfo::GameMode mode;
	int32 lastScore;
};

using App = SceneManager<String, GameData>;
