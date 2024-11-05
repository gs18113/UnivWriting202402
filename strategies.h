#include<bits/stdc++.h>

struct Agent;

double stratA(Agent* a, Agent* b, double, double);

double stratB(Agent* a, Agent* b, double, double);

double stratC(Agent* a, Agent* b, double, double);

double stratD(Agent* a, Agent* b, double, double);

double stratE(Agent* a, Agent* b, double, double);

double stratF(Agent* a, Agent* b, double, double);

double stratG(Agent* a, Agent* b, double, double);

extern double (*strategies[])(Agent*, Agent*, double, double);


class RandomGenerator {
private:
    std::default_random_engine generator;
    std::normal_distribution<double> distribution;
    std::uniform_real_distribution<double> uni;

public:
    RandomGenerator(double mean = 0.0, double stddev = 1.0) 
        : generator(std::chrono::system_clock::now().time_since_epoch().count()),
          distribution(mean, stddev),
          uni(0.0, 1.0) {}
    
    double getGaussianNumber() {
        return distribution(generator);
    }

    double getUni(){
        return uni(generator);
    }

    int getInt(int min, int max) {
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(generator);
    }
};

struct Agent {
    double resource;
    double _resource = 0;
    double loss;
    int strategy_type;
    double (*strategy)(Agent*, Agent*, double, double);
    std::vector<int> neighbors; // size ~ 150

    Agent(RandomGenerator* gen) {
        resource = _resource = 150;
        loss = 1 + gen->getGaussianNumber() / 10;
        if(loss < 0) loss = 0;
        strategy = strategies[strategy_type = rand()%7];
    }
    Agent(RandomGenerator* gen, int strat){
        resource = _resource = 150;
        loss = 1 + gen->getGaussianNumber() / 10;
        if(loss < 0) loss = 0;
        strategy = strategies[strategy_type = strat];
    }
};

extern int dunbar;
extern RandomGenerator gen;
