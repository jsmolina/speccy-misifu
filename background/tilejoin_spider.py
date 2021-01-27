import sys
from PIL import Image
imgs = [
    'udg_estanteria_der_01',
    'udg_estanteria_der_02',
    'udg_estanteria_izq_01',
    'udg_estanteria_izq_02',
    'udg_estanteria_top_vacio',
    'udg_jarron_flores',
    'udg_jarron_der',
    'udg_jarron_izq',
    'udg_libro_inclinado_01',
    'udg_libro_inclinado_02',
    'udg_libros_01',
    'udg_libros_02'
]
result = ["#define {} {}".format(i.upper(), idx + 65) for idx, i in enumerate(imgs)]
print('\n'.join(result))

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
