# Gestión del Conocimiento en las Organizaciones
## Sistemas de Recomendación basados en el Contenido

### Diego Rodríguez Pérez
### alu0101203980@ull.edu.es

## Descripción del Código Desarrollado

### 1 Lectura del fichero y almacenamiento
En esta primera fase se irá leyendo el fichero palabra a palabra y se irá almacenando en un vector de tuplas, las cuales contienen el término, el archivo al que pertenece, el índice y las veces que aparece en el archivo. Esto se desarrolla en la función **crearMatriz()**.

### 2 Cálculo del TF, IDF y TF-IDF
En esta segunda fase se irá leyendo el vector que contiene la información mencionada en el apartado 1. Entonces se usará las veces que ha apareciudo el término para calcular su **TF**, luego con este dato se calculará el **IDF** y por último haciendo uso de estos dos resultados se calculará el **TF-IDF**. Todos estos resuñtados se almacenarán en otro vector de tuplas. Esto se desarrolla en la función **calcularResultados()**.

### 3 Muestra de Resultados
En esta tercera fase se irá leyendo el vector de tuplas que contiene todos los resultados y se irán mostrando en forma de tabla. Esto se desarrolla en la función **mostrarTablas()**.

### 4 Normalización del TF
En esta cuarta fase se irá leyendo el vector de tuplas y se irá normalizando el **TF** de cada término utilizando la fórmula indicada en las diapositivas y se irá almacenando en otro vector de tuplas. Esto se desarrolla en la función **normalizarTF()**.

### 5 Cálculo de la longitud del vector
En esta quinta fase se irá leyendo vector de tuplas y se irá calculando la longitud del vector de cada arhivo. Esta información se almacenará en un vector de pares, los cuales contienen la longitud del vector y el archivo al que pertenece el propio vector. Esto se desarrolla en la funcióm **longitudVector()**.

### 5 Cálculo de la longitud del vector
En esta quinta fase se irá leyendo vector de tuplas y se irá calculando la longitud del vector de cada arhivo. Esta información se almacenará en un vector de pares, los cuales contienen la longitud del vector y el archivo al que pertenece el propio vector. Esto se desarrolla en la funcióm **longitudVector()**.

### 6 Cálculo de los valores necesarios para sacar la similitud
En esta sexta fase se irá leyendo el vector con los **TF** normalizados y el que contiene la longitud de los vectore. Entonces se creará otro vector que almacenará el término, el archivo añ que pertenece y el valor necesario para calcular la similitud. Esto se desarrolla en la funcióm **valoresCoseno()**.

### 7 Cálculo de la **Similitud Coseno**
En esta séptima y última fase se irá leyendo el vector con los valores necesarios para calcular la similaridad y se buscarán las palabras comunes entre los archivos y se calculará la similitud entre cada par de documentos. Esto se desarrolla en la funcióm **vectoresAuxiliares()**.

## Ejemplo de uso

### 1 Ejecución del ejecutable
Se ejecuta en la terminal el comando **./a**.

### 2 Selección del fichero
Se elige el fichero con el que se desea calcular los resultados.

### 3 Visualización de resultados
Se abre la Terminal y se observan los resultados que se muestran por pantalla
