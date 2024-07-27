#include "ejercicios.h"

void generarNombreAleatorio(char* nombre)
{
    const char* nombres[] = {"Juan", "Maria", "Pedro", "Ana", "Luis", "Marta", "Jose", "Laura", "Carlos", "Lucia"};
    strcpy(nombre, nombres[rand() % 10]);
}

void generarApellidoAleatorio(char* apellido)
{
    const char* apellidos[] = {"Garcia", "Martinez", "Lopez", "Gonzalez", "Perez", "Rodriguez", "Sanchez", "Ramirez", "Cruz", "Fernandez"};
    strcpy(apellido, apellidos[rand() % 10]);
}

int generarArchivoLotePersonas(const char* nombreArch, const char* modoApertura)
{
    FILE* archPersonas;
    tPersona persona;
    int i;

    if ((archPersonas = fopen(nombreArch, modoApertura)) == NULL)
    {
        perror("Error al abrir el archivo");
        return FILE_ERR;
    }

    for (i = 0; i < CANT_PERSONAS; i ++)
    {
        persona.dni = rand() * 99; // DNI aleatorio de 8 dígitos
        generarNombreAleatorio(persona.nombre);
        generarApellidoAleatorio(persona.apellido);
        persona.edad = rand() % 100 + 1; // Edad aleatoria entre 0 y 99

//        mostrarPersonaPorConsola(&persona);
        fwrite(&persona, sizeof(tPersona), 1, archPersonas);
    }

    fclose(archPersonas);
    return OK;
}

void generarIndicePersona(void* indice, const void* regLeido, int nroReg)
{
    ((tIndice*)indice)->dni = ((tPersona*)regLeido)->dni;
    ((tIndice*)indice)->nroReg = nroReg;
}


void mostrarPersonaPorConsola(const void* persona)
{
    printf("%d|%d|%s|%s\n",
           ((tPersona*)persona)->dni,
           ((tPersona*)persona)->edad,
           ((tPersona*)persona)->nombre,
           ((tPersona*)persona)->apellido);
}

void mostrarDNIPersonaPorConsola(const void* persona)
{
    printf("%d",((tPersona*)persona)->dni);
}

void mostrarIndicePersona(const void* persona)
{
    printf("%d",((tIndice*)persona)->dni);
}
void mostrarIndicePersona2(const void* persona)
{
    printf("%d|%d\n",((tIndice*)persona)->dni, ((tIndice*)persona)->nroReg);
}
void mostrarIndicePersona3(void* arch, const void* nodo)
{
    fwrite(((tNodo*)nodo)->info, ((tNodo*)nodo)->tamInfo, 1, (FILE*)arch);
}

int cmpPersonas(const void* persona1, const void* persona2)
{
    return ((tPersona*)persona1)->dni - ((tPersona*)persona2)->dni;
}

int cmpIndPersonas(const void* persona1, const void* persona2)
{
    return ((tIndice*)persona1)->dni - ((tIndice*)persona2)->dni;
}

/// Tests
void testear_si_el_indice_se_condice_con_el_registro_correspondiente()
{
    FILE* archLeer;
    FILE* archIdx;

    tPersona persona;
    tIndice idx;

    if((archLeer = fopen("personas.dat", "rb")) == NULL ||
       (archIdx = fopen("personas.idx", "rb")) == NULL)
    {
        fclose(archIdx);
        return;
    }

    fread(&idx, sizeof(tIndice), 1, archIdx);
    while(!feof(archIdx))
    {
        fseek(archLeer, idx.nroReg * sizeof(tPersona), SEEK_SET);
        fread(&persona, sizeof(tPersona), 1, archLeer);
//        fseek(archLeer, -0L, SEEK_CUR);
        if(idx.dni == persona.dni)
            printf("TEST PASSED\t%10d = %10d\n", idx.dni, persona.dni);
        else
            printf("ERROR:\t\t%10d != %10d\n", idx.dni, persona.dni);
        fread(&idx, sizeof(tIndice), 1, archIdx);
    }

    fclose(archLeer);
    fclose(archIdx);
}
