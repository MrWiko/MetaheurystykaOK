#pragma once
#include "graph.h"
#include "represenation-struct.h"

namespace GraphAlgos {
    /*
    type method_name(const Graph& graph, ...)
    */

    bool ifGraphHasEulerCycle(Graph& graphHandle);

    bool ifGraphHasHamiltonCycle(Graph& graphHandle);

};