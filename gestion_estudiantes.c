#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de la estructura del estudiante
typedef struct {
    char *nombre;
    char *apellido;
    unsigned int edad : 7;  // Uso de bitfields para optimizar
    unsigned int id;
    float *calificaciones;
    int num_materias;
} Estudiante;

// Variables globales
Estudiante **lista_estudiantes = NULL;
int num_estudiantes = 0;
size_t memoria_utilizada = 0;

// Función para agregar un estudiante
void agregar_estudiante(const char *nombre, const char *apellido, unsigned int edad, unsigned int id, float *calificaciones, int num_materias) {
    lista_estudiantes = realloc(lista_estudiantes, (num_estudiantes + 1) * sizeof(Estudiante*));
    Estudiante *nuevo = (Estudiante*) malloc(sizeof(Estudiante));
    
    nuevo->nombre = strdup(nombre);
    nuevo->apellido = strdup(apellido);
    nuevo->edad = edad;
    nuevo->id = id;
    nuevo->num_materias = num_materias;
    nuevo->calificaciones = (float*) malloc(num_materias * sizeof(float));
    memcpy(nuevo->calificaciones, calificaciones, num_materias * sizeof(float));
    
    lista_estudiantes[num_estudiantes++] = nuevo;
    memoria_utilizada += sizeof(Estudiante) + strlen(nombre) + 1 + strlen(apellido) + 1 + num_materias * sizeof(float);
    
    printf("Estudiante \"%s %s\" agregado correctamente. Memoria utilizada: %zu bytes.\n", nombre, apellido, memoria_utilizada);
}

// Función para eliminar un estudiante por ID
void eliminar_estudiante(unsigned int id) {
    for (int i = 0; i < num_estudiantes; i++) {
        if (lista_estudiantes[i]->id == id) {
            size_t memoria_liberada = sizeof(Estudiante) + strlen(lista_estudiantes[i]->nombre) + 1 + strlen(lista_estudiantes[i]->apellido) + 1 + lista_estudiantes[i]->num_materias * sizeof(float);
            
            free(lista_estudiantes[i]->nombre);
            free(lista_estudiantes[i]->apellido);
            free(lista_estudiantes[i]->calificaciones);
            free(lista_estudiantes[i]);
            
            // Compactación de la lista
            for (int j = i; j < num_estudiantes - 1; j++) {
                lista_estudiantes[j] = lista_estudiantes[j + 1];
            }
            num_estudiantes--;
            lista_estudiantes = realloc(lista_estudiantes, num_estudiantes * sizeof(Estudiante*));
            memoria_utilizada -= memoria_liberada;
            
            printf("Estudiante con ID %u eliminado correctamente. Memoria liberada: %zu bytes.\n", id, memoria_liberada);
            return;
        }
    }
    printf("Estudiante con ID %u no encontrado.\n", id);
}

// Función para actualizar estudiante
void actualizar_estudiante(unsigned int id, const char *nuevo_nombre, const char *nuevo_apellido, unsigned int nueva_edad) {
    for (int i = 0; i < num_estudiantes; i++) {
        if (lista_estudiantes[i]->id == id) {
            memoria_utilizada -= strlen(lista_estudiantes[i]->nombre) + 1 + strlen(lista_estudiantes[i]->apellido) + 1;
            free(lista_estudiantes[i]->nombre);
            free(lista_estudiantes[i]->apellido);
            
            lista_estudiantes[i]->nombre = strdup(nuevo_nombre);
            lista_estudiantes[i]->apellido = strdup(nuevo_apellido);
            lista_estudiantes[i]->edad = nueva_edad;
            
            memoria_utilizada += strlen(nuevo_nombre) + 1 + strlen(nuevo_apellido) + 1;
            printf("Estudiante con ID %u actualizado correctamente. Memoria utilizada: %zu bytes.\n", id, memoria_utilizada);
            return;
        }
    }
    printf("Estudiante con ID %u no encontrado.\n", id);
}

// Función para liberar toda la memoria al final
void liberar_memoria() {
    for (int i = 0; i < num_estudiantes; i++) {
        free(lista_estudiantes[i]->nombre);
        free(lista_estudiantes[i]->apellido);
        free(lista_estudiantes[i]->calificaciones);
        free(lista_estudiantes[i]);
    }
    free(lista_estudiantes);
    num_estudiantes = 0;
    memoria_utilizada = 0;
}

// Prueba del sistema
typedef struct {
    unsigned int edad : 7;
} BitfieldTest;

int main() {
    float calificaciones1[] = {4.5, 3.8, 4.0};
    agregar_estudiante("Laura", "Vargas", 18, 12345678, calificaciones1, 3);
    
    eliminar_estudiante(12345678);
    
    liberar_memoria();
    return 0;
}
