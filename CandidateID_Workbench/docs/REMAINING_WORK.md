# Remaining work before a compliant final submission

This package is an honest starter, not a completed Unified Engineering Workbench.

1. **One-click delivery (mandatory):** build on Windows x64, produce `Launch.exe`, package runtime DLLs if needed, verify launch after extracting ZIP on a clean Windows account. Do not use a first-run source build.
2. **UI/backend integration:** connect the browser UI to a local C++ service or replace it with a native UI. Add operation progress, cancellation/safe completion, validation messages, exports and status.
3. **Geometry:** implement complete ASCII STL parsing and actual 3D triangle rendering with rotate/pan/zoom/fit. Implement full nodal CSV numeric parsing, non-finite rejection, node inspection, coloured 3D point cloud and legend.
4. **FEA:** verify the implementation independently, run N=10/20/40/80, save raw CSV, plot exact and FE curves and mesh-convergence/error data. Add boundary-condition and malformed-input tests.
5. **Performance:** run serial and parallel using identical generated cases and compare per-case outputs; current benchmark times serial/parallel but does not yet emit a serial-vs-parallel max-difference check or full raw repetition data. Capture CPU model, physical/logical cores, RAM, compiler, flags and five repetition timings.
6. **Hardware:** implement three mock adapter classes with discover/capabilities/connect/disconnect/telemetry and a recoverable timeout demo. Current UI is documentation-only.
7. **Backprop:** verify handwritten gradient derivation and produce a legible handwritten two-page maximum appendix. Export the full 101-point loss history and plot it.
8. **Quality:** expand tests for invalid values, malformed files, empty files, large files, cancellation and deterministic ordering. Add meaningful Git commits and include a real repository/bundle.
9. **Report/demo:** replace every placeholder with actual results and screenshots. Do not invent test or benchmark evidence.
