# QMK config for Corne 

## Memory

In `config.h`, using RGB uses up a lot of memory, but not importing fancy RGB animations (e.g. breathing)
results in a much smaller memory footprint!

## Display 

To make the display I used the following useful sites:

- [Convert image to hex array, image2cpp](https://javl.github.io/image2cpp/)
- [Pixel art drawer](https://www.pixilart.com)

Image2cpp is a bit rough, e.g. for small features, what did work pretty well however was:

1. Use Figma to make the nacho outlines as svg.
2. Use pixel art drawer to import svg, add manually small features like eyes and smiles, then save to image.
3. Use Image2cpp on the output of the previous step.

Note that It seems easier to skip step 2, and do the features on figma, but adding 2 did help. Maybe It could be skipped
if I added features in figma pixelwise (e.g. the smile.)
