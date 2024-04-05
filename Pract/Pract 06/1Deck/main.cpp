#include <iostream>
#include "CardType.h"
#include "MonsterCard.h"
#include "MagicCard.h"
#include "Deck.h"
#pragma warning(disable : 4996)

using namespace CONSTANTS;

const char* MonsterCard::getName() const
{
	return name;
}

const int MonsterCard::getAttack() const
{
	return attack;
}
const int MonsterCard::getProtect() const
{
	return protect;
}

void MonsterCard::setAttack(const int &attack)
{
	this->attack = attack;
}
void MonsterCard::setProtect(const int &protect)
{
	this->protect = protect;
}
void MonsterCard::setName(const char* name)
{
	if (!name || strlen(name) > MAX_SIZE_NAME) return;
	strcpy(this->name, name);
}

MonsterCard::MonsterCard(const char* name, const int attack, const int protect)
{
	setName(name);
	setAttack(attack);
	setProtect(protect);
}

const char* MagicCard::getName() const
{
	return name;
}
const char* MagicCard::getEffect() const
{
	return effect;
}
const CardType MagicCard::getCard() const
{
	return type;
}

void MagicCard::setName(const char* name)
{
	if (!name || strlen(name) > MAX_SIZE_NAME) return;

	delete[] name;
	strcpy(this->name, name);	
}
void MagicCard::setEffect(const char* effect)
{
	if (!effect || strlen(name) > MAX_SIZE_EFFECT) return;
	
	delete[] effect;
	strcpy(this->effect, effect);
}
void MagicCard::setType(const CardType &type)
{
	this->type = type;
}

MagicCard::MagicCard(const char* name, const char* effect, const CardType &type)
{
	setName(name);
	setEffect(effect);
	setType(type);
}

void MonsterCard::copyName(const char* newName)
{
	name = new char[strlen(newName) + 1];

	strcpy(name, newName);
}

void MonsterCard::copyFrom(const MonsterCard& other)
{
	copyName(other.name);
	this->attack = other.attack;
	this->protect = other.protect;
}

void MonsterCard::free()
{
	delete[] name;
	attack = 0;
	protect = 0;
}

MonsterCard::MonsterCard(const MonsterCard& other)
{
	copyFrom(other);
}

MonsterCard::~MonsterCard()
{
	free();
}

MonsterCard& MonsterCard::operator=(const MonsterCard& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}


Deck::Deck(const MonsterCard* monstCs, const MagicCard* magCs) 
{
	setMonstCs(monstCs);
	setMagCs(magCs);
}

const Deck::MonsterCard getMonstCs(const Deck& other) const
{

}
const Deck::MagicCard getMagCs(const Deck& other) const
{

}

void Deck::setMonstCs(const MonsterCard* monstCs)
{

}
void Deck::setMagCs(const MagicCard* magCs)
{

}

int main()
{

}
