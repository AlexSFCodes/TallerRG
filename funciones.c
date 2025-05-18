#include <stdio.h>
#include <string.h>
#include "funciones.h"
void ProduccionProducto(char productos[MaximoProducto][30], int Recursos[MaximoProducto][MaximoComponente],
                        char NRecursos[MaximoComponente][30], int Cantidad_Recursos[MaximoComponente],
                        int countproductos, int countrecursos) {
    
    if (countproductos == 0) {
        printf("No hay productos para producir.\n");
        return;
    }

    printf("Que desea producir?\n");
    for (int i = 0; i < countproductos; i++) {
        printf("%i. %s\n", i + 1, productos[i]);
    }

    int eleccion = -1, val = 0;
    do {
        printf("Ingrese el numero del producto >> ");
        val = scanf("%i", &eleccion);
        if (val != 1) {
            printf("Entrada invalida. Intente de nuevo.\n");
            while (getchar() != '\n');
        } else if (eleccion < 1 || eleccion > countproductos) {
            printf("Producto invalido. Intente de nuevo.\n");
        }
    } while (val != 1 || eleccion < 1 || eleccion > countproductos);
    eleccion--;

    int unidades = 0, tiempos = 0;

    do {
        printf("Cuantas unidades de %s desea producir? >> ", productos[eleccion]);
        val = scanf("%i", &unidades);
        if (val != 1) {
            printf("Entrada invalida. Intente de nuevo.\n");
            while (getchar() != '\n');
        } else if (unidades <= 0) {
            printf("La cantidad debe ser mayor que cero. Intente de nuevo.\n");
        }
    } while (val != 1 || unidades <= 0);

    do {
        printf("En cuanto tiempo lo quiere producir? >> ");
        val = scanf("%i", &tiempos);
        if (val != 1) {
            printf("Entrada invalida. Intente de nuevo.\n");
            while (getchar() != '\n');
        } else if (tiempos <= 0) {
            printf("El tiempo debe ser mayor que cero. Intente de nuevo.\n");
        }
    } while (val != 1 || tiempos <= 0);

    int tiempo_necesario = Recursos[eleccion][0] * unidades;
    if (tiempos < tiempo_necesario) {
        printf("No se puede realizar en ese tiempo\n");
        return;
    }

    int sePuede = 1;
    for (int j = 1; j < countrecursos; j++) {
        int necesarios = Recursos[eleccion][j] * unidades;
        if (Cantidad_Recursos[j] < necesarios) {
            printf("Faltan recursos: %s\n", NRecursos[j]);
            sePuede = 0;
        }
    }

    if (sePuede) {
        for (int j = 0; j < countrecursos; j++) {
            Cantidad_Recursos[j] -= Recursos[eleccion][j] * unidades;
        }
        printf("Se produjeron %i unidades de %s\n", unidades, productos[eleccion]);
    } else {
        printf("No se puede producir por falta de recursos.\n");
    }
}

void menu() {
    printf("\n--- MENU ---\n");
    printf("1. Crear un producto\n");
    printf("2. Ver productos\n");
    printf("3. Anadir/Editar productos o componentes\n");
    printf("4. Ver recursos\n");
    printf("5. Reabastecer stock\n");
    printf("6. Producir productos\n");
    printf("7. Salir\n>> ");
}

void submenu() {
    printf("\n-- Submenu: Productos y componentes --\n");
    printf("1. Anadir componente\n");
    printf("2. Editar producto\n");
    printf("3. Eliminar producto\n");
    printf("4. Regresar\n>> ");
}

int valopc() {
    int opc, val;
    val = scanf("%i", &opc);
    while (val != 1 || opc < 1 || opc > 7) {
        printf("Entrada invalida. Intenta de nuevo:\n");
        while (getchar() != '\n');
        val = scanf("%i", &opc);
    }
    return opc;
}

