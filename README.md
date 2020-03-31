# PUKI - Picture Utility King
Picture Utility King - simple image processing tool written in C as a homework at Budapest University of Technology and Economics

The program works with PPM images to make the code very simple. It's platform independent, tested on OS X El Capitan and Win 10.
It can be called via arguments. Below you can see usage informations.

## Functions
* blur: 35 pixel quarterly average (very slow, i know)
* sharpen 3x3 convulation matrix
* lighten: make the image 2x brighter
* darken: make the image 2x darker
* grayscale: make the image grayscale

## How to use
It can be called via arguments:
> puki < sourceimage.ppm > < destinationimage.ppm > < operation >

where <b> < sourceimage.ppm > </b> is the name of the image what we would like to modify, <b> < destinationimage.ppm > </b> is the name of the modified image what we will save and <b> < operation > </b> is the name of the function we would like to perform.
  
### Example
> puki first.ppm second.ppm grayscale
  
## What if an error occured
PUKI returns with 1 and an error message if something cannot be done. Otherwise it responds 0.

