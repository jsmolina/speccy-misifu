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
            (7, 15), (7, 1), (7, 9), (7, 1), \
            (8, 8), (8, 9), (8, 7), (8, 1), \
            (11, 0), (11, 13), (11, 1), \
            (12, 0), (12, 1), (12, 7), (12, 15), (12, 2), \
            (13, 1), (13, 6), (13, 2), (13, 7), (13, 1), (13, 6), (13, 1), (13, 7)

suelo_coords = (0, 12), (0, 5), (0, 11), \
        (1, 0), (1, 5), (1, 8), (1, 6), (1, 4), (1, 7), \
        (2, 2), (2, 5), (2, 4), (2, 4), (2, 3), (2, 9)
#suelo_flags = hex(int('0100101010010110', 2))
suelo_flags = hex(int('110100110110010', 2))
for idx, v in enumerate(imgs):

    print("#define UDG_" + str(v[1]) + " " + str(128+(idx)))

coords = []
for i in ladrillos:
    coords.append("0x{:01x}{:01x}".format(i[0], i[1]))

print("const uint8_t coords [] = {" + ", ".join(coords) + "};")
print("#define TOTAL_COORDS {}".format(len(coords)))
print("// Then just use binary ops: `(a & 0xF0) >> 4` gives first number, `a & 0x0F` gives second")

coords_suelo = []
for i in suelo_coords:
    coords_suelo.append("0x{:01x}{:01x}".format(i[0], i[1]))

print("const uint8_t coords_suelo [] = {" + ", ".join(coords_suelo) + "};")
print("#define TOTAL_COORDS_SUELO {}".format(len(coords_suelo)))
print("const uint16_t suelo_flags = " + suelo_flags + ";")
print("// ((suelo_flags >> i) & 1)")

queso = ((0, 15),
         (2, 15),
         (15, 2),
         (15, 0), (3, 1),
         (15, 15),
         (1, 2), (3, 1),
         (15, 15),
         (3, 1), (3, 2),
         (15, 15),
         (1, 4), (1, 5),
         (15, 0), (2, 5), (5, 15),
         (3, 1), (2, 5), (15, 15),
         (2, 5), (3, 5), (15, 1), (3, 5), (5, 0))

queso_coords = []
for i in queso:
    queso_coords.append("0x{:01x}{:01x}".format(i[0], i[1]))

print("const uint8_t coords_queso [] = {" + ", ".join(queso_coords) + "};")
print("#define TOTAL_COORDS_QUESO {}".format(len(queso_coords)))



# para los 4 ratones
# pos0, pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8, pos9
holes = (3, 5), (11, 1),  (0, 1), (6, 6),  (8, 3), (12, 13),   (3, 2), (11, 8),\
        (6, 1), (8, 9), (12, 5)

holes_coords = []
for i in holes:
    holes_coords.append("0x{:01x}{:01x}".format(i[0], i[1]))
print("const uint8_t coords_holes [] = {" + ", ".join(holes_coords) + "};")
print("#define TOTAL_COORDS_HOLES {}".format(len(holes_coords)))

#((1,2,3), repeticiones) tipos de udg, al llegar a 10 saltar fila
# 1 = udg_libros_01, udg_libros_02
# 2 = udg_libro_inclinado_01, udg_libro_inclinado_02
# 3 = udg_estanteria_top_vacio, vacio

# por defecto pinto completo de udg_libros_01, udg_libros_02


agujeros = (
    (1, 7), (9, 15), # 1
    (15,  # 2
     0), (2, 3), (6, 7), (8, 15),  # 3
    (3, 8),  # 4
    (15, 2), (3, 4), (5, 9),  # 5
    (15, 2), (5, 15),  # 6
    (1, 3), (4, 5), (7, 8), # 7
    (15, 3), (7, 8), # 8
    (15, 0), (2, 6), (9, 15), # 9
    (2, 6), (5, 6), # 10
    (15, 2), (4, 5), (6, 8), # 11
    (15, 4), (8, 15), # 12
    (0, 2), (3, 6), (7, 9), # 13
    (15, 2), (7, 15)  # 14
)
# solo pares, fila, col
inclinados = ((0, 5), (4, 1), (4, 7), (8, 5), (10, 1), (12, 5))


empty_coords = []
for i in agujeros:
    empty_coords.append("0x{:01x}{:01x}".format(i[0], i[1]))
print("const uint8_t empty_holes [] = {" + ", ".join(empty_coords) + "};")
print("#define TOTAL_EMPTY_HOLES {}".format(len(empty_coords)))

italic_coords = []
for i in inclinados:
    italic_coords.append("0x{:01x}{:01x}".format(i[0], i[1]))
print("const uint8_t italic [] = {" + ", ".join(italic_coords) + "};")
print("#define TOTAL_ITALIC_HOLES {}".format(len(italic_coords)))

perros = (
    (4, 2), (1, 5), (5, 5), (3, 2), (0, 4), (4, 3), (4, 3), (2, 3)
)

perros_coords = []
for i in perros:
    perros_coords.append("0x{:01x}{:01x}".format(i[0], i[1]))

print("const uint8_t perros_coords [] = {" + ", ".join(perros_coords) + "};")
print("#define TOTAL_PERROS {}".format(len(perros_coords)))
