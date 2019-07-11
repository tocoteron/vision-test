#pragma once
#include "App.h"
#include "Score.h"

static const std::array<Score, GameInfo::MAX_SAVE_RANKING_SCORE> defaultHighScores
{
	Score(Date(2018, 11, 10), U"ゲスト", 0),
	Score(Date(2018, 11, 10), U"ゲスト", 0),
	Score(Date(2018, 11, 10), U"ゲスト", 0),
	Score(Date(2018, 11, 10), U"ゲスト", 0),
	Score(Date(2018, 11, 10), U"ゲスト", 0),
	Score(Date(2018, 11, 10), U"ゲスト", 0),
	Score(Date(2018, 11, 10), U"ゲスト", 0),
	Score(Date(2018, 11, 10), U"ゲスト", 0),
	Score(Date(2018, 11, 10), U"ゲスト", 0)
};

class ScoreManager
{
public:
	static void save(int32 score, String name = U"ゲスト")
	{
		if (FileSystem::Exists(GameInfo::SAVE_FILE_PATH)) {
			Deserializer<BinaryReader>{GameInfo::SAVE_FILE_PATH}(highScores);
		}
		else {
			Serializer<BinaryWriter>{GameInfo::SAVE_FILE_PATH}(highScores);
		}

		if (highScores.back().score <= score) {
			highScores.back() = Score(Date::Today(), name, score);

			std::sort(highScores.begin(), highScores.end(), [](const Score& l, const Score& r)
			{
				return l.score > r.score ? true : l.score == r.score ? l.date > r.date : false;
			});

			Serializer<BinaryWriter>{GameInfo::SAVE_FILE_PATH}(highScores);
		}
	}

	static std::array<Score, GameInfo::MAX_SAVE_RANKING_SCORE> load()
	{
		if (FileSystem::Exists(GameInfo::SAVE_FILE_PATH)) {
			Deserializer<BinaryReader>{GameInfo::SAVE_FILE_PATH}(highScores);
		}
		else {
			Serializer<BinaryWriter>{GameInfo::SAVE_FILE_PATH}(highScores);
		}

		return highScores;
	}
private:
	static std::array<Score, GameInfo::MAX_SAVE_RANKING_SCORE> highScores;
};

std::array<Score, GameInfo::MAX_SAVE_RANKING_SCORE> ScoreManager::highScores = defaultHighScores;
