---
title: "TP1: Sudoku Remoto"
author: Federico del Mazo - 100029
date: |
  | Facultad de Ingeniería, Universidad de Buenos Aires
  | [75.42] Taller de Programación
  | 
  | 10 de septiembre de 2019
---

En el presente se muestra un tp de un sudoku..

## Esqueleto general

[describir sudoku y network por separado, decir que la conexion tiene que ser minima y que esto ayuda a que eventualmente se pueda, por ejemplo, cambiar de juego, o, por ejemplo, pedirle a otro que se encargue de las comuniaciones. Tambien, se puede jugar al sudoku localmente]
```c
[2 diagramas de clases]
```
notar que el server nunca conoce al socket
que el cliente nunca sabe que hizo el server con su comando, solo imprime lo que recibe... etc
[incluso, cada modulo podria haber sido su propio directorio, y el proyecto funcionaria igual (asi fue el desarrollo, pero la entrega especifica que todos los fuente esten en el mismo root)]
[filetree en desarrollo]
## Comunicación

diagramas desde el punto de vista de network/client
avisar que considero mal que el cliente sepa de comportamiento
de recibir cosas complicadas, el cliente tendria que tener un dispatcher propio, pero en este caso es siempre imprimir lo que recibe

## Problemas particulares

### sudoku

* representacion
* verificacion secciones

### network

## aclaraciones del alumno