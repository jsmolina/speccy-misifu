import sys
from PIL import Image
imgs = [
    'udg_watertop',
    'udg_watertop2',
    'udg_fish',
    'udg_fish2',
    'udg_fishL',
    'udg_fishL2',
    'udg_serp_F1_01',
    'udg_serp_F2_01',
    'udg_serp_F1_02',
    'udg_serp_F2_02',
]

imgs = [i + '.png' for i in imgs]
images = [Image.open(x) for x in imgs]
widths, heights = zip(*(i.size for i in images))

total_width = sum(widths)
max_height = max(heights)

new_im = Image.new('RGB', (total_width, max_height))

x_offset = 0
for im in images:
  new_im.paste(im, (x_offset,0))
  x_offset += im.size[0]

new_im.save('test.png')
