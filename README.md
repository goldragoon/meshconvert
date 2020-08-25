# meshconvert

Convert numerous formats of 3D mesh files into another.
Natively supports multithreading, conversion of 3D mesh files stored in certain directory hierarchy.

## BUILD
```
mkdir build && cd build
cmake ..
make
```

## Usage
./meshconvert --source=[SOURCE] --destination=[DESTINATION] --format=obj

## Example
```
./meshconvert --source=data/bunny.ply --destination=output.obj --format=obj # Single File
./meshconvert --source=data --destination=output --format=obj # Directory
```

## Dependencies
Boost, assimp, cxxopts
