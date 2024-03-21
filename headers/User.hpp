#ifndef USER_HPP
#define USER_HPP
#include <iostream>
#include <sstream>
#include <string>

class User
{
private:
    int score;
    int level;
    int scoreTemp;
public:
    User() : score(0), level(1), scoreTemp(0) {}

    int getScore() {
        return score;
    }
    void reset() {
        score=0;
        level=1;
        scoreTemp=0;
    }
    int getScoreTemp() {
        return scoreTemp;
    }
    int getLevel() {
        return level;
    }
    void increasePoints(int numberOfLines) {
        score+=numberOfLines*level*numberOfLines*100;
        scoreTemp+=numberOfLines*level*numberOfLines*100;
    }
    void increaseLevel() {
        if(scoreTemp>=level*1000) {
            scoreTemp=scoreTemp%(level*1000);
            level++;
        }
        
    }

    std::string Serialize() const {
        std::ostringstream oss;
        oss << score << " " << level << " " << scoreTemp << " ,";
        return oss.str();
    }

    // Deserialization of the Grid object
    void Deserialize(const std::string& serializedData) {
        std::istringstream iss(serializedData);
        iss >> score;
        iss >> level;
        iss >> scoreTemp;
    }


    ~User() {}
};




#endif