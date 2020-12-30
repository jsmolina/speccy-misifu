import sys

imgs = [
    ('j_ladrillos', '$'),
    ('queso_textura', 144),
    ('j_piedras', '%'),
    ('udg_valla2', 'V'),
    ('udg_valla1', 'W'),
    ('udg_valla3', 'X'),
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

for idx, v in enumerate(imgs):

    print("#define UDG_" + str(v[1]) + " " + str(128+(idx)))
