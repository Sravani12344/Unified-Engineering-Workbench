#include "workbench.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>

static void usage() {
 std::cout << "Unified Engineering Workbench (C++17)\n"
           << "Commands:\n  workbench thermal [elements] [output.csv]\n"
           << "  workbench benchmark [cases] [elements] [repetitions]\n"
           << "  workbench neural [steps]\n"
           << "  workbench inspect-stl <file.stl>\n"
           << "  workbench inspect-csv <file.csv>\n";
}
int main(int argc,char** argv) {
 try {
  if(argc<2){usage();return 0;}
  std::string cmd=argv[1];
  if(cmd=="thermal") {
   wb::ThermalConfig c; if(argc>2)c.elements=std::atoi(argv[2]);
   auto r=wb::solve_thermal(c);
   std::cout<<"elements="<<c.elements<<" max_midpoint_error_C="<<r.max_midpoint_error<<"\n";
   for(auto n:r.nodes) std::cout<<n.x<<","<<n.temperature<<"\n";
   if(argc>3){wb::write_thermal_csv(argv[3],r);std::cout<<"Wrote "<<argv[3]<<"\n";}
  } else if(cmd=="benchmark") {
   int cases=argc>2?std::atoi(argv[2]):2000, elems=argc>3?std::atoi(argv[3]):80, reps=argc>4?std::atoi(argv[4]):5;
   std::cout<<"logical_cpus="<<std::thread::hardware_concurrency()<<" cases="<<cases<<" elements="<<elems<<" repetitions="<<reps<<"\n";
   std::cout<<"workers,median_ms,speedup,efficiency\n";
   for(auto r:wb::run_benchmark(cases,elems,reps)) std::cout<<r.workers<<","<<r.median_ms<<","<<r.speedup<<","<<r.efficiency<<"\n";
  } else if(cmd=="neural") {
   int steps=argc>2?std::atoi(argv[2]):100; auto r=wb::train_one_neuron(steps);
   std::cout<<"initial_prediction="<<r.prediction<<" initial_loss="<<r.loss<<"\n"
            <<"initial_gradients dw="<<r.dw<<" db="<<r.db<<" dv="<<r.dv<<" dc="<<r.dc<<"\n"
            <<"final_parameters w="<<r.w<<" b="<<r.b<<" v="<<r.v<<" c="<<r.c<<"\n"
            <<"finite_difference_max_error="<<r.finite_difference_max_error<<"\n";
   for(std::size_t i=0;i<r.loss_history.size();++i) std::cout<<i<<","<<r.loss_history[i]<<"\n";
  } else if(cmd=="inspect-stl" && argc>2) {
   std::size_t n;std::string e;bool ok=wb::validate_stl_ascii(argv[2],n,e);
   std::cout<<(ok?"VALID":"INVALID")<<" triangles="<<n<<" "<<e<<"\n";return ok?0:2;
  } else if(cmd=="inspect-csv" && argc>2) {
   std::size_t n;std::string e;bool ok=wb::validate_nodal_csv(argv[2],n,e);
   std::cout<<(ok?"VALID":"INVALID")<<" rows="<<n<<" "<<e<<"\n";return ok?0:2;
  } else usage();
 } catch(const std::exception& e){std::cerr<<"ERROR: "<<e.what()<<"\n";return 1;}
 return 0;
}
