# Mixed Precision Proof-of-Concept

The repo contains a proof-of-concept of one way of setting up "mixed precision" support in a library.

## Motivation

* Allow for the compile-time configuration of the precision used by the library (i.e. build everything either in double precision or in single precision).
   * If the library is re-configured with a different precision, applications will use the newly configured precision without changing their code.
* Allow the same application to mix double-precision and single-precision computations.
   * For example, operator evaluation can be performed in double precision and the preconditioner can be applied in single precision.
* If mixed precision support is not desired or needed, then there is no extra compile time (the library can be compiled for only one precision if wanted).
* Minimal changes to the existing library (i.e. not everything needs to be templated).
* Backwards compatible: all existing applications should continue to compile/work with no changes.

## How it Works

The makefile will build a library (`libexample.a`) and an executable linking against the library (`main`).

There are two configuration options available in the makefile:

* `ENABLED_PRECISIONS` contains a list of enabled precicisions (i.e. one or both of `FP64` and `FP32`)
* `DEFAULT_PRECISION` defines the default precision, and must be one of the precisions listed in `ENABLED_PRECISIONS`.

If `FP64` is enabled, the double-precision API will be made available in the `mp::fp64` namespace. Likewise, if `FP32` is enabled, the single-precision API will be made available in the `mp::fp32` namespace. If both are enabled, then both `mp::fp64` and `mp::32` namespaces will be available, and the library will have both versions compiled.

Depending on `DEFAULT_PRECISION`, all the names from either `mp::64` or `mp::32` will be injected into the `mp` namespace with a `using` directive. This allows users to access e.g. `mp::Vector` without specifiying the desired precision—the configured `DEFAULT_PRECISION` will be used in this case.

Running the `main` executable will print out the element type (either `double` or `float`) used for three vectors:

```cpp
mp::Vector v1(10);
mp::fp64::Vector v2(10);
mp::fp32::Vector v3(10);
```

The vector `v1` will have element type defined by `DEFAULT_PRECISION`. Vectors `v2` and `v3` will ahve element types `double` and `float`, respectively.

The expected output (with `DEFAULT_PRECISION = FP64`) is:

```
The vector v1 has elements of type: double
The vector v2 has elements of type: double
The vector v3 has elements of type: float
```

Removing one of `FP64` or `FP32` from the `ENABLED_PRECISIONS` list will result in a compile-time error (unless the corresponding `v2` or `v3` is deleted from `main.cpp`).
