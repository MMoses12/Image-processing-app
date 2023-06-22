# Image Processing Program

This is a command-line program for image processing. It allows users to perform various operations on images, such as exporting, deleting, inverting colors, equalizing histograms, mirroring, converting to grayscale, scaling, and rotating on PPM or PGM images.

## Features

- Export an image combined with a token to a file in PGM or PPM format, depending on whether the image is grayscale or color.
- Delete an image and its corresponding token from memory.
- Invert the brightness of an image.
- Equalize the histogram of an image.
- Mirror an image vertically.
- Convert a color image to grayscale.
- Scale an image by a given factor.
- Rotate an image clockwise or counterclockwise a specified number of times.
- Quit the program.

## Usage

To use the program, run the executable and enter the corresponding commands:

- `e <$token> as <filename>`: Export the image with the specified token to a file.
- `d <$token>`: Delete the image with the specified token.
- `n <$token>`: Invert the colors of the image with the specified token.
- `z <$token>`: Equalize the histogram of the image with the specified token.
- `m <$token>`: Mirror the image vertically.
- `g <$token>`: Convert the image to grayscale.
- `s <$token> by <factor>`: Scale the image by the given factor.
- `r <$token> clockwise <X> times`: Rotate the image clockwise or counterclockwise by the specified number of times.
- `q`: Quit the program.

## Error Handling

The program provides error messages in case of the following situations:

- If the exported file already exists: `[ERROR] File exists`
- If the user doesn't have permission to create or write to the file: `[ERROR] Unable to create file`
- If the image is already grayscale: `[NOP] Already grayscale $token`

## Examples

Here are a few examples of command usage:

- `e $1 as image.pgm`: Export the image with token `$1` to a file named `image.pgm`.
- `d $2`: Delete the image with token `$2`.
- `n $3`: Invert the colors of the image with token `$3`.
- `m $4`: Mirror the image with token `$4`.
- `g $5`: Convert the image with token `$5` to grayscale.
- `s $6 by 2.5`: Scale the image with token `$6` by a factor of 2.5.
- `r $7 clockwise 3 times`: Rotate the image with token `$7` clockwise 3 times.
