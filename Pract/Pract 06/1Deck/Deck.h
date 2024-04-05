class Deck {
private:
    MonsterCard monsterCards[20];
    MagicCard magicCards[20];
    int monsterCount = 0;
    int magicCount = 0;

public:
    int getMonsterCardCount() const { return monsterCount; }

    int getMagicCardCount() const { return magicCount; }

    MonsterCard getMonsterCard(int index) const {
        if (index >= 0 && index < monsterCount) {
            return monsterCards[index];
        }
    }
    MagicCard getMagicCard(int index) const {
        if (index >= 0 && index < magicCount) {
            return magicCards[index];
        }
    }

    int getMagicCardCount() const {
        return magicCount;
    }

    int getMonsterCardCount() const {
        return monsterCount;
    }

    void addMagicCard(const MagicCard& card) {
        if (magicCount < 20) {
            magicCards[magicCount++] = card;
        }
    }

    void addMonsterCard(const MonsterCard& card) {
        if (monsterCount < 20) {
            monsterCards[monsterCount++] = card;
        }
    }

    void changeMagicCard(int index, const MagicCard& newCard) {
        if (index >= 0 && index < magicCount) {
            magicCards[index] = newCard;
        }
    }

    void changeMonsterCard(int index, const MonsterCard& newCard) {
        if (index >= 0 && index < monsterCount) {
            monsterCards[index] = newCard;
        }
    }

    void removeMagicCard(int index) {
        if (index >= 0 && index < magicCount) {
            for (int i = index; i < magicCount - 1; ++i) {
                magicCards[i] = magicCards[i + 1];
            }
            --magicCount;
        }
    }

    void removeMonsterCard(int index) {
        if (index >= 0 && index < monsterCount) {
            for (int i = index; i < monsterCount - 1; ++i) {
                monsterCards[i] = monsterCards[i + 1];
            }
            --monsterCount;
        }
    }

};
