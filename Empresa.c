#include <stdio.h>
#include <string.h>
#include "funciones.h"

int main() {
    int Recursos[MaximoProducto][MaximoComponente] = {0};
    int Cantidad_Recursos[MaximoComponente] = {0};
    int opc = 0, countproductos = 0, seguir = 1, countrecursos = 3;
    char productos[MaximoProducto][30] = { "", "", "", "", "" };
    char NRecursos[MaximoComponente][30] = {"Tiempo", "Ruedas", "BloquePlano"};

    while (seguir == 1) {
        menu();
        opc = valopc();
        switch (opc) {
            case 1:
                if (countproductos < MaximoProducto) {
                    Crearproducto(Recursos, NRecursos, productos, countproductos, countrecursos);
                    countproductos++;
                } else {
                    printf("Maximo numero de productos alcanzado.\n");
                }
                break;

            case 2:
                for (int i = 0; i < countproductos; i++) {
                    printf("Producto #%d: %s\n", i + 1, productos[i]);
                    printf("Componentes necesarios:\n");
                    printf("Recurso\tCantidad\n");
                    for (int j = 0; j < countrecursos; j++) {
                        printf("%s\t%i\n", NRecursos[j], Recursos[i][j]);
                    }
                }
                break;

            case 3: {
                submenu();
                int subopc = valopc();
                switch (subopc) {
                    case 1:
                        AgregarRecurso(NRecursos, Cantidad_Recursos, &countrecursos);
                        break;
                    case 2:
                        EditarProducto(productos, Recursos, NRecursos, countproductos, countrecursos);
                        break;
                    case 3:
                        EliminarProducto(productos, Recursos, &countproductos);
                        break;
                    case 4:
                        break;
                    default:
                        printf("Opcion del submenu no valida.\n");
                        break;
                }
                break;
            }

            case 4:
                printf("Recurso\tCantidad\n");
                for (int i = 1; i < countrecursos; i++) {
                    printf("%s\t%i\n", NRecursos[i], Cantidad_Recursos[i]);
                }
                break;

            case 5:
                for (int i = 1; i < countrecursos; i++) {
                    int anadir = -1;
                    do {
                        printf("Cantidad de %s a anadir: ", NRecursos[i]);
                        if (scanf("%i", &anadir) != 1 || anadir < 0) {
                            printf("Entrada invalida, debe ser numero positivo.\n");
                            while (getchar() != '\n');
                        }
                    } while (anadir < 0);
                    Cantidad_Recursos[i] += anadir;
                }
                break;

            case 6: 
                ProduccionProducto(productos, Recursos, NRecursos, Cantidad_Recursos, countproductos, countrecursos);
                break;
            case 7:
                seguir = 0;
                break;

            default:
                printf("Opcion no valida.\n");
                break;
        }
    }
    return 0;
}
