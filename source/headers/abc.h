//
// Created by shikamaru on 2021/9/21.
//

#ifndef ABC_ABC_H
#define ABC_ABC_H

Food currentBestFood;

//void findMinMax(Food *pFood, double &min, double &max);
void fdcpy(Food &sFood, Food &tFood);
double* calAccessProb(Food _foods[FoodsNum]);
void findMinMax(Food *foods, double &min, double &max);
void hybrid(Food *foods, int j);
void roulette(double *P, Food _foods[FoodsNum]);
void normalization(double *P, Food _foods[FoodsNum]);

/*!
 * 复制 Food
 * @param sFood source food
 * @param tFood target food
 */
void fdcpy(Food &sFood, Food &tFood) {
    for (int i = 0; i < GoodsNum; ++i) {
        // 将 sFood 序列的每一个值依次赋值给 tFood
        // 这样做的目的是防止该属性的指针直接赋值，否则对复制 Food 修改时，源 Food 也会改变
        tFood.setSequence(i, sFood.getSequence(i));
    }
    // 其他属性的复制
    tFood.setFitness(sFood.getFitness());
    tFood.setSeqLen(sFood.getSeqLen());
    tFood.setCounts(0);
}

/*!
 * 计算第一次交叉之后的每一个食物源访问的概率
 * @param _foods 所有的已经交叉之后的食物源
 * @return 每一个食物源访问概率的数组
 */
double* calAccessProb(Food _foods[FoodsNum]) {
    static double P[FoodsNum] = {0};
//    normalization(P, _foods); // 使用归一化计算概率集
    roulette(P, _foods); // 使用轮盘赌计算概率集
    /**TEST*/
//    for (int i = 0; i < FoodsNum; ++i) {
//        std::cout << P[i] << " ";
//    }

    return P;
}

/*!
 * 找到所有 fitness 中的最大值与最小值
 * @param foods  所有输入的食物源
 * @param min  最小 fitness
 * @param max  最大 fitness
 */
void findMinMax(Food *foods, double &min, double &max) {
    int begin = 0;
    if (FoodsNum % 2 == 1) {
        min = max = foods[0].getFitness();
        begin = 1;
    } else {
        if (foods[0].getFitness() < foods[1].getFitness()) {
            min = foods[0].getFitness();
            max = foods[1].getFitness();
        }
        else {
            min = foods[1].getFitness();
            max = foods[0].getFitness();
        }
        begin = 2;
    }

    for (int i = begin; i < FoodsNum-1; i = i+2) {
        double preFitness = foods[i].getFitness();
        double nextFitness = foods[i+1].getFitness();
        if (preFitness < nextFitness) {
            if (preFitness < min)
                min = preFitness;
            if (nextFitness > max)
                max = nextFitness;
        } else {
            if (nextFitness < min)
                min = nextFitness;
            if (preFitness > max)
                max = preFitness;
        }
    }

}

/*!
 * 交叉操作：
 * 对于当前的食物源 f1，随机选取另外一个食物源 f2，从 f2 中选取其序列 s2 的三分之一 g2，
 * 再从 f1 的序列 s1 中剔除掉与 g2 相同的序列，最后将 g2 连接到 s1 的相应位置
 * @param foods 所有食物源
 * @param j 当前食物源的index
 */
void hybrid(Food *foods, int j) {// 两个时间序列进行交叉，遗传下一代，交叉的个体数量为总数量的三分之一（取整）
    // copy food[j] to tempFood and avoid using the same address of the time sequence
    Food tempFood;
    fdcpy(foods[j], tempFood);

    int r = rand()%( (GoodsNum - GoodsNum / 20) - 0 + 1) + 0; // 随机选取交叉序列的起始位置[0, (GoodsNum - GoodsNum / 3)]
    int rdFdIndex = rand()%( (FoodsNum - 1) - 0 + 1) + 0; // [0, FoodsNum-1]
    Food randomFood = currentBestFood; // 选取目前最好的食物源杂交
//    Food randomFood = foods[rdFdIndex]; // 随机选取一个食物源交叉

    for (int iter = r; iter < r + (GoodsNum/20); ++iter) { // 取出从随机位置开始，向后至“总数的三分之一”个元素
        /**
         *  全部迭代完后的效果就是
         *  从 food2 中选取一段序列
         *  从 food1 中删除掉这些序列中的值
         *  再将这些值拼接到 food1 的末尾
         * */
        int currentElement = randomFood.getSequence(iter);
        tempFood.removeFromSequence(currentElement); // (CODE_LENTH^2) 从自身的序列中删除交叉对象的该元素
//        tempFood.addToEndOfSequence(currentElement); // 再将其置于序列的末尾
        tempFood.addIntoSequence(iter, currentElement); // 再将其置于序列的末尾
    }
//    tempFood.calFitness(); // 交叉完后重新计算适应度值
    enSimpleCode(tempFood);
    if (tempFood.getFitness() < foods[j].getFitness()) { // 比较前后的适应度值，并选择是否更新
        foods[j] = tempFood;
//        foods[j].calFitness();
//        enSimpleCode(foods[j]);
        foods[j].setCounts(0);

        if (foods[j].getFitness() < currentBestFood.getFitness()) {
            // 每次交叉之后如果有更新，则与当前 Best 比较是否更新 Best
            fdcpy(foods[j], currentBestFood);
        }
    } else {
        foods[j].updateCounts();
    }

    // todo 杂交时采用遗传算法的思想


}

