#ifndef __AC_H__
#define __AC_H__

#include <ant.h>
#include <vector> // std::vector

class AC
{
    private:
        static std::vector<Ant> antList;
    public:
        static void push_ant(Ant ant);
        static void set_ant(Ant ant, int index);
        static Ant& get_ant(int index);
        static std::size_t ant_count();
        static void step(unsigned seed);
};

#endif
