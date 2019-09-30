#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "solidGrid.hpp"
using namespace std;

int generate_graph_segment(int l, Graph *g,int v_created);

pair<Graph*,int> generate_random_solidGrid(int n);

#endif