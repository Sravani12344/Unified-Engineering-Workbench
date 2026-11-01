# Architecture notes

Intended layers:
1. UI/presentation: user selects inputs, sees validation, progress and results.
2. Application orchestration: validates requests, schedules work, handles cancellation and exports.
3. C++ domain core: mesh assembly, numerical solution, file parsing, benchmark scheduling, adapter interfaces.
4. Platform adapters: filesystem, CPU/threading and future hardware transports.

Current implementation: C++ CLI core plus static UI prototype. The UI is not yet connected to the CLI; this is a known gap.
