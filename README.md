
# ACPLT/RTE example application project

This repository represents an example of an application-specific project build with the ACPLT/OV runtime environment (https://github.com/acplt/rte).
It demonstrates, how the ACPLT/RTE core repository and additional library repositories can be combined with custom libraries to allow building the runtime environment with an application-specific set of libraries in one go.
For more information on this project structure, please refer to OV's readme file:
https://github.com/acplt/rte#project-structure

The included custom library `demolib` shows a really simple example of a custom OV library.


## Building

The composed project forms a singe CMake project that requires the same build steps as the ACPLT/OV RTE core project.
On Linux, this typically includes installing GCC, `make`, `cmake`, `tcl`, `bison` and `flex` and executing the following commands:
```bash
mkdir build
cd build
cmake ..
make -j 4
```

For more advanced build setups and building on (or for) other platforms, see OV's readme file:
https://github.com/acplt/rte#building-acpltov


## Development

When playing around with the `demolib` code and making changes to its OVM model file, you'll want to (re-)generate the C sourcecode templates as a reference for the expected C function signatures.
For this task, the `acplt_builder` program is included in the `rte` core repository and build with the overall project.

So, after building the project once (or explicitly building the program with `make acplt_builder`), you can run `acplt_builder` in the project root:
```bash
export OV_LIBRARY_PATH="$(pwd)/rte/core:$(pwd)/rte/syslibs:$(pwd)/rte_fblib:$(pwd)/rte_fblib:$(pwd)/rte_field"
build/rte/core/acplt_builder/acplt_builder -f -l demolib/model/demolib.ovm
```

For more information about `acplt_builder`, see OV's readme file:
https://github.com/acplt/rte#generating-library-source-templates
