//
// Created by shikamaru on 2021/9/21.
//

#ifndef ABC_FOOD_H
#define ABC_FOOD_H

#include <ostream>
#include <vector>
#define GoodsNum 2000
#define FoodsNum 500

class Food {
private:
    int *sequence;
    int seqLen;
    double fitness;
    int counts;

public:


    Food();

    int *getSequenceAddress() const;

    int getSequence(int index) const;

    void setSequence(int index, int target);

    int getSeqLen() const;

    void setSeqLen(int seqLen);

    double getFitness() const;

    void setFitness(double fitness);

    int getCounts() const;

    void setCounts(int updateCounts);

    friend std::ostream &operator<<(std::ostream &os, const Food &food);

    //user funcs
    void stirSequence();
    void calFitness();
    void updateCounts();
    void removeFromSequence(int target);
    void addIntoSequence(int target);

};


#endif //ABC_FOOD_H