#include "workbench.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <thread>
#include <vector>
#include <numeric>
#include <stdexcept>

namespace wb {
static double one_case(int seed, int elements) {
    // Fixed deterministic case generator: varied positive conductivity and source.
    const double k = 5.0 + (seed*37 % 1000)/100.0;
    const double q = 1000.0 + (seed*7919 % 10000);
    ThermalConfig c; c.elements=elements; c.conductivity=k; c.heat_generation=q;
    auto r=solve_thermal(c);
    double sum=0; for(const auto& n:r.nodes) sum += n.temperature;
    return sum;
}
std::vector<BenchmarkRow> run_benchmark(int cases, int elements, int reps) {
    if(cases<1 || elements<1 || reps<1) throw std::invalid_argument("cases, elements and repetitions must be positive");
    const unsigned logical=std::max(1u,std::thread::hardware_concurrency());
    const int maxw=std::min(4,(int)logical);
    std::vector<int> workers; for(int p=1;p<=maxw;++p) workers.push_back(p);
    std::vector<double> medians;
    for(int p:workers) {
        std::vector<double> times;
        for(int rep=0;rep<reps;++rep) {
            std::vector<double> out(cases);
            auto start=std::chrono::steady_clock::now();
            if(p==1) {
                for(int i=0;i<cases;++i) out[i]=one_case(i+1,elements);
            } else {
                std::vector<std::thread> pool;
                for(int w=0;w<p;++w) pool.emplace_back([&,w]{
                    for(int i=w;i<cases;i+=p) out[i]=one_case(i+1,elements);
                });
                for(auto& th:pool) th.join();
            }
            auto end=std::chrono::steady_clock::now();
            times.push_back(std::chrono::duration<double,std::milli>(end-start).count());
            volatile double checksum=std::accumulate(out.begin(),out.end(),0.0); (void)checksum;
        }
        std::sort(times.begin(),times.end()); medians.push_back(times[times.size()/2]);
    }
    std::vector<BenchmarkRow> rows;
    for(std::size_t i=0;i<workers.size();++i) {
        const double speed=medians[0]/medians[i];
        rows.push_back({workers[i],medians[i],speed,speed/workers[i],one_case(1,elements)});
    }
    return rows;
}
}
