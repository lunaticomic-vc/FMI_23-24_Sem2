#pragma once
#include "CardType.h"

using namespace CONSTANTS;

class MonsterCard 
{
	char* name = nullptr;
	unsigned int attack = 0;
	unsigned int protect = 0;

	void copyName(const char* name);

	void free();
	void copyFrom(const MonsterCard& other);

public:
	MonsterCard() = default;
	MonsterCard(const MonsterCard& other): name(other.name), attack(other.attack), protect(other.protect) {}
	MonsterCard& operator=(const MonsterCard& other) {}
	~MonsterCard() {}

	const char* getName() const;
	const int getAttack() const;
	const int getProtect() const;

	void setAttack(const int &attack);
	void setProtect(const int& protect);
	void setName(const char* name);
};
