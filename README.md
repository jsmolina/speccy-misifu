# speccy-misifu
Misifu la gatita (WIP) - zxspectrum

Development in progress
http://zx-dev-mia-remakes.proboards.com/thread/12/misifu-gatita-alley-cat-demake

# Story
```
La pérrada ha raptado a Fred, y sólo lo liberará si destrozas las habitaciones del edificio del 
propietario del banco que ha deshauciado a sus amigos. ¿Cómo lo harás? Como ya sabes, 
¡a lo gatuno, misifu!
```

```
The dogad has kidnapped Fred, and they will only free him if you destroy the rooms of a building. 
This building belongs to the bank that evicted 'dogad' friends. How do you do it? 
Just be a cat, misifu!!
```
Controls: OPQA SPACE

# Levels

EN
- Alley. Try to jump inside a window, but be aware of the dog, he will try to bite you and take a live.
- Cheese. Try to eat ALL the mousies. Some holes are connected if you press space, just discover them
- Fishtank. Enter inside fishtank jumping inside it. Inside fishtank: eat all fishes but be aware of eels and oxygen.
- Bookself. Destroy the vases in the bookself, but be aware of the spider, and the dog!
- Bird. Throw the birdcage, eat the bird!
- Sleeping dogs. Press space when on drinkers, be aware of touching them three times, or you'll awake them... and that's not ending so well.
- Hearts. That's the last level and thus the most difficult. Reach the topmost without falling and you'll rescue Fred and see the ending. 
Game will restart from Alley after hearts.

ES
- Alley. intenta saltar en una ventana, pero cuidado con el perro ya que intentará morderte y quitarte una vida!
- Queso. Intenta comerte todos los ratones. Algunos agujeros están conectados si pulsas espacio, tendrás que descubrir cuáles.
- Pecera. Entra en la pecera saltando sobre ella desde más arriba. Dentro de la pecera: cómete todos los peces, pero cuidado con las anguilas electricas y el oxígeno.
- Estantería. Rompe los jarrones de la estanteria, pero cuidado con la araña... y como siempre, el perro!
- Jaula/pajaro. Tira la jaula, cómete el pájaro y ojo con el perro.
- Perros durmiendo. Presiona espacio en los bebederos, pero cuidado con tocar los perros tres veces, o los levantarás... y ya sabemos que eso no acaba bien.
- Corazones. Este es el último nivel, y el más dificil. Consigue llegar a lo más arriba y rescatarás a Fred, para ver el final.
El juego empezará de nuevo en el callejón.

PT
Controles: OPQA / Kempston (0 = pausa)

- Ruela. Tenta pular por uma janela, mas cuidado com o cão que tentará tirar-te a vida!
- Queijo. Tenta comer todos os ratos. Alguns buracos estão conectados entre si, terás que descobrir quais.
- Aquário. Entra no aquário, saltando de cima. Dentro do aquário: come todos os peixes, mas cuidado com as enguias elétricas e com o oxigénio.
- Estante. Quebra os jarros da estante, mas cuidado com a aranha... E como sempre, com o cão!
- Gaiola/Pássaro. Quebra a gaiola, come o pássaro e cuidado com o cão.
- Cães a dormir. Pressiona a tecla de “espaço” nos bebedouros, mas cuidado para não tocares os cães três vezes ou irás acordá-los... E já sabemos que isso não termina bem.
- Corações. Este é o último nível e o mais difícil. Tenta chegar o mais alto possível e salvar Fred para ver o final. O jogo começa então novamente na ruela.

Apesar de se abrirem diferentes janelas... Só após terminares este nível, poderás passar ao próximo. 

RU
Догад похитил Фреда, и они освободят его, только если вы уничтожите комнаты здания. Это здание принадлежит банку, который выселит друзей Догада. Как ты сделаешь это? Просто будь кошкой, Мисифу !!

Управление: OPQA SPACE / Kempston (0 = пауза)

– Аллея. Попробуйте прыгнуть в окно, но будьте внимательны с собакой, она постарается вас укусить и съесть.
– Сыр. Попробуйте съесть всех мышей. Некоторые отверстия связаны, если вы нажмете пробел, то откроете их.
– Аквариум. Войдите в аквариум, прыгнув в него. Внутри аквариума ешьте всех рыб, но помните о угрях и кислороде.
– Книжная полка. Уничтожьте вазы на книжной полке, но будьте осторожны с пауком и собакой!
– Птица. Сбрось птичью клетку и съешь птицу!
– Спящие собаки. Нажимайте пробел, когда стоите на поилках, будьте внимательны, касаясь их. Если ты коснёшься их трижды, то разбудешь их … и это не так хорошо заканчивается.
– Сердца. Это последний уровень и, следовательно, самый сложный. Доберитесь до самого верха, не упав, и вы спасете Фреда и увидите конец.
Игра перезапустится с Аллеи после комнаты с сердцами.

Вы не сможете получить доступ к следующему уровню, пока не закончите текущий, неважно, в какое окно вы вошли.

# Building
You'll need z88dk, so you could download it from here:
http://nightly.z88dk.org/
(tested on v13056-e8264f0-20181009)

Just execute :
`$ make` 

# Rebuilding sprites
Requires:
https://github.com/jsmolina/png2sp1sprite

See the Makefile as it contains udg and sprites lines.



Contributions/suggestions are more than welcome!

![Image of Misifu](https://user-images.githubusercontent.com/447481/50655530-c5d09800-0f90-11e9-8c1a-0f209cd2cd70.png)


# Collaborators
* alvin, first for being author of the GREAT z88dk, and second for helping me with moving AY to bank 6.
* ER on the graphic material.
* nq for ingame music.
* beykersoft for intro music.
* Marcelo Nunes for the portuguese translation of instructions.

# Special Thanks to
* Matthew Logue helping with some testing.
* Ivan Sánchez, motivation.
* Alexey, helping on very good ideas.
* Dario, who helped with feedback.

# Dedicated to
Clàudia :)

# Why it is not Fred again?
First, the original, GREAT AND ORIGINAL game Alley Cat is what it is, and I have to give it a respect. 
Second, nowadays my daughter asks me why most of the game heroes are 'males'.
Third, because `misifu` is a very affectionate way of calling a cat in Spain, my grandma did it so often.

# Appearances on media
Indieretronews:
http://www.indieretronews.com/2019/01/alley-cat-ataridos-cat-classic-as-128k.html

Some youtube videos that game appeared:

Modern ZX-Retro Gaming (first walkthrough!)
www.youtube.com/watch?v=2TCfAb7khP4&app=desktop

Arnau Jess
www.youtube.com/watch?v=JFjiWd7ziHM

Javi Ortiz
youtu.be/iBZ9AfL0jOo?t=161

Game running on a real +2A (mine)
www.youtube.com/watch?v=v-mvxf3EnuI