/*!
 * 将适应度值归一化
 * @param P 用于存储计算后的概率值
 * @param _foods 所有食物源的地址
 */
void normalization(double *P, Food _foods[FoodsNum]) {
    double min = 0; // 存储当前食物源中的最小 fitness
    double max = 0; // 存储当前食物源中的最大 fitness
    findMinMax(_foods, min, max); // 确定最小值与最大值
    for (int i = 0; i < FoodsNum; ++i) {
        // 对所有的适应度值进行归一化，均缩小为 [0, 1] 之间的数
        P[i] = (_foods[i].getFitness() - min) / (max - min);
    }
}

/*!
 * 通过轮盘赌计算每一个食物源的概率
 * @param P 用于存储计算后的概率值
 * @param _foods 所有食物源的地址
 */
void roulette(double *P, Food _foods[FoodsNum]) {
    int totalFitness = 0;
    double probs = 0.0;
    for (int i = 0; i < FoodsNum; ++i) {
        totalFitness += _foods[i].getFitness();
    }
    for (int j = 0; j < FoodsNum; ++j) {
        probs += _foods[j].getFitness() / (totalFitness * 1.0);
        P[j] = probs;
    }
}

/*!
 * ABC算法主体
 */
void abc() {

//    getParameters();

    int empBeeNum = FoodsNum; // 引领蜂
    int onLookBeeNum = FoodsNum; // 跟随蜂

    // 初始化阶段
    CS_swap();//随机货位
    Food foods[FoodsNum]; // 生成新的食物源种群
//    Food *foods = new Food[FoodsNum]; // 生成新的食物源种群
    enCode(foods); // 计算种群中个体的适应度值
    fdcpy(foods[0], currentBestFood); // 将第一个食物源设置为 Best，便于每一轮比较
    for (int i = 0; i < FoodsNum; ++i) {
//        std::cout << foods[i] << std::endl; //输出初始种群
        if (foods[i].getFitness() < currentBestFood.getFitness()) { // 第一轮迭代，找到当前 Best
            fdcpy(foods[i], currentBestFood);
        }
    }
    std::cout << "The best ever: " << currentBestFood << std::endl;
    // 初始化阶段

    std::cout << "*****************************" << std::endl;

    for (int i = 0; i < MAXITERTIME; ++i) {  // 总迭代次数

        /**
         * 引领蜂对于每一个食物源进行访问（采集）
         * 采集过程为：
         *  . 对于该食物源 food1 ，选择邻域内的另外一个食物源 food2 进行交叉，产生一个新的食物源 food3
         *  . 对比该食物源 food1 与新食物源 food3 的适应度值 fit1 与 fit3
         *  . food1 = fit1 < fit3 ? food1 : food3
         *  . 若 food1 的值进行了更新，则将采集次数 count 置 0，否则 count + 1
         *      （此部的目的是为了模拟食物源采集之后的消耗，若采集次数增加到一定数目 Limit，则舍弃该食物源，并生成一个新的食物源）
         * 直到所有的食物源都被采集
         * */
        for (int j = 0; j < empBeeNum; ++j) {  // 引领蜂采集阶段
            hybrid(foods, j); // 交叉
        }

        double *accessProb; // 计算决策概率集

        accessProb = calAccessProb(foods);

        /**
         * 跟随蜂阶段，蜜蜂对食物源随机进行访问
         * */
        int currentFood = 0;
        int currentBee = 0;
        while (currentBee < onLookBeeNum) { // 对于所有的跟随蜂，依次去随机访问食物源
            double randProb = (rand()%1000 + 1) / 1000.0; // 产生一个[0.001, 1]的随机概率
            if (randProb < accessProb[currentFood]) { // 如果随机产生的概率满足此条件，则对此食物源进行采集
                hybrid(foods, currentFood);
                currentBee++; // 采集之后则轮到下一个跟随蜂
            }
            currentFood++; // 更换下一个食物源
            if (currentFood >= FoodsNum) { currentFood = 0; } // 防止食物源越界
        }

//        for (int iter = 0; iter < onLookBeeNum; ++iter) {
//            double randProb = (rand()%100 + 1) / 100.0; // 产生一个[0, 1]的随机概率
//            if (currentFood >= (FoodsNum - 1)) { currentFood = 1; }
//            for (int j = currentFood; j < FoodsNum; ++j) {
//                if (randProb < accessProb[j]) { // 随机概率与该食物源的决策概率进行比较，决定是否采集
//                    hybrid(foods, j); //
//                } else {
//                    continue;
//                }
//            }
//        }


        /**
         * 侦查蜂阶段，蜜蜂抛弃不新鲜的食物源
         **/
        for (int s = 0; s < FoodsNum; ++s) {
            if (foods[s].getCounts() >= LIMIT) {
                foods[s].stirSequence();
                enSimpleCode(foods[s]);
                foods[s].setCounts(0);
            }
        }
        std::cout << "Gen " << i + 1 << ": ";
        std::cout << currentBestFood.getFitness() << std::endl;
//        for (int i = 0; i < FoodsNum; ++i) {
//            std::cout << foods[i] << std::endl;
//        }
        if (currentBestFood.getFitness() == 0) break;
    }

    std::cout << "*****************************" << std::endl;
    std::cout << "The best ever: " << currentBestFood << std::endl;

}

#endif //ABC_ABC_H
