Corey LeFevre
CS475 CUDA1 README

VecAdd:
Experiment to show how coalesced memory accesses improve performance on GPU.
Original kernel used and timed for vectors of 500, 1000, and 2000 elements.
Then new kernel created that used coalesced accesses and timed again for same number of elements.

MatMult:
Experiment to show how performance is affected by block and tile size.
Original kernel used and timed for square matrices of size 256x256, 512x512, and 1024x1024.
New kernel created from original that used footprint of 32 and modified to work correctly.
New kernel timed for same matrix sizes.
