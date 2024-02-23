#ifndef USER_HPP
#define USER_HPP

class User
{
private:
    unsigned int score;
    unsigned int level;
    unsigned int scoreTemp;
public:
    User() : score(0), level(1), scoreTemp(0) {}

    unsigned int getScore() {
        return score;
    }
    unsigned int getScoreTemp() {
        return scoreTemp;
    }
    unsigned int getLevel() {
        return level;
    }
    void increasePoints(unsigned int numberOfLines) {
        score+=numberOfLines*level*numberOfLines*100;
        scoreTemp+=numberOfLines*level*numberOfLines*100;
    }
    void increaseLevel() {
        if(scoreTemp>=level*1000) {
            scoreTemp=scoreTemp%(level*1000);
            level++;
        }
        
    }

    ~User() {}
};




#endif