void Crearproducto(int Recursos[MaximoProducto][MaximoComponente], char NRecursos[MaximoComponente][30], char productos[MaximoProducto][30], int count, int countrecursos) {
    printf("Ingrese el nombre del producto:\n");
    while (getchar() != '\n');
    fgets(productos[count], 30, stdin);
    int len = strlen(productos[count]);
    if (productos[count][len - 1] == '\n') productos[count][len - 1] = '\0';

    for (int i = 0; i < countrecursos; i++) {
        int val;
        do {
            printf("Cantidad de %s necesaria >> ", NRecursos[i]);
            val = scanf("%d", &Recursos[count][i]);
            if (val != 1 || Recursos[count][i] < 0) {
                printf("Entrada invalida, debe ser un numero entero positivo.\n");
                while (getchar() != '\n');
            }
        } while (val != 1 || Recursos[count][i] < 0);
    }
}

void AgregarRecurso(char NRecursos[MaximoComponente][30], int Cantidad_Recursos[MaximoComponente], int *countrecursos) {
    if (*countrecursos >= MaximoComponente) {
        printf("Se alcanzo el maximo numero de recursos.\n");
        return;
    }

    printf("Nombre del recurso >> ");
    while (getchar() != '\n');
    fgets(NRecursos[*countrecursos], 30, stdin);
    int len = strlen(NRecursos[*countrecursos]);
    if (NRecursos[*countrecursos][len - 1] == '\n') NRecursos[*countrecursos][len - 1] = '\0';

    int val;
    do {
        printf("Cantidad disponible >> ");
        val = scanf("%i", &Cantidad_Recursos[*countrecursos]);
        if (val != 1 || Cantidad_Recursos[*countrecursos] < 0) {
            printf("Entrada invalida. Intente de nuevo.\n");
            while (getchar() != '\n');
        }
    } while (val != 1 || Cantidad_Recursos[*countrecursos] < 0);

    (*countrecursos)++;
}

void EditarProducto(char productos[MaximoProducto][30], int Recursos[MaximoProducto][MaximoComponente], char NRecursos[MaximoComponente][30], int countproductos, int countrecursos) {
    printf("Ingrese el nombre del producto a editar:\n");
    while (getchar() != '\n');
    char Compara[30];
    fgets(Compara, 30, stdin);
    int len = strlen(Compara);
    if (Compara[len - 1] == '\n') Compara[len - 1] = '\0';

    int encontrado = 0;
    for (int i = 0; i < countproductos; i++) {
        if (strcmp(Compara, productos[i]) == 0) {
            encontrado = 1;
            printf("Nuevo nombre: ");
            fgets(productos[i], 30, stdin);
            len = strlen(productos[i]);
            if (productos[i][len - 1] == '\n') productos[i][len - 1] = '\0';

            for (int j = 0; j < countrecursos; j++) {
                int val;
                do {
                    printf("Cantidad necesaria de %s: ", NRecursos[j]);
                    val = scanf("%i", &Recursos[i][j]);
                    if (val != 1 || Recursos[i][j] < 0) {
                        printf("Entrada invalida. Intente de nuevo.\n");
                        while (getchar() != '\n');
                    }
                } while (val != 1 || Recursos[i][j] < 0);
            }
            break;
        }
    }
    if (!encontrado) printf("Producto no encontrado.\n");
}

void EliminarProducto(char productos[MaximoProducto][30], int Recursos[MaximoProducto][MaximoComponente], int *countproductos) {
    printf("Ingrese el nombre del producto a eliminar:\n");
    while (getchar() != '\n');
    char Compara[30];
    fgets(Compara, 30, stdin);
    int len = strlen(Compara);
    if (Compara[len - 1] == '\n') Compara[len - 1] = '\0';

    int encontrado = 0;
    for (int i = 0; i < *countproductos; i++) {
        if (strcmp(Compara, productos[i]) == 0) {
            encontrado = 1;
            for (int j = i; j < *countproductos - 1; j++) {
                strcpy(productos[j], productos[j + 1]);
                for (int k = 0; k < MaximoComponente; k++) {
                    Recursos[j][k] = Recursos[j + 1][k];
                }
            }
            (*countproductos)--;
            printf("Producto eliminado.\n");
            break;
        }
    }
    if (!encontrado) printf("Producto no encontrado.\n");
}
