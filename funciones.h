#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MaximoProducto 5
#define MaximoComponente 7

void menu();
void submenu();
int valopc();

void Crearproducto(int Recursos[MaximoProducto][MaximoComponente], char NRecursos[MaximoComponente][30], char productos[MaximoProducto][30], int countproductos, int countrecursos);
void AgregarRecurso(char NRecursos[MaximoComponente][30], int Cantidad_Recursos[MaximoComponente], int *countrecursos);
void EditarProducto(char productos[MaximoProducto][30], int Recursos[MaximoProducto][MaximoComponente], char NRecursos[MaximoComponente][30], int countproductos, int countrecursos);
void EliminarProducto(char productos[MaximoProducto][30], int Recursos[MaximoProducto][MaximoComponente], int *countproductos);
void ProduccionProducto(char productos[MaximoProducto][30], int Recursos[MaximoProducto][MaximoComponente],
                        char NRecursos[MaximoComponente][30], int Cantidad_Recursos[MaximoComponente],
                        int countproductos, int countrecursos);

#endif
