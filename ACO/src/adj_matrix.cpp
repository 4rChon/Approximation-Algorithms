#include <adj_matrix.h>
#include <string>
#include <sstream>

AdjMatrix::AdjMatrix()
{
    AdjMatrix(0);
}

AdjMatrix::AdjMatrix(int nodeCount)
{
    this->nodeCount = nodeCount;
    this->adj = new float*[this->nodeCount];
    for(int i = 0; i < this->nodeCount; i++)
    {
        this->adj[i] = new float[this->nodeCount];
        for(int j = 0; j < this->nodeCount; j++)
        {        
            this->adj[i][j] = 0;
        }
    }
}

AdjMatrix::AdjMatrix(int nodeCount, float initValue)
{
    this->nodeCount = nodeCount;
    this->adj = new float*[this->nodeCount];
    for(int i = 0; i < this->nodeCount; i++)
    {
        this->adj[i] = new float[this->nodeCount];
        for(int j = 0; j < this->nodeCount; j++)
        {
            if(j != i)
                this->adj[i][j] = initValue;
            else this->adj[i][j] = 0;
        }
    }
}

void AdjMatrix::set_edge(int start, int end, float value)
{
    this->adj[start][end] = value;    
    this->adj[end][start] = value;
}

float AdjMatrix::get_edge(int start, int end) const
{
    return this->adj[start][end];
}

std::string AdjMatrix::str() const
{
    std::ostringstream s;
    for(int i = 0; i < this->nodeCount; i++)
    {
        for(int j = 0; j < this->nodeCount; j++)
            s << this->adj[i][j] << " ";
        s << "\n";
    }
    return s.str();
}

