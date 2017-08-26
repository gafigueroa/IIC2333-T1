# README

### Autores
- Juan Cortes (1363772J)
- Guillermo Figueroa (13634526)

### Decisiones de diseño
- La cola de prioridades (queue) está modelada con un min heap
- Al agregar un elemento al min Heap se calcula la prioridad de sus nodos
- La función que calcula la prioridad de los nodos se escoge al momento de crear el heap, segun el tipo de cola que se pide (Ver tipos en la documentacion)
- La decisión de realizar un min heap comenzó en la base de que una menor prioridad era mejor (1 mejor que 43), pero luego de preguntar
supimos que más alta es mejor, simplemente se almacena 64 - priority para seguir utilizando el min heap


### Supuestos adicionales
- Cambiar de estado corresponde a un tick del scheduler
- Imprimimos IDLE en caso de que no haya nada ejecutandose


### Información adicional
* Se adjunta además una documentación del código, esta se encuentra en la carpeta docs, basta con abrir cualquier archivo .html y luego navegar en ella con su navegador web favorito	