#ifndef __AM_H__
#define __AM_H__

#include <string> // std::string

class AdjMatrix
{
    private:
        int nodeCount;
        float **adj;
    public:
        AdjMatrix();
        AdjMatrix(int nodeCount);
        AdjMatrix(int nodeCount, float initValue);
        void set_edge(int start, int end, float value);
        void update_trail();
        float get_edge(int start, int end) const;
        std::string str() const;
};

#endif
