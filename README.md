# Bin-Packing
A take on the bin packing problem written in C++

An implementation of the bin packing problem. This program takes a given 8 item sizes and attempts to pack them into bins, putting it in an existing bin if there is enough space, or creating a new bin if there is not.

The program also estimates the number of extra bins; the ratio used for optimal bins to extra bins is 3:2.

It also allows the user to specify a random number of items to pack. It assigns random sizes to those items and packs them, again calculating the estimated number of extra bins used.
