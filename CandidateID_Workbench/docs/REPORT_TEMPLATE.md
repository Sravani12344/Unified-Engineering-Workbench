# Unified Engineering Workbench — Technical Report

**Candidate ID:** [enter ID]  
**Build/version:** [actual version]  
**Date:** [date]

## 1. Overview and architecture
[Describe the implemented user workflow and actual architecture. Add an architecture diagram. Distinguish implemented features from planned features.]

## 2. Geometry and data handling
[Document accepted ASCII STL and CSV schema, units, provenance, validation, tested size limits, viewer controls, and screenshots. Clearly label synthetic data.]

## 3. Thermal finite-element analysis
Model: `-d/dx(kA dT/dx)=qA`.  
Parameters: L=1 m, A=1e-4 m², k=10 W/(m·K), q=10000 W/m³, T(0)=100°C, T(L)=20°C.  
Exact solution: `T_exact(x)=100-80x/L+[q/(2k)]x(L-x)`.  
[Explain assembly, Dirichlet boundary conditions, solver, midpoint error, mesh convergence. Insert actual N=10,20,40,80 results and plots.]

## 4. Performance
[Actual CPU model, physical/logical cores, RAM, compiler/version, optimization flags, workload, warm-up, five raw repetitions, medians, speedup and efficiency. Include serial/parallel numerical-difference check.]

## 5. Hardware abstraction
[Actual module diagram and mock adapter demonstration. Identify all simulated interactions. Explain JTAG is a debug/programming interface, not a compute board.]

## 6. Neural-network backpropagation
[Insert handwritten derivation appendix (max two pages). Explain forward pass, four chain-rule gradients, simultaneous update, finite-difference validation and actual loss curve.]

## 7. Testing, limitations and AI-use disclosure
[Actual tests and outcomes, known limitations, representative AI prompts/outputs, human edits, validation, and one unsuitable AI suggestion or deliberate challenge test.]

## 8. Conclusion
[Summarize only verified implementation outcomes.]
