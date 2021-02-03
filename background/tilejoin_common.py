import sys
from PIL import Image
imgs = [
    'wall1',
    'wall2',
    'wall3',
    'wall4',
    'curtain',
    'q_barra_cortina',
    'udg_sillaL',
    'udg_sillaLM',
    'udg_sillaRM',
    'udg_sillaR',
    'mesatop',
    'mesapata',
    'mesaside',
    'q_mesabase',
    'wall5',
    'lamp1',
    'lamp2',
    'udg_silla2_parte01',
    'udg_silla2_parte02',
    'udg_silla2_parte03',
    'udg_silla2_parte04',
]
result = ["#define {} {}".format(i.upper(), idx + 128) for idx, i in enumerate(imgs)]
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

new_im.save('rooms.png')
