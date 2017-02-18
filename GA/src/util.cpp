#include <util.h>
#include <city.h>
#include <tour.h>
#include <tour_manager.h>
#include <cstdlib>      // atof
#include <fstream>      // ifstream
#include <iostream>     // std::cout, std::endl
#include <string>       // std::string
#include <vector>       // std::vector

int load_tsp(std::string fileName)
{
    std::string line;
    bool gettingCoords = false;
    
    std::ifstream tsp("../../res/" + fileName + ".tsp");
    if(tsp.is_open())
    {
        while(getline(tsp, line))
        {
            if(line.compare("EDGE_WEIGHT_TYPE") > 1)
                if(!line.compare("EDGE_WEIGHT_TYPE: EUC_2D") == 0 && !line.compare("EDGE_WEIGHT_TYPE : EUC_2D"))
                {
                    std::cout << "Invalid Format: " << line << "\nRequired: EDGE_WEIGHT_TYPE : EUC_2D or EDGE_WEIGHT_TYPE: EUC_2D" << std::endl;
                    break;
                }
            if(!line.compare("NODE_COORD_SECTION"))
                gettingCoords = true;
            else if(!line.compare("EOF"))
                gettingCoords = false;
            else if(gettingCoords)
            {
                City nextCity = parse_line(line);
                TM::add_city(nextCity);
            }
        }
        tsp.close();
        return 0;
    }    
    else return 1;
        
}

float subStringToFloat(std::string line, int pos, int length)
{
    char buffer[length];
    line.copy(buffer, pos, length);
    
    return atof(buffer);
}

City parse_line(std::string line)
{
    std::string str_id = "";
    std::string str_x  = "";
    std::string str_y  = "";
    bool bool_id = false;
    bool bool_x  = false;
    bool bool_y  = false;
    for(size_t i = 0; i < line.size(); i++)
    {
        if(line[i] == ' ')
        {
            if(str_id.size() > 0)
            {
                bool_x = true;
                bool_id = false;
            }
            
            if(str_x.size() > 0)
            {
                bool_y = true;
                bool_x = false;
            }
            
            if(str_y.size() > 0)
                break;
        }
        else if(line[i] != ' ')
        {
            if(!bool_id && !bool_x && !bool_y)
                bool_id = true;
            
            if(bool_id)
                str_id += line[i];
            else if(bool_x)
                str_x += line[i];
            else if(bool_y)
                str_y += line[i];
        }
    }
    return City(subStringToFloat(str_x, str_x.size(), 0),
                subStringToFloat(str_y, str_y.size(), 0));
}
