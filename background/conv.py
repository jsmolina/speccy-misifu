import sys

imgs = [
    ('j_ladrillos', '$'),
    ('queso_textura', 144),
    ('j_piedras', '%'),
    ('udg_valla2', 'V'),
    ('udg_valla1', 'W'),    ('udg_valla3', 'X'),
    ('udg_valla4', 'Y'),
    ('cubo_down1', 'L'),
    ('cubo_down2', 'D'),
    ('cubo_down3', 'E'),
    ('cubo_middle1', 'F'),
    ('cubo_middle2', 'G'),
    ('cubo_middle3', 'H'),
    ('cubotop1', 'I'),
    ('cubotop2', 'J'),
    ('cubotop3', 'K'),
    ('udg_c', 'C'),
    ('udg_a', 'A'),
    ('udg_t', 'T'),
    ('udg_rope', 'R'),
    ('udg_win1', 'M'),
    ('udg_win2', 'N'),
    ('udg_clothes11', 'O'),
    ('udg_clothes12', 'P'),
    ('udg_clothes21', 'Q'),
    ('udg_clothes22', 'S'),
    ('udg_boot', 'U'),
    ('udg_boot2', 'Z')
]

# each y,x pair is a byte, then are gaps!!  15, jump == no paint. Change on Y means X goes zero.
ladrillos = (0, 0), (0, 1), (0, 10), (0, 5), (0, 1), (0, 13), (0, 1), \
            (2, 3), (2, 1), (2, 15), (2, 9), \
            (3, 1), (3, 1), (3, 1), (3, 12), (3, 1), (3, 13), (3, 1), \
            (4, 1), (4, 15), (4, 1), \
            (8, 8), (8, 9), (8, 7), (8, 1), \
            (11, 0), (11, 12), (11, 1), \
            (12, 0), (12, 1), (12, 7), (12, 15), (12, 2), \
            (13, 1), (13, 5), (13, 2), (13, 7), (13, 1), (13, 6), (13, 1), (13, 6)

for idx, v in enumerate(imgs):

    print("#define UDG_" + str(v[1]) + " " + str(128+(idx)))

coords = []
for i in ladrillos:
    coords.append("0x{:01x}{:01x}".format(i[0], i[1]))

print("const uint8_t coords [] = {" + ", ".join(coords) + "};")
print("// Then just use binary ops: `(a & 0xF0) >> 4` gives first number, `a & 0x0F` gives second")
