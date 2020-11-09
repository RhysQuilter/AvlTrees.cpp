#pragma once
#include <string>
using namespace std;

class AvlBalanceFactor
{
public:
	static const int Balanced = 0;
	static const int LeftUnbalanced = 1;
	static const int RightUnbalanced = -1;

	static string ToString(const int& height)
	{
		if (height > Balanced)
			return "Left Unbalanced";
		else if (height < Balanced)
			return "Right Unbalanced";
		else //if (height == Balanced)
			return "Balanced";
	}
};