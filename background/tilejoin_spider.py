import sys
from PIL import Image
imgs = [
    'udg_spiderplant11',
    'udg_spiderplant21',
    'udg_spidershelfleft',
    'udg_spidershelfright',
    'udg_spiderempty',
    'udg_spiderbook'
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

new_im.save('level5.png')
