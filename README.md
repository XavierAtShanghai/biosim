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
# animation of some numerical results
## a pulse propagates through an arterial cirlcle
![Alt Text](https://github.com/XavierAtShanghai/biosim/blob/master/animation/convert.gif)
## pressure wave propagation through the whole arterial system of an adult human
![Alt Text](https://github.com/XavierAtShanghai/biosim/blob/master/animation/heart2fig.gif)
## pressure wave propagtion through the arterial network of a kindey of mouse
![Alt Text](https://github.com/XavierAtShanghai/biosim/blob/master/animation/kidneyM1.gif)

# If this code is helpful for your research, please cite the following article:
```
@article{wang2015verification,
  title={Verification and comparison of four numerical schemes for a 1D viscoelastic blood flow model},
  author={Wang, Xiaofei and Fullana, Jose-Maria and Lagr{\'e}e, Pierre-Yves},
  journal={Computer methods in biomechanics and biomedical engineering},
  volume={18},
  number={15},
  pages={1704--1725},
  year={2015},
  publisher={Taylor \& Francis}
}
```
