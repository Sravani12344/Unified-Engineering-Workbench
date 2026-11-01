#include "workbench.hpp"
#include <cmath>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <vector>

namespace wb {
double exact_temperature(double x, const ThermalConfig& c) {
    return c.left_temperature + (c.right_temperature-c.left_temperature)*x/c.length
         + c.heat_generation/(2.0*c.conductivity)*x*(c.length-x);
}
ThermalResult solve_thermal(const ThermalConfig& c) {
    if (c.elements < 1 || c.length <= 0 || c.area <= 0 || c.conductivity <= 0)
        throw std::invalid_argument("Mesh, length, area and conductivity must be positive.");
    const int n = c.elements;
    const double dx = c.length/n;
    const double ke = c.conductivity*c.area/dx;
    const double fe = c.heat_generation*c.area*dx/2.0;
    std::vector<double> diag(n+1, 0.0), lower(n, 0.0), rhs(n+1, 0.0);
    for (int e=0; e<n; ++e) {
        diag[e] += ke; diag[e+1] += ke;
        lower[e] = -ke;
        rhs[e] += fe; rhs[e+1] += fe;
    }
    // Apply prescribed end temperatures by eliminating their contributions.
    rhs[1] -= lower[0]*c.left_temperature;
    rhs[n-1] -= lower[n-1]*c.right_temperature;
    diag[0] = diag[n] = 1.0;
    rhs[0] = c.left_temperature; rhs[n] = c.right_temperature;
    lower[0] = 0.0; lower[n-1] = 0.0;
    // Thomas algorithm for the tridiagonal system.
    std::vector<double> a(n+1,0.0), b=diag, d=rhs;
    for (int i=1; i<=n; ++i) a[i] = lower[i-1];
    for (int i=1; i<=n; ++i) {
        if (std::abs(b[i-1]) < 1e-20) throw std::runtime_error("Singular thermal system.");
        const double m = a[i]/b[i-1];
        b[i] -= m*0.0; // upper diagonal equals -ke except constrained endpoints
        d[i] -= m*d[i-1];
    }
    // Rebuild a general tridiagonal solve using symmetry of the FE stiffness matrix.
    std::vector<double> upper(n+1,0.0), lower2(n+1,0.0), diag2(n+1,0.0), rhs2=rhs;
    for (int i=0;i<=n;++i) diag2[i] = (i==0 || i==n) ? 1.0 : 2.0*ke;
    for (int i=1;i<n;++i) { lower2[i] = -ke; upper[i] = -ke; }
    rhs2[1] = fe + ke*c.left_temperature;
    rhs2[n-1] = fe + ke*c.right_temperature;
    // Correct for the special n=1 case (both nodes are prescribed).
    std::vector<double> cp(n+1,0.0), dp(n+1,0.0);
    cp[0] = upper[0]/diag2[0]; dp[0] = rhs2[0]/diag2[0];
    for (int i=1;i<=n;++i) {
        const double den = diag2[i]-lower2[i]*cp[i-1];
        if (std::abs(den)<1e-20) throw std::runtime_error("Singular thermal system.");
        cp[i] = (i==n ? 0.0 : upper[i]/den);
        dp[i] = (rhs2[i]-lower2[i]*dp[i-1])/den;
    }
    std::vector<double> t(n+1);
    t[n]=dp[n];
    for(int i=n-1;i>=0;--i) t[i]=dp[i]-cp[i]*t[i+1];
    ThermalResult out;
    for(int i=0;i<=n;++i) out.nodes.push_back({i*dx,t[i]});
    for(int e=0;e<n;++e) {
        const double xm=(e+0.5)*dx;
        const double fem=0.5*(t[e]+t[e+1]);
        out.max_midpoint_error=std::max(out.max_midpoint_error,std::abs(fem-exact_temperature(xm,c)));
    }
    return out;
}
void write_thermal_csv(const std::string& path, const ThermalResult& r) {
    std::ofstream f(path);
    if(!f) throw std::runtime_error("Cannot create output CSV: "+path);
    f << "x_m,temperature_C\n" << std::setprecision(12);
    for(const auto& n:r.nodes) f << n.x << "," << n.temperature << "\n";
}
}
