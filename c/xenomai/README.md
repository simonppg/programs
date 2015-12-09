# Tareas xenomai

## Copilacion
- Entra a la carpeta del proyecto
$ cd xenomai
- Compila
$ make
- ejecuta el programa
$ bin/program

prog
 |
 +-[include]
 |  +-[mod1]
 |  |   |
 |  |   +-a_mod1.h
 |  |   +-b_mod1.h
 |  |
 |  +-[mod2]
 |  |   +-a_mod2.h
 |  |   +-b_mod2.h
 |  |
 |  +-app1.h
 |  +-app2.h
 |  +-header1.h
 |  +-header1.h
 |
 +-[src]
 |  +-[mod1]
 |  |   |
 |  |   +-a_mod1.cpp
 |  |   +-b_mod1.cpp
 |  |
 |  +-[mod2]
 |  |   +-a_mod2.cpp
 |  |   +-b_mod2.cpp
 |  +-app1.cpp
 |  +-app2.cpp
 |
 +-build
