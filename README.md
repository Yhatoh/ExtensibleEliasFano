# Código implementación de esquemas 2 y 4

## Código

El código implementado es el creado por Abdel Sandoval en su repositorio [ExtensibleEliasFano](https://github.com/apdelsm/ExtensibleEliasFano)

Se agrego a la carpeta *include* los archivos scheme2.hpp y scheme4.hpp, estos contienen las implementación de los esquemas hablados en el trabajo Adapative Succinctness de Diego Arroyuelo y Rajeev Raman.

Además, en la carpeta *src* el archivo main.cpp contiene el código para realizar los testing de los esquemas junto al sd_vector.

## Tests

En la carpeta *tests* se encuentran los 3 códigos usados para generados los test hablados en el trabajo. Y los test generados se encuentran en *test/test*, donde luego cada carpeta se separa por el grupo de test correspondiente.


## Complilación y ejecución

### Compilar

Para compilar, debe situarse a la altura del makefile y hacer ```make``` esto le generá el archivo compilado en la carpeta *bin*.

### Ejecución

Para ejecutarlo, debe hacer el siguiente comando ```./bin/test``` donde luego se le pedirá el input en cuestión que corresponde al siguiente formato:

```
Tamaño del vector de bits
el vector de bits
```

Por ejemplo:

```
10
0100111010
```

Si quiere ejecutar todos los test generados por los archivos .py de la carpeta *tests*, puede usar el siguiente comando:

```
./executor
```

Este le ejecutará todos los test y serán almacenados en un archivo .txt con el mismo nombre, en la carpeta *result/tests/test*, separados por su respectivo grupo de test.