#pragma once
#include <vector>
#include <cstdint>

namespace minerva {

class DagNode {
protected:
    std::vector<DagNode*> successors;
    std::vector<DagNode*> predecessors;
};

class OpNode: public DagNode {
public:
    enum OpType {
        mult
    };
    OpType type;
    std::vector<size_t> operands;
};

class DataNode: public DagNode {
public:
    uint32_t storageIdx;
};

}

/*
 * Engine has several pools of operators, e.g. MKL, CUDA, Basic.
 * Upon traversing an operater node, the engine will look up corresponding
 * function in current pool using `OpType` of the node.
 * If lookup fails, the engine will resort to backup pools.
 * For example, if the engine visits a matrix multiplication node, and
 * if we are running CUDA mode, it will get the `OpType` of the node, which
 * is `mult` of course. Then it will find `mult` function in CUDA pool. But
 * unfortunately we are too lazy to implement a CUDA multiplication. Then
 * the engine looks it up in Basic pool, which is a handwritten version
 * of matrix multiplication. Engine calls this function, pushes arguments
 * onto stack, mark the node complete, and moves on.
 */

