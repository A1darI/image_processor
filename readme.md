## image_processor

This is a console application for processing 24-bit BMP files.

## Description

[image_processor.cpp](https://github.com/A1darI/image_processor/blob/012ecaeb51d8c96ae99dc8248fb0e9c9dace86e8/image_processor.cpp) - initial source file

filters - all filters implementation

examples - filter application example

file_handling - implementation of reading and writing BMP files

[image.h](https://github.com/A1darI/image_processor/blob/bb41d152d47e1a3b0ba57b9ae46dad3ac8549dbf/image.h) - image representation

[cmd_parser.h](https://github.com/A1darI/image_processor/blob/bb41d152d47e1a3b0ba57b9ae46dad3ac8549dbf/cmd_parser.h) - command line parsing


### Supported image format

Input and output graphic files must be in the format [BMP](http://en.wikipedia.org/wiki/BMP_file_format).

A 24-bit BMP file is used without compression and without a color table. The type of `DIB header` used is `BITMAPINFOHEADER`.

### Arguments format

When run without arguments, the program displays help.

### Filters

#### Crop (-crop width height)
Crop the image to the specified width and height. The top left of the image is used.

If the requested width or height exceeds the dimensions of the original image, the available portion of the image is returned.

#### Grayscale (-gs)
Converts an image to grayscale using a formula

![encoding](https://latex.codecogs.com/svg.image?R'%20=%20G'%20=%20B'%20=0.299%20R%20&plus;%200%20.587%20G%20&plus;%200%20.%20114%20B)

#### Negative (-neg)
Converts an image to a negative using the formula

![encoding](https://latex.codecogs.com/svg.image?R'%20=%201%20-%20R,%20G'%20=%201%20-%20G,%20B'%20=%201%20-%20B)

#### Sharpening (-sharp)
Sharpening. Achieved by using a matrix

![encoding](https://latex.codecogs.com/svg.image?%5Cbegin%7Bbmatrix%7D%20&%20-1%20&%20%20%5C%5C-1%20&%205%20&%20-1%20%5C%5C%20&%20-1%20&%20%20%5C%5C%5Cend%7Bbmatrix%7D)

#### Edge Detection (-edge threshold)
Boundary selection. The image is converted to grayscale and a matrix is applied

![encoding](https://latex.codecogs.com/svg.image?%5Cbegin%7Bbmatrix%7D%20&%20-1%20&%20%20%5C%5C-1%20&%204%20&%20-1%20%5C%5C%20&%20-1%20&%20%20%5C%5C%5Cend%7Bbmatrix%7D)

Pixels with a value that exceeds `threshold` are painted white, the rest are black.

#### Gaussian Blur (-blur sigma)
[Gaussian_blur](https://en.wikipedia.org/wiki/Gaussian_blur),

The value of each of the colors of the `C[x0][y0]` pixel is determined by the formula

![encoding](https://latex.codecogs.com/svg.image?C%5Bx_0%5D%5By_0%5D%20=%20%5Csum_%7Bx=0,y=0%7D%5E%7Bwidth-1,%20height-1%7DC%5Bx%5D%5By%5D%5Cfrac%7B1%7D%7B%5Csqrt%5B%5D%7B2%5Cpi%5Csigma%5E2%7D%7De%5E%7B-%5Cfrac%7B%5Cleft%7Cx_o-x%5Cright%7C%5E2%20&plus;%20%5Cleft%7Cy_o-y%5Cright%7C%5E2%7D%7B2%5Csigma%5E2%7D%7D)

#### Crystallize filter(-crystallize number_of_superpixels compactness)
Implements a simple linear iterative clustering algorithm [SLIC](https://www.iro.umontreal.ca/~mignotte/IFT6150/Articles/SLIC_Superpixels.pdf)
