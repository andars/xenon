#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <random>

struct context {
    std::default_random_engine& gen;
    std::uniform_real_distribution<float>& rand_real;
};

#endif
