#!/usr/bin/env python
"""
png2udg.py

Copyright (C) 2018 Jordi Sesmero
Based on the original idea from Juan J. Martinez
Uses UDG format z88dk SP1: ZXSpectrumZSDCCnewlib_SP1_04_BiggerSprites.md

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

"""
__version__ = "1.0.1"

from argparse import ArgumentParser
from PIL import Image
from os.path import basename

INK = (255, 255, 255)
PAPER = (205, 0, 0)
MASK = (0, 0, 0)

COLORS = [INK, PAPER, MASK,]


def get_value(rgb, animated=False):
    """
    Obtains pixel value if it is enabled. Color is not supported yet here.
    :param rgb:
    :param animated: It is a WTF from SP1. If I do animation it requires me to invert the values...
    :return:
    """

    if rgb[0] > 0 or rgb[1] > 0 or rgb[2] > 0:
        return "1" if not animated else "0"
    else:
        return "0" if not animated else "1"


def do_formatted(column):
    """
    Generates binary formatted value from column array
    :param column:
    :return:
    """
    return "0x{:02x}".format(int('{}'.format(''.join(column)), 2))



def main():
    animated = False

    parser = ArgumentParser(description="png2sp1sprite",
                            epilog="Copyright (C) 2018 Jordi Sesmero",
                            )

    parser.add_argument("--version", action="version", version="%(prog)s "  + __version__)
    parser.add_argument("-i", "--id", dest="id", default="sprite", type=str,
                        help="variable name (default: sprite)")

    parser.add_argument("-b", "--base", dest="base",
                        help="generate asm file", action='store', default=128)

    parser.add_argument("image", help="image to convert", nargs="?")

    args = parser.parse_args()

    base = int(args.base)

    if not args.image:
        parser.error("required parameter: image")
    name = basename(args.image).split('.')[0]

    try:
        image = Image.open(args.image)
    except IOError:
        parser.error("failed to open the image")
        exit(1)

    (w, h) = image.size

    if (w % 8) != 0 or h != 8:
        parser.error("%r size should be 8x8 8 but it is %sx%s" % (args.image, w, h))

    rows = []
    blocks = []
    fmt = ""
    for bloque in range(0, w, 8):
        gdu = []
        for y in range(0, h):
            col = []
            # vamos al bloque de 8 que toca (ej: 0 al 8, 8 al 16, 16 al 24, 24 al 32)
            for x in range(bloque, bloque + 8):
                pixel = image.getpixel((x, y))
                col.append(get_value(pixel, animated=False))

            gdu.append(do_formatted(col))
        rows.append(gdu)
    len_name = "{}_TILES_LEN".format(name.upper())
    base_name = "{}_TILES_BASE".format(name.upper())
    print("#define {}  {}".format(len_name, len(rows)))
    print("#define {}  {}".format(base_name, base))
    print("const uint8_t " + name + "[] = {")
    for idx, r in enumerate(rows):
        print(', '.join(r) + ',' + ' // y:0, x:{} ({})'.format(idx, str(idx + base)))
    print('};')
    print("uint8_t *pt = {};".format(name))
    print("/* So now you can use: ")
    print("for (i = 0; i < {}; i++, pt += 8)".format(len_name))
    print("    sp1_TileEntry({} + i, pt);".format(base_name))
    print("\nand printing every udg as simple as")
    print("sp1_PrintAt(row, col, INK, something > 128);")
    print("*/")


if __name__ == "__main__":
    main()

