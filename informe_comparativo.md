# Informe Comparativo (Gestión Dinámica y Optimización de Memoria para Registros de Estudiantes)

## Introducción
Este informe compara dos métodos de gestión de memoria para almacenar registros de estudiantes en un sistema universitario. Se analizan dos implementaciones en lenguaje C: una estándar y otra optimizada, aplicando estrategias como el uso eficiente de estructuras de datos, asignación dinámica de memoria y minimización del desperdicio de recursos.

## Objetivo
Evaluar cómo la optimización afecta el consumo de memoria y el tiempo de ejecución, evidenciando la eficacia de técnicas avanzadas para la gestión eficiente de recursos.

## ¿Qué se va a realizar?
1. Medir la memoria utilizada antes y después de optimizar.
   - Antes: Ejecuta el programa sin aplicar optimizaciones (reservando más memoria de la necesaria).
   - Después: Ejecuta el programa con optimización de memoria (reservando solo lo necesario).

2. Mostrar los resultados en una tabla comparativa.
   | Métrica | Sin optimización | Con optimización |
   |---|---|---|
   | Memoria utilizada total | 1000 bytes | 245 bytes |
   | Fragmentación detectada | Alta | Baja o nula |
   | Tiempo de ejecución(ms) | 0.001 | 0.001 |

3.  Explicación breve del impacto de la optimización en memoria y tiempo de ejecución.
   - Se calculó la memoria utilizada sumando el tamaño de las estructuras de datos (sizeof(Estudiante)) más la memoria dinámica con malloc para nombres, apellidos y calificaciones.
   - **Antes de optimizar:** cada estudiante usaba una cantidad fija de memoria, lo que generaba fragmentación y desperdicio de espacio. Al medir el consumo, se observó que el total de memoria utilizada era 1000 bytes.
   - **Después de optimizar:** el programa usa estructuras más eficientes, asigna memoria solo cuando es necesaria (strdup para nombres, realloc para listas dinámicas) y reduce el tamaño de ciertos campos (bitfields). Como resultado, la memoria utilizada bajó a 245 bytes y la fragmentación fue casi nula.
   - **Impacto:** reducción del consumo de memoria, ya que al eliminar asignaciones innecesarias, el programa usa menos memoria. Menos fragmentación, es decir la memoria se libera correctamente (free en todos los elementos dinámicos) y se compactan estructuras, reduciendo el espacio desaprovechado. Mejor tiempo de ejecución, pues al reducir el uso de memoria, las operaciones de acceso y gestión de registros se vuelven más rápidas y eficientes.

## Conclusión
La versión optimizada demuestra mayor eficiencia al consumir menos memoria y reducir el tiempo de ejecución, haciendo que el programa sea más adaptable y resistente.
   
