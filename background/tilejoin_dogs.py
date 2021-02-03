import sys
from PIL import Image
imgs = [
    'udg_cuenco_vacio',
    'udg_cuenco_lleno',
    'udg_cachorro_derecha_cola',
    'udg_cachorro_derecha_cuerpo',
    'udg_cachorro_derecha_cabeza',
    'udg_cachorro_derecha_cabeza_ojos',
    'udg_cachorro_izquierda_cabeza',
    'udg_cachorro_izquierda_cuerpo',
    'udg_cachorro_izquierda_cola',
    'udg_cachorro_izquierda_cabeza_ojos',
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

new_im.save('level7.png')
