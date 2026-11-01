#include "workbench.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

namespace wb {
bool validate_stl_ascii(const std::string& path,std::size_t& count,std::string& error) {
    std::ifstream f(path); count=0;
    if(!f){error="File could not be opened.";return false;}
    std::string line; bool solid=false;
    while(std::getline(f,line)) {
        std::istringstream ss(line); std::string a,b; ss>>a>>b;
        if(a=="solid") solid=true;
        if(a=="facet" && b=="normal") ++count;
        if(line.size()>1000000){error="Line exceeds safe 1 MB limit.";return false;}
    }
    if(!solid || count==0){error="Expected non-empty ASCII STL with 'solid' and facet normal records.";return false;}
    error.clear(); return true;
}
bool validate_nodal_csv(const std::string& path,std::size_t& rows,std::string& error) {
    std::ifstream f(path); rows=0;
    if(!f){error="File could not be opened.";return false;}
    std::string line;
    if(!std::getline(f,line) || line!="node_id,x_m,y_m,z_m,temperature_C"){
        error="CSV header must be node_id,x_m,y_m,z_m,temperature_C";return false;
    }
    while(std::getline(f,line)) {
        if(line.empty()) continue;
        std::istringstream ss(line); std::string cell; int columns=0;
        while(std::getline(ss,cell,',')) ++columns;
        if(columns!=5){error="Each nodal row must contain exactly five comma-separated fields.";return false;}
        ++rows;
        if(rows>1000000){error="CSV exceeds tested safety limit of 1,000,000 rows.";return false;}
    }
    if(rows==0){error="CSV contains no data rows.";return false;}
    error.clear(); return true;
}
}
