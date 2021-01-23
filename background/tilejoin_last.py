import sys
from PIL import Image
imgs = [
    'heart1',
    'heart2',
    'cupid11',
    'cupid12',
    'cupid13',
    'cupid21',
    'cupid22',
    'cupid23',
    'cupid31',
    'cupid32',
    'cupid33',
    'catheaven1',
    'catheaven2',
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
