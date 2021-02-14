import sys
from PIL import Image
imgs = [
    'udg_corazon_01',
    'udg_corazon_02',
    'udg_corazon_roto_01',
    'udg_corazon_roto_02',
    'rata_derecha_01',
    'rata_derecha_02',
    'rata_izquierda_01',
    'rata_izquierda_02'
]
for idx, item in enumerate(imgs):
    print('#define UDG_' + item.upper() + ' {}'.format(128+idx))


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


new_im.save('last.png')
