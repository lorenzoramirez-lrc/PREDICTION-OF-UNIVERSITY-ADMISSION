
# Predicción de Admisión Universitaria

**Autores: Lorenzo Ramírez Calderón, Nicolás Sánchez Luengas, Lucas Rincón Mican.**

Proyecto Final para la clase de Programación Avanzada, Pontificia Universidad Javeriana, Bogotá.

Pipeline ETL de extracción, transformación, y carga de una base de datos de 400 estudiantes para análisis y posterior creación de un modelo de regresión lineal que prediga si el estudiante fue admitido en la universidad con base a sus estadísticas. El proceso del Pipeline fue realizado modularmente a través de C++.
La regresión lineal de predicción y la interfaz gráfica para ingreso de datos fueron hechas en Java.


## Estructura

```
cpp/
├── Pipeline.h               # Declaración de funciones (readCSV, Head, Info, Describe, Correlation, saveAnalysisToTxt, 
|                              convertTableToStudents, writeStudentsBinary)
├── AnalysisModule.cpp       # Implementación del módulo de análisis
├── ConversionModule.cpp     # Implementación de conversión a estructuras, escritura y lectura del binario
├── DataTransformer.cpp      # Implementación de la lectura del CSV y transformación a tabla
└── pipeline.cpp             # Main que ejecuta todo el pipeline a traves de un  menú interactivo
```

```
java/
├── Aplicante.java               # Clase que representa al Aplicante.
├── FormularioAplicante.java     # Clase que representa a la interfaz gráfica integrando las otras dos clases.
├── ModeloRegresion.java         # Clase que representa al ModeloRegresion. 
└── Main.java                    # Main que ejecuta la interfaz gráfica.
```
Después de haber sido ejecutado el pipeline la carpeta data tendrá la siguiente estructura:
```
data/
├── Admission_Predict.csv          # CSV extraído
├── Admission_Predict_new.bin      # Archivo binario convertido del CSV con la información de cada estudiante
├── modelo_parametros.json         # Parámetros de la regresión lineal con su intercepto y coeficientes
├── admitido.jpg                   # Imagen que aparece en la interfaz gráfica cuando el estudiante fue admitido
├── no_admitido.png                # Imagen que aparece en la interfaz gráfica cuando el estudiante no fue admitido
└── transformacion_resultados.txt  # Resultados del análisis del CSV conteniendo Info, Describe y Correlation
```



## Implementación C++

1. **Apertura y transformación:**
- Se abre el CSV y utilizando la función readCSV se obtiene la información de filas y columnas además de transformar el CSV a una matriz.

2. **Menú Interactivo de Análisis:**
- Se muestra el siguiente menú:
    1. Líneas específicas (head, según la cantidad solicitada).
    2. Información básica del CSV (Número de filas y columnas, y para cada columna su nombre, tipo de dato y cantidad de filas no nulas).
    3. Estadísticas descriptivas (Promedio, desviación estándar, valor mínimo y máximo).
    4. Matriz de correlación.
    5. Guardar análisis y base de datos en archivos.

- Los resultados se visualizan en la terminal.

3. **Guardar Información**
- Se guardan todas las estadísticas del menú en un archivo TXT.
- Se convierte la matriz a un arreglo de estructuras.
- Se crea archivo binario y se transforma el arreglo de estructuras a binario.
- Se comprueba la conversión imprimiendo el head y tail del archivo.

4. **Finalización del programa**


## Implementación JAVA

- **Aplicante.java**
    - Atributos: Nombre, GreScore, ToeflScore, UniversityRating, Sop, Lor, CGPA, Research.
    - Metodos: Constructor, Getters, Setters
- **ModeloRegresion.java**
    - Atributos: Intercepto, Hashmap de coeficientes(Categoría, Valor)
    - Métodos:
        - Constructor: Carga modelo desde un archivo JSON utilizando operaciones de texto para encontrar él interceptó y utilizar los coeficientes como claves de un Hashmap
        - Predicción: Recibe un objeto Aplicante y aplica la regresión lineal a sus atributos.
        - Admitido: Utiliza el método predicción para compararlo con 0.8 y regresar un booleano que indica si el aplicante fue admitido o no.
- **FormularioAplicante.java**
    - Atributos: Campos de texto para cada atributo de la clase Aplicante, etiquetas para título e imágenes, botón de enviar, y un objeto de la clase ModeloRegresion.
    - Métodos:
        - Constructor:
            1. Configura y añade todos los campos de texto, etiquetas y botones, además de instanciar el modelo de regresión.
            2. Añade al botón un controlador de acciones, que toma las respuestas de los campos de texto e instancia un Aplicante.
            3. Se utiliza el método Admitido y con base en esa respuesta se diseñan dos respuestas diferentes que muestran si fue admitido o no acompañado de una imagen y su puntaje.
            4. Se muestran los resultados
            5. Se maneja una excepción que verifica que todos los campos estén llenos y con números(Excepto Nombre).
- **Main.java**
    - Instancia el objeto de FormularioAplicante y lo hace visible.

## Compilación y Ejecución

Si estás en una terminal diferente a Unix/Linux dirígete al *AnalysisModule.cpp* y descomenta la línea 306 freopen("CON", "w", stdout); y comenta la 307.

```c++
    freopen("CON", "w", stdout);
    //freopen("/dev/tty", "w", stdout);
```

Dirigirse al directorio raíz del proyecto

```bash
    cd proyecto
```
Compilar el pipeline utilizando:

```bash
    g++ cpp/AnalysisModule.cpp cpp/ConversionModule.cpp cpp/DataTransformer.cpp cpp/pipeline.cpp -o Pipeline
```

Finalmente, ejecuta la siguiente línea y sigue las instrucciones en pantalla, presionando enter al digitar información:

```bash
./Pipeline
```

**Después del análisis de los datos para poder visualizar la interfaz se siguen los siguientes pasos:**

Dirigirse al directorio raíz del proyecto

```bash
cd proyecto
```

Compilar la interfaz utilizando:

```bash
javac java/Aplicante.java java/ModeloRegresion.java java/FormularioAplicante.java java/Main.java
```

Por último, se ejecuta la siguiente línea, se llenan los campos de texto y se oprime el botón "Evaluar Aplicación".

```bash
java -cp java Main
```
