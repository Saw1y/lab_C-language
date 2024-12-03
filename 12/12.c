#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

#include "12.h"


// Функции
// 1. Создание
Vehicle *CreateVehicle(VehicleType type, VehicleDetails details, unsigned char flags) {
	Vehicle* NewVehicle = (Vehicle*)malloc(sizeof(Vehicle));
	if (NewVehicle) {
		NewVehicle->type = type;
		NewVehicle->details = details;
		NewVehicle->flags = flags;
	}
	return NewVehicle;
}
// 2. Добавление
Vehicle **AddVehicle(Vehicle **vehicles, int *count,Vehicle *NewVehicle) {
	vehicles = (Vehicle **)realloc(vehicles, (*count + 1) * sizeof(Vehicle*));
	if (vehicles) {
		vehicles[*count] = NewVehicle;
		(*count)++;
	}
	return vehicles;
}
// 3. Удаление
Vehicle **DelVehicle(Vehicle **vehicles, int *count, int index) {
	if (index >= 0 && index < *count) {
		free(vehicles[index]);
		int i;
		for (i = index; i < *count - 1; i++) {
			vehicles[i] = vehicles[i + 1];
		}
		(*count)--;
		vehicles = (Vehicle**)realloc(vehicles, (*count) * sizeof(Vehicle *));
	}
    return vehicles;
}

// 4. Обновление
void UpdateVehicle(Vehicle *vehicle, VehicleType new_type, VehicleDetails new_details, unsigned char new_flags) {
	{
		vehicle->type = new_type;
		vehicle->details = new_details;
		vehicle->flags = new_flags;
	}
}

