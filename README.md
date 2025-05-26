
# Prediccion de Admision Universitaria

**Autores: Lorenzo Ramirez Calderon, Nicolas Sanchez Luengas, Lucas Rincon Mican.**

Proyecto Final para la clase de Programación Avanzada, Pontificia Universidad Javeriana, Bogotá.


Pipeline ETL de extracción, transformación, y carga de una base de datos de 400 estudiantes para análisis y posterior creación de un modelo de regresión lineal que prediga si el estudiante fue admitido en la universidad con base a sus estadísticas. El proceso del Pipeline fue realizado modularmente a través de C++.
La regresión lineal de prediccion y la interfaz gráfica para ingreso de datos fueron hechas en Java.


## Estructura

```
cpp/
├── Pipeline.h               # Declaración de funciones (readCSV, Head, Info, Describe, Correlation, saveAnalysisToTxt, 
|                              convertTableToStudents, writeStudentsBinary)
├── AnalysisModule.cpp       # Implementación del módulo de análisis
├── ConversionModule.cpp     # Implementación de conversión a estructuras, escritura y lectura del binario
├── DataTransformer.cpp      # Implementación de la lectura del CSV y transformación a tabla
└── pipeline.cpp             # Main que ejecuta todo el pipline a traves de un  menú interactivo
```

```
java/
├── Pipeline.h               # Declaración de funciones (readCSV, Head, Info, Describe, Correlation, saveAnalysisToTxt, 
|                              convertTableToStudents, writeStudentsBinary)
├── AnalysisModule.cpp       # Implementación del módulo de análisis
├── ConversionModule.cpp     # Implementación de conversión a estructuras, escritura y lectura del binario
├── DataTransformer.cpp      # Implementación de la lectura del CSV y transformación a tabla
└── pipeline.cpp             # Main que ejecuta todo el pipline a traves de un  menú interactivo
```
Despues de haber sido ejecutado el pipeline la carpeta data tendra la siguiente estructura
```
data/
├── Admission_Predict.csv          # CSV extraido 
├── Admission_Predict_new.bin      # Archivo binario convertido del csv con la informacion de cada estudiante
├── modelo_parametros.json         # Parametros de la regresion lineal con su intercepto y coeficientes
└── transformacion_resultados.txt  # Resultados del analisis del csv conteniendo Info, Describe y Correlation
```



## Implementacion C++

1. **Apertura y transformación:**
- Se abre el csv y utilizando la funcion readCSV se obtiene la informacion de filas y columnas ademas de transformar el csv a una matriz.

2. **Menú Interactivo de Análisis:**
- Se muestra el siguiente menu:
    1. Líneas específicas (head, según la cantidad solicitada).
    2. Información básica del CSV (Numero de filas y columnas, y para cada columna su nombre, tipo de dato y cantidad de filas no  nulas).
    3. Estadísticas descriptivas (Promedio, desviacion estandar, valor minimo y maximo).
    4. Matriz de correlación.
    5. Guardar analisis y base de datos en archivos.

- Los resultados se visualizan en la terminal.


3. **Guardar Información**
    - Se guardan todas las estadisticas del menu en un archivo txt.
    - Se convierte la matriz a un arreglo de estructuras.
    - Se crea archivo binario y se transforma el arreglo de estructuras a binario.
    - Se comprueba la conversion imprimiendo el head y tail del archivo.

4. **Finalizacion del programa**



## Implementacion JAVA


## Compilacion y Ejecucion

Si estas en una terminal diferente a Unix/Linux dirigete al *AnalysisModule.cpp* y descomenta la linea 306 freopen("CON", "w", stdout); y comenta la 307.

```
    freopen("CON", "w", stdout);
    //freopen("/dev/tty", "w", stdout);
```

Dirigirse al directorio raiz del proyecto

```bash
  cd proyecto
```
Compilar el pipeline utilizando:

```bash
  g++ cpp/AnalysisModule.cpp cpp/ConversionModule.cpp cpp/DataTransformer.cpp cpp/pipeline.cpp -o Pipeline
```

Finalmente, ejecuta la siguiente linea y sigue las instrucciones en pantalla, presionando enter al digitar informacion:


```bash
  ./Pipeline
```