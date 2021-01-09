import sys
from PIL import Image
imgs = [
    'j_ladrillos',
    'queso_textura',
    'j_piedras',
    'udg_valla2',
    'udg_valla1',
    'udg_valla3',
    'udg_valla4',
    'cubo_down1',
    'cubo_down2',
    'cubo_down3',
    'cubo_middle1',
    'cubo_middle2',
    'cubo_middle3',
    'cubotop1',
    'cubotop2',
    'cubotop3',
    'udg_c',
    'udg_a',
    'udg_t',
    'udg_rope',
    'udg_win1',
    'udg_win2',
    'udg_clothes11',
    'udg_clothes12',
    'udg_clothes21',
    'udg_clothes22',
    'udg_boot',
    'udg_boot2',
    'j_valla_rota',
    'grosor_ventana'
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
