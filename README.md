# cppvk

Build: `bazel build //:cppvk` (Note: By default, Bazel will create files outside of the code directory and symlink to them)

Run: `./bazel-bin/cppvk`

Dependency graph: `bazel query --notool_deps --noimplicit_deps "deps(//:cppvk)" --output graph`
