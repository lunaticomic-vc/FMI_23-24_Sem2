#pragma once
#include "CardType.h"

using namespace CONSTANTS;

class MagicCard 
{
	char name[MAX_SIZE_NAME + 1];
	char effect[MAX_SIZE_EFFECT + 1];
	CardType type;

public:

	const char* getName() const;
	const char* getEffect() const;
	const CardType getType() const;

	void setName(const char* name);
	void setEffect(const char* effect);
	void setType(const CardType& type);

};
