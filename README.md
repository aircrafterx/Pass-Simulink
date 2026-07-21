# PASS-Simulink: Real-Time Block Diagram Simulator

An interactive, web-based graphical environment for building, saving, loading, and simulating dynamic block diagrams (similar to MATLAB/Simulink). The application features a high-performance C++ backend for execution schedulers and topological sorting, coupled with a React/Vite-based graphical drag-and-drop frontend with real-time waveform visualization.

---

## Architecture Overview

PASS-Simulink is divided into two primary subsystems:

1. **High-Performance C++ Simulation Backend (`PASS-Backend`)**:
   - Built with **C++20** and standard library components.
   - Uses **Kahn's Topological Sorting Algorithm** to execute blocks in dependency order.
   - Performs **Cycle Detection** to prevent invalid simulation loops from freezing execution.
   - Binds an HTTP server on port `8085` (using `cpp-httplib` and `nlohmann/json`) to handle compiler execution requests and state saving/loading.
   - Provides default block implementations:
     - **Sources**: Clock, Sine, Cosine
     - **Math**: Add, Subtract, Multiply, Average, Gain, Min, Max
     - **Sinks**: Scope (records traces)

2. **Interactive Drag-&-Drop Frontend (`PASS-Frontend`)**:
   - Built on **React** with **Vite** as the bundler.
   - Uses **HTML5 Drag and Drop API** and svg-based rendering for block connections.
   - Connects to the backend via a REST API.
   - Features **Real-Time Scope Animation**: simulation outputs are dynamically animated point-by-point to resemble physical oscilloscope sweeps, rather than stretching statically.
   - Exposed editor context under `window.simulinkEditor` for simple E2E browser testing.

---

## Environment Setup (Fresh System)

### 1. Prerequisites

#### For both OS (Windows / Linux / macOS):
- **Node.js** (v18.0.0 or higher) and **npm** (v9.0.0 or higher)
- **CMake** (v3.20 or higher)
- **Git** (for cloning submodules/repositories)
- **C++ Compiler** with **C++20 support**:
  - **Windows**: MSVC (Visual Studio 2022+ with Desktop development with C++) or MinGW-w64.
  - **macOS**: Clang (Xcode Command Line Tools).
  - **Linux**: GCC (v10+).

---

## Compilation & Run Instructions

Follow these instructions to compile and run both applications.

### 1. Backend Server Setup (`PASS-Backend`)

Open a terminal at the project root folder.

```bash
cd PASS-Backend
mkdir build
cd build
```

Then compile:

#### Windows (with MSVC):
```cmd
cmake ..
cmake --build . --config Release
```
This builds the server executable in `./Release/PASS_Simulink_Backend.exe` or `./PASS_Simulink_Backend.exe`.

#### Linux & macOS:
```bash
cmake ..
cmake --build .
```
This builds `./PASS_Simulink_Backend`.

To run the backend server:
```bash
# Windows
.\Release\PASS_Simulink_Backend.exe

# Linux/macOS
./PASS_Simulink_Backend
```
The console will output:
`PASS-Simulink backend listening on port 8085...`

*Note: The backend automatically saves/loads block diagrams to a `project.json` file inside the build execution directory.*

---

### 2. Frontend Application Setup (`PASS-Frontend`)

Open another terminal at the project root folder.

```bash
cd PASS-Frontend
npm install
```

To run the development server locally:
```bash
npm run dev
```

Once running, navigate to the local server URL displayed in the terminal:
**`http://localhost:5173/`**

---

## Using the Simulator

1. **Assemble Diagram**: Drag source blocks (e.g., `Clock`, `Sine Wave`), math blocks (e.g., `Multiply`, `Add`), and sink blocks (e.g., `Scope`) from the left-hand block library panel onto the grid canvas.
2. **Connect Ports**: Drag from the output port circle on the right side of a block to the input port circle on the left side of another block.
3. **Configure Settings**: Edit simulation settings at the bottom pane:
   - `Start` (Default: `0.0`)
   - `End` (Default: `10.0`)
   - `Step` (Default: `0.1` - controls interval ticks)
4. **Execute**: Click the **Run Simulation** button. The scope panel will animate the values left-to-right in real-time.
5. **Persist State**:
   - Click **Save** to serialize the graphical layout + parameters and save it as `project.json` on the server's build directory.
   - Click **Load** to reload the layout on canvas at any time.
