#include "App.h"
#include "Title.h"
#include "Game.h"
#include "Result.h"
#include "Ranking.h"

void setupFullScreen(const int32 width, const int32 height)
{
	const Size BaseSize(width, height);

	Window::SetBaseSize(BaseSize);

	const auto[displayIndex, displayMode]
		= OptimalScreen::Get(OptimalScreen::Preference::AspectMin, BaseSize);

	Graphics::SetFullScreen(true, displayMode.size, displayIndex, displayMode.refreshRateHz);

	//Print << U"Display {} | size {} @ {} Hz"_fmt(displayIndex, displayMode.size, displayMode.refreshRateHz);
}

int init()
{
	Graphics::SetTargetFrameRateHz(GameInfo::FPS);

	setupFullScreen(GameInfo::WINDOW_WIDTH, GameInfo::WINDOW_HEIGHT);
	//Window::Resize(1920, 1080);

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

    System::SetExitEvent(WindowEvent::CloseButton);

	while (System::Update())
	{
		if (!manager.update()) {
			break;
		}
	}
}