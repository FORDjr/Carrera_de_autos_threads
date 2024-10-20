# Carrera de autos usando hilos
### Diego Pozas y Luis Lagunas

El proyecto utiliza threads para simular avances y distancias en “una carrera de autos”. Cada auto tiene su propio hilo y su avance se calcula de manera aleatoria entre 1 a 10 mts hasta finalizar la distancia indicada por el usuario.

## Requerimientos

- A cada auto se le asigna un nombre con su hilo respectivo (Auto0, Auto1, Auto2 …)
- Cada auto tiene su simulador de velocidad, usando tiempos de espera.
- El programa muestra de color verde los ganadores a tiempo real.
- Los autos avanzan de 1 a 10 metros en cada iteración.
- Cada avance se muestra a tiempo real con su respectivo auto
- El ganador y el orden de llegada se muestran al final de la carrera.

## Requisitos

- Compilador C++ con soporte para C++11 o superior.
  
### Compilación en Linux/MacOS (con Makefile)
Con Linux puedes compilar el programa utilizando el `Makefile` incluido. 
```bash
make
```

## Uso del programa
Para ejecutar el simulador, debes proporcionar dos argumentos.
<Distancia en metros> <Número de autos>
Ejemplo:
```bash
./carrera 100 3
```
Salida esperada (el progreso variará por la naturaleza aleatoria del programa):
```diff
Distancia total carrera: 100 metros
----------------------------------------------
Auto0 avanza 5 metros (total: 5 metros)
Auto1 avanza 5 metros (total: 5 metros)
Auto2 avanza 3 metros (total: 3 metros)
...
Auto1 avanza 10 metros (total: 95 metros)
Auto2 avanza 2 metros (total: 77 metros)
+Auto0 avanza 5 metros y termina la carrera en el lugar 1!!!
Auto1 avanza 1 metros (total: 96 metros)
Auto2 avanza 7 metros (total: 84 metros)
+Auto1 avanza 6 metros y termina la carrera en el lugar 2!!!
Auto2 avanza 10 metros (total: 94 metros)
Auto2 avanza 5 metros (total: 99 metros)
+Auto2 avanza 8 metros y termina la carrera en el lugar 3!!!


Lugar   Auto
------------------
1       Auto0
2       Auto1
3       Auto2

```


