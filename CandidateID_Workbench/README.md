# Unified Engineering Workbench — starter submission

**Status:** source starter, not a completed assessment. Do not submit this package as a fully compliant final build without completing and verifying the items in `docs/REMAINING_WORK.md`.

## Architecture
- `src/`: C++17 backend: 1D linear finite-element thermal solver, independent-case CPU benchmark, handwritten one-neuron backpropagation, basic ASCII STL/CSV structural validation.
- `include/`: public core interfaces.
- `ui/`: responsive browser UI prototype. It is not yet connected to the C++ executable.
- `tests/`: small CTest smoke test.
- `data/`: one ASCII STL sample and one explicitly synthetic nodal CSV.
- `docs/`: report template, design notes, outstanding work and AI-use log template.

## Build on Windows 11
Install Visual Studio 2022 Build Tools with the C++ workload and CMake, or use Visual Studio 2022. Then from this folder:

```powershell
cmake --preset windows-release
cmake --build --preset windows-release
ctest --test-dir build -C Release --output-on-failure
```

The executable is produced at `build/Release/workbench.exe` with the Visual Studio generator. This package does **not** include a prebuilt `Launch.exe`. A true one-click packaged executable still needs to be built and tested on Windows and bundled with all runtime dependencies.

## Commands
```powershell
.\build\Release\workbench.exe thermal 10 results\thermal_N10.csv
.\build\Release\workbench.exe thermal 20 results\thermal_N20.csv
.\build\Release\workbench.exe thermal 40 results\thermal_N40.csv
.\build\Release\workbench.exe thermal 80 results\thermal_N80.csv
.\build\Release\workbench.exe benchmark 2000 80 5
.\build\Release\workbench.exe neural 100
.\build\Release\workbench.exe inspect-stl data\sample_ascii.stl
.\build\Release\workbench.exe inspect-csv data\synthetic_nodal_temperatures.csv
```

## Thermal model
Two-node linear 1D elements; constant material and area; uniform volumetric heat generation; steady state; prescribed temperatures at both ends. Exact solution:
`T(x)=T_left+(T_right-T_left)x/L + q x(L-x)/(2k)`.
The implementation reports maximum absolute error at element midpoints using linear interpolation of nodal FE temperatures.

## Data provenance
`data/synthetic_nodal_temperatures.csv` is generated sample data, **not an ANSYS export**. The importer currently performs structural checks only; full numeric, finite-value, node-ID, and geometry validation remains to be implemented.

## Honest evidence policy
Do not claim tests, benchmarks, Windows launch, UI/backend integration, 3D rendering, hardware connectivity, or Git history unless you actually run and capture them. Record actual machine/compiler/CPU/RAM/flags and raw outputs.
