#include "App.h"
#include "Title.h"
#include "Game.h"
#include "Result.h"
#include "Ranking.h"

void setupFullScreen()
{
    const Array<Size> resolutions = Graphics::GetFullscreenResolutions();

    if (!resolutions)
    {
        throw Error(U"フルスクリーンモードを利用できません。");
    }

    // 選択肢を作成
    const Array<String> options = resolutions.map(Format);

    // 最大のフルスクリーン解像度にする
    size_t index = resolutions.size() - 1;
    if (!Window::SetFullscreen(true, resolutions[index]))
    {
        throw Error(U"フルスクリーンモードへの切り替えに失敗しました。");
    }
}

int init()
{
	Graphics::SetTargetFrameRateHz(GameInfo::FPS);

    if(GameInfo::isFullScreen)
    {
        setupFullScreen();
    }
    else
    {
        Window::Resize(Size(GameInfo::WINDOW_WIDTH, GameInfo::WINDOW_HEIGHT));
    }

	FontAsset::Register(U"Title", GameInfo::TITLE_FONT_SIZE, Typeface::Heavy);
	FontAsset::Register(U"Menu", GameInfo::MENU_FONT_SIZE, Typeface::Bold);

	return 0;
}

void Main()
{
	init();

	App manager;

	manager.add<Title>(U"Title");
	manager.add<Game>(U"Game");
	manager.add<Result>(U"Result");
	manager.add<Ranking>(U"Ranking");

	while (System::Update())
	{
		if (!manager.update()) {
			break;
		}
	}
}
