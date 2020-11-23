# Porous
---
A (WIP) program that processes the [Big Graphene dataset](https://nrc-digital-repository.canada.ca/eng/view/object/?id=9f09901d-0736-4204-a35d-0c88ffb8da3b), consisting of DFT calculations of ground state energy for 500,000 samples of graphene with random pores, made for training an [Extensive Deep Neural Network](https://github.com/millskyle/extensive_deep_neural_networks). The program will collect all the samples into one hdf5 file and replace the positions of each carbon molecule into potential wells according to [this publication](https://pubs.rsc.org/en/content/articlelanding/2019/SC/C8SC04578J#!divAbstract).