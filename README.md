
Los amigos del instituto del cerebro nos pidieron que implementemos un intérprete del famoso lenguaje llamado Brainfuck, este lenguaje cuenta con la característica que tiene muy pocas instrucciones posibles (sólo 7) y tambien por tener un compilador o intérprete muy pequeño y fácil de implementar.

Un link útil para probar este lenguaje es este intérprete online.

Su tarea es implementar un intérprete de Brainfuck en el lenguaje C. El programa deberá ejecutarse de la siguiente forma:

    $ ./bf <ruta al archivo> 

Donde ruta al archivo es la ruta al archivo a interpretar. Por ejemplo: ./bf ejemplo.bf. En caso que no se indique ruta al archivo, deberá leerse de entrada estándar (similar a como hace el intérprete de Python).

Se brinda en el sitio de descargas un set (reducido) de archivos de prueba de ejemplo. La forma de ejecutar dichas pruebas es:

    $ ./pruebas.sh ruta/a/ejecutable/bf

Tener en cuenta que estas pruebas contemplan casos triviales, y algunos muy complejos. Para pruebas intermedias recomendamos implementar las suyas, pudiendo utilizar el intérprete provisto para confirmar resultados. Se pueden seguir agregando pruebas utilizando el mismo formato que las anteriores: tener un archivo “xx_in” que servirá de entrada al programa (instrucción ‘,’), otro “xx_script” que deberá tener el código a interpretar, otro “xx_out” que corresponderá con la salida esperada, y otro de “xx.test” que deberá contener la descripción de la prueba.
Observaciones

    Todos los caracteres diferentes a los definidos por el lenguaje deben ser ignorados.
    Se puede considerar que el archivo fuente entra todo en memoria, aunque recomendamos sólo almacenar lo necesario.
    Se debe validar la cantidad de argumentos pasados al programa, en caso de haber una cantidad inválida, escribir por salida de error (stderr): Error: Cantidad erronea de parametros (sin tildes).
    Se debe validar (en caso de indicarse) que se pueda leer el archivo pasado por parámetro. En caso de no ser posible escribir por salida de error (stderr): Error: archivo fuente inaccesible.
    Las impresiones realizadas por el programa deben realizarse a salida estándar (stdout).



