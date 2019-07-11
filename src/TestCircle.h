#pragma once
#include <Siv3D.hpp>

class TestCircle 
{
public:
	enum class HolePos
	{
		LEFT,
		RIGHT,
		TOP,
		BOTTOM
	};

	enum class Size
	{
		XXXS = 2,
		XXS = 5,
		XS = 10,
		S = 20,
		M = 40,
		L = 80,
		XL = 160,
		XXL = 320,
		XXXL = 480,
	};

	TestCircle() {};

	TestCircle(int x, int y, HolePos pos, Size size) :
		holePos(pos),
		size(size),
		circle(x, y, static_cast<int>(size))
	{
		double hole_size = circle.r;
		switch (pos) {
		case HolePos::LEFT:
			rect = Rect(circle.x - circle.r * 1.2, circle.y - hole_size / 2, circle.r * 1.2, hole_size);
			break;
		case HolePos::RIGHT:
			rect = Rect(circle.x, circle.y - hole_size / 2, circle.r * 1.2, hole_size);
			break;
		case HolePos::TOP:
			rect = Rect(circle.x - hole_size / 2, circle.y - circle.r * 1.2, hole_size, circle.r * 1.2);
			break;
		case HolePos::BOTTOM:
			rect = Rect(circle.x - hole_size / 2, circle.y, hole_size, circle.r * 1.2);
			break;
		}
	}

	void draw() const
	{
		double circle_thick = circle.r * 5 / 14;

		circle.drawFrame(circle_thick, ColorF(0.0, 0.0, 0.0, 1.0));
		rect.draw(ColorF(1.0, 1.0, 1.0, 1.0));
	}

	HolePos getHolePos()
	{
		return holePos;
	}

	Size getSize()
	{
		return size;
	}

	static TestCircle getRandomTestCircle(int x, int y)
	{
		std::random_device rnd;
		HolePos holePos = indexToHolePos(rnd() % 4);
		Size size = indexToSize(rnd() % 9);

		return TestCircle(x, y, holePos, size);
	}

	static HolePos indexToHolePos(int index)
	{
		switch (index) {
		case 0:
			return HolePos::LEFT;
		case 1:
			return HolePos::RIGHT;
		case 2:
			return HolePos::TOP;
		case 3:
			return HolePos::BOTTOM;
		default:
			return HolePos::LEFT;
		}
	}

	static int holePosToIndex(HolePos holePos)
	{
		switch (holePos) {
		case HolePos::LEFT:
			return 0;
		case HolePos::RIGHT:
			return 1;
		case HolePos::TOP:
			return 2;
		case HolePos::BOTTOM:
			return 3;
		}
	}

	static Size indexToSize(int index)
	{
		switch (index) {
		case 0:
			return Size::XXXS;
		case 1:
			return Size::XXS;
		case 2:
			return Size::XS;
		case 3:
			return Size::S;
		case 4:
			return Size::M;
		case 5:
			return Size::L;
		case 6:
			return Size::XL;
		case 7:
			return Size::XXL;
		case 8:
			return Size::XXXL;
		default:
			return Size::M;
		}
	}

	static int sizeToIndex(Size size)
	{
		switch (size) {
		case Size::XXXS:
			return 0;
		case Size::XXS:
			return 1;
		case Size::XS:
			return 2;
		case Size::S:
			return 3;
		case Size::M:
			return 4;
		case Size::L:
			return 5;
		case Size::XL:
			return 6;
		case Size::XXL:
			return 7;
		case Size::XXXL:
			return 8;
		}
	}
private:
	HolePos holePos;
	Size size;
	Circle circle;
	Rect rect;
};