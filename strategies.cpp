#include "strategies.h"

double stratA(Agent* a, Agent* b, double mem1, double mem2) { // fair angel
    double help = a->resource / dunbar;
    help = std::min(help, a->_resource / a->loss);
    help = std::min(help, 2.0);
    a->_resource -= a->loss * help;
    b->_resource += help;
    return help;
}

double stratB(Agent* a, Agent* b, double mem1, double mem2) { // eye to eye
    double help = mem2;
    help = std::min(help, a->_resource / a->loss);
    help = std::min(help, 2.0);
    a->_resource -= a->loss * help;
    b->_resource += help;
    return help;
}

double stratC(Agent* a, Agent* b, double mem1, double mem2) { // eye to eye, but to my limit
    double help = mem2 * a->resource / dunbar;
    help = std::min(help, a->_resource / a->loss);
    help = std::min(help, 2.0);
    a->_resource -= a->loss * help;
    b->_resource += help;
    return help;
}

double stratD(Agent* a, Agent* b, double mem1, double mem2) { // for the weak
    //double help = a->resource > b->resource ? a->resource / dunbar : 0;
    double help = a->loss < 1 ? mem2 * a->resource / dunbar : 0;
    help = std::min(help, a->_resource / a->loss);
    help = std::min(help, 2.0);
    a->_resource -= a->loss * help;
    b->_resource += help;
    return help;
}

double stratE(Agent* a, Agent* b, double mem1, double mem2) { // for the rich
    double help = a->resource < b->resource ? a->resource / dunbar : 0;
    help = std::min(help, a->_resource / a->loss);
    help = std::min(help, 2.0);
    a->_resource -= a->loss * help;
    b->_resource += help;
    return help;
}

double stratF(Agent* a, Agent* b, double mem1, double mem2) { // save half for myself
    double help = mem2 * a->resource / 300;
    help = std::min(help, a->_resource / a->loss);
    help = std::min(help, 2.0);
    a->_resource -= a->loss * help;
    b->_resource += help;
    return help;
}

double stratG(Agent* a, Agent* b, double mem1, double mem2) { // random
    double help = 0;
    help = std::min(help, a->_resource / a->loss);
    help = std::min(help, 2.0);
    a->_resource -= a->loss * help;
    b->_resource += help;
    return help;
}

double (*strategies[])(Agent*, Agent*, double, double) = {stratA, stratB, stratC, stratD, stratE, stratF, stratG};