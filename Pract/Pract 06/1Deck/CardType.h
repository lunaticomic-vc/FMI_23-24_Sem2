#pragma once

namespace CONSTANTS
{
	constexpr int MAX_AMOUNT_CARDS = 20;
	constexpr int MAX_SIZE_NAME = 25;
	constexpr int MAX_SIZE_EFFECT = 100;
}

enum CardType
{
	trap,
	buff,
	spell
};

