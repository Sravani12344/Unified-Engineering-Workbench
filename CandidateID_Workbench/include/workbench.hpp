#pragma once
#include <cstddef>
#include <string>
#include <vector>

namespace wb {
struct ThermalConfig {
    double length = 1.0, area = 1e-4, conductivity = 10.0;
    double heat_generation = 10000.0, left_temperature = 100.0, right_temperature = 20.0;
    int elements = 10;
};
struct ThermalNode { double x, temperature; };
struct ThermalResult {
    std::vector<ThermalNode> nodes;
    double max_midpoint_error = 0.0;
};
ThermalResult solve_thermal(const ThermalConfig& cfg);
double exact_temperature(double x, const ThermalConfig& cfg);
void write_thermal_csv(const std::string& path, const ThermalResult& result);

struct BenchmarkRow {
    int workers;
    double median_ms, speedup, efficiency;
    double checksum;
};
std::vector<BenchmarkRow> run_benchmark(int cases, int elements, int repetitions);

struct NNResult {
    double prediction, loss;
    double dw, db, dv, dc;
    double w, b, v, c;
    double finite_difference_max_error;
    std::vector<double> loss_history;
};
NNResult train_one_neuron(int steps = 100, double learning_rate = 0.1);
bool validate_stl_ascii(const std::string& path, std::size_t& triangle_count, std::string& error);
bool validate_nodal_csv(const std::string& path, std::size_t& row_count, std::string& error);
}
