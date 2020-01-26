#pragma once
#include "App.h"
#include "ScoreManager.h"

class Ranking : public App::Scene
{
public:
	Ranking(const InitData& initData) :
		IScene(initData),
		cursor(0),
		crownTexture(U"./assets/crown-mini.png"),
		scoreFont(SCORE_FONT_SIZE)
	{}

	void update() override
	{
		if ((MouseL | KeyEnter | KeyEscape).down()) {
			changeScene(U"Title");
		}

		if (KeyDown.down()) {
			cursor = (cursor + 1) % highScores.size();
		}
		else if (KeyUp.down()) {
			cursor = (cursor - 1 + highScores.size()) % highScores.size();
		}
	}

	void draw() const override
	{
		int32 scoreFontMaxWidth = 0;
		int32 maxScoreWidth = 0;
		int32 topScoreY = (Window::ClientHeight() - GameInfo::BOTTOM_LABEL_HEIGHT - SCORE_FONT_SIZE * highScores.size()) / 2;

		// Cursor Label
		Rect(
			0,
			topScoreY + cursor * SCORE_FONT_SIZE + 10,
			Window::ClientWidth(),
			SCORE_FONT_SIZE
		).draw(Color(128, 191, 63));

		for (int i = 0; i < highScores.size(); ++i) {
			maxScoreWidth = std::max(
				maxScoreWidth,
				scoreFont(U"{}位  {:0>6}  {}"_fmt(
					i + 1,
					//highScores[i].name,
					highScores[i].score,
					highScores[i].date
				)).region().w
			);
		}

		for (int i = 0; i < highScores.size(); ++i) {
			scoreFont(U"{}位  {:0>6}  {}"_fmt(
				i + 1,
				//highScores[i].name,
				highScores[i].score,
				highScores[i].date
			)).draw(
				(Window::ClientWidth() - maxScoreWidth) / 2,
				topScoreY + i * SCORE_FONT_SIZE,
				Color(40)
			);
		}

		crownTexture.draw(
			(Window::ClientWidth() - maxScoreWidth) / 2 - crownTexture.width() - 10,
			topScoreY
		);

		// Under Label
		Rect(
			0,
			Window::ClientHeight() - GameInfo::BOTTOM_LABEL_HEIGHT,
			Window::ClientWidth(),
			GameInfo::BOTTOM_LABEL_HEIGHT
		).draw(Color(84, 103, 122));
	}
private:
	int32 cursor;
	std::array<Score, GameInfo::MAX_SAVE_RANKING_SCORE> highScores = ScoreManager::load();
	Texture crownTexture;
	Font scoreFont;
	static const int SCORE_FONT_SIZE = 60;
};
