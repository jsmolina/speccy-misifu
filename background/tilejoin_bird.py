import sys
from PIL import Image
imgs = [
    'udg_cuadro_superior_izquierda',
    'udg_cuadro_superior_derecha',
    'udg_cuadro_inferior_izquierda',
    'udg_cuadro_inferior_derecha',
    'udg_jaula_derecha_rota',
    'udg_jaula_derecha',
    'udg_jaula_izquierda',
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

new_im.save('level6.png')
