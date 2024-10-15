![Alt text](screenshot/output.png)
# PPMWriter
- Used to write text to a ppmimage
- Only supports ascii characters defined in MFont.hh, any other codepoint is replaced with the inverted "?"
- No external FONTS/Libraries used, only depends on stdlib
## Convert .ppm to .png/.jpeg
>ffmpeg -i output.ppm output.png
