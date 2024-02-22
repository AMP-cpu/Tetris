#ifndef USER_HPP
#define USER_HPP

class User
{
private:
    unsigned int pontuation;
    unsigned int level;
public:
    User() : pontuation(0), level(1) {}

    unsigned int getPontuation() {
        return pontuation;
    }
    unsigned int getLevel() {
        return level;
    }
    void increasePoints(unsigned int numberOfLines) {
        pontuation+=numberOfLines*numberOfLines*level*100;
    }
    void increaseLevel() {
        level++;
    }

    ~User() {}
};




#endif