#ifndef USER_HPP
#define USER_HPP

class User
{
private:
    unsigned int score;
    unsigned int level;
public:
    User() : score(0), level(1) {}

    unsigned int getScore() {
        return score;
    }
    unsigned int getLevel() {
        return level;
    }
    void increasePoints(unsigned int numberOfLines) {
        score+=numberOfLines*numberOfLines*level*100;
    }
    void increaseLevel() {
        level++;
    }

    ~User() {}
};




#endif