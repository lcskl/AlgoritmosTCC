#ifndef BRUTEFORCEVALIDATOR_HPP
#define BRUTEFORCEVALIDATOR_HPP

#include <vector>
#include "bipartiteK3.hpp"

void cleanInfectedArray(int *infected,int n,std::vector<int> infected_at_0);

int simulate(Graph g, int* infected,int k);

int testIfSetSizeKPercolates(Graph g,int k);

#endif