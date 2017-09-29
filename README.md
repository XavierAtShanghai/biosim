# COMPILE
```
make
```

# Usage
```
bin/bloodlfow
Usage: bloodflow -i inputFolder -o dataFolder [-s string] [-q] [-v]
-h --help	Display this usage information.
-i --input	folderName Parameter files to initalize the computing.
-o --output	folderName Write output to this folder.
-s --suffix	string Suffix to the names of output files.
-q --sequential sequential computing, otherwise using openMP.
-v --verbose	Print verbose messages.
```
# run examples
### one artery segment
```
bin/bloodflow  -i example/oneArtery/param/ -o example/oneArtery/data_result/
```
### one branch
```
bin/bloodflow  -i example/oneBranching/param/ -o example/oneBranching/data_result/
```
### one branch-convergence (circle)
```
bin/bloodflow  -i example/branchConvergence/param/ -o example/branchConvergence/data_result/
```
