// В каждой лабораторной работе нужно создать динамический массив структур, 
// описывающих сущность из вариантов задания. В работе должны быть функции по 
// созданию структуры, добавлению её в массив, удалению из массива, обновление данных 
// (изменение) структуры, вывод информации по всем структурам из массива, вывод 
// информации только по сущностям, имеющим указанную комбинацию состояний 
// (реализовать через маску). 
// Структура сущности должна содержать перечисляемое поле, задающее минимум 3 
// типа сущности, поле объединения с подструктурами, каждая из которых задаёт свои поля 
// для каждого типа сущности (минимум 2 поля для каждого типа сущности), и поле, 
// содержащая минимум пять флагов, описывающих комбинации состояний сущности 
// (Например для сущности «транспортное средство» это могут быть флаги «ИСПОЛЬЗУЕТСЯ», 
// «НЕ_ЗАПРАВЛЕН», «АРЕНДОВАН», «ТРЕБУЕТ_ОФОРМЛЕНИЯ», «ТРЕБУЕТ_РЕМОНТА»)

// Вариант 18. Транспортное средство. Создайте структуру Vehicle, которая содержит поле
// перечисление, устанавливающее тип транспортного средства, поле-объединение 
// структур, которые содержат разные параметры в зависимости от типа транспортного 
// средства, и поле с флагами для установления комбинаций состояния транспортного 
// средства.

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

#define MAX_LENGTH  	50
#define IN_USE 			0x01
#define NOT_REFUELED 	0x02
#define RENTED 			0x04
#define NEEDS_DOCUMENTS 0x08
#define NEEDS_REPAIR 	0x10

// Перечисление транспортных средств
typedef enum {
    CAR,
    TRUCK,
    MOTORCYCLE,
} VehicleType;


// Все структуры для каждого ТС
typedef struct {
	int seats;
	float engineVolume;
} CarInfo;

typedef struct {
	int number_axles;
	float maxLoad;
} TruckInfo;

typedef struct {
	int maxSpeed;
	float trunkVolume;
} MotorcycleInfo;

// Объединение
typedef union {
	CarInfo car;
	TruckInfo truck;
	MotorcycleInfo motorcycle;
} VehicleDetails;

// Автомобили структурой
typedef struct {
	VehicleType type;
	VehicleDetails details;
	unsigned char flags;
} Vehicle;



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
}

// 4. Обновление
void UpdateVehicle(Vehicle *vehicle, VehicleType new_type, VehicleDetails new_details, unsigned char new_flags) {
	{
		vehicle->type = new_type;
		vehicle->details = new_details;
		vehicle->flags = new_flags;
	}
}


// 5. Вывод Полностью
void PrintVehicle(const Vehicle *vehicle) {
	printf("Тип автомибильного средства: ");
	switch (vehicle->type) {
		case CAR:
			printf("Автомобиль\n");
			printf("Количество мест: %d\n", vehicle->details.car.seats);
			printf("Объём двигателя: %.2f\n", vehicle->details.car.engineVolume);
			break;
		case TRUCK:
			printf("Грузовик\n");
			printf("Максимальная нагрузка: %.2f\n", vehicle->details.truck.maxLoad);
			printf("Количество осей: %d\n", vehicle->details.truck.number_axles);
			break;
		case MOTORCYCLE:
			printf("Мотоцикл\n");
			printf("Максимальная скорость: %d\n", vehicle->details.motorcycle.maxSpeed);
			printf("Объём багажника: %f \n", vehicle->details.motorcycle.trunkVolume);
			break;
	}

	printf("Cостояния: ");
	if (vehicle->flags & IN_USE)
		printf("Используется");
	if (vehicle->flags & NOT_REFUELED)
		printf("Не заправлен");
	if (vehicle->flags & RENTED)
		printf("Арендован");
	if (vehicle->flags & NEEDS_DOCUMENTS)
		printf("Требует оформления");
	if (vehicle->flags & NEEDS_REPAIR)
		printf("Требует ремонта");
	printf("\n");
}

void PrintAllVehicles(Vehicle **vehicles, int count) {
	int i;
	for (i = 0; i < count; i++) {
		printf("Транспортное средство %d:\n", i + 1);
		PrintVehicle(vehicles[i]);
		printf("\n");
	}
}

void PrintVehicleByFlags(Vehicle **vehicles, int count, unsigned char flagMask) {
	int i;
	for (i = 0; i < count; i++) {
		if ((vehicles[i]->flags & flagMask) == flagMask) {
			PrintVehicle(vehicles[i]);
			printf("\n");
		}
	}
}


void InputVehicleDetails(VehicleDetails *details,VehicleType type) {
	switch(type) {
		case CAR:
			printf("Введите количество сидений: ");
			scanf("%d", &details->car.seats);
			printf("Введите объём двигателя: ");
			scanf("%f", &details->car.engineVolume);
			break;
		case TRUCK:
			printf("Введите количество осей: ");
			scanf("%d", &details->truck.number_axles);
			printf("Введите максимальную нагрузку: ");
			scanf("%f", &details->truck.maxLoad);
			break;

		case MOTORCYCLE:
			printf("Введите максимальную скорость: ");
			scanf("%d", &details->motorcycle.maxSpeed);
			printf("Введите объём багажника: ");
			scanf("%f", &details->motorcycle.trunkVolume);
			break;

	}
}



int main() {
	setlocale(LC_ALL, "Russian");
	int count = 0;
	Vehicle **vehicles= NULL;
	int choice;
	Vehicle *new_vehicle;
	VehicleDetails details;
	unsigned char flags;
	int vehicle_index;

	printf("Выберите функцию\n");
	printf("1. Создать транспортное средство\n");
	printf("2. Удалить транспортное средство\n");
	printf("3. Обновить транспортное средство\n");
	printf("4. Вывести все транспортные средства\n");
	printf("5. Вывести транспортные заданные комбинацией флагов\n");
	printf("6. Выход\n");

	while (true) {
		printf("\n");
		printf("Введите номер функции: ");
		scanf("%d", &choice);
		printf("\n");

		switch (choice) {
			case 1:
				printf("Выберите тип траспортного средство\n");
				printf("0 - Машина  ");
				printf("1 - Грузовик  ");
				printf("2 - Мотоцикл \n");
				int type;
				scanf("%d", &type);
				if (type < 0 || type > 2) {
					printf("Неверно.\n");
					break;
				}
				printf("Введите флаги состояния трансортного средства (введите значение в формате 0x..): ");
				scanf("%hhx", &flags);
				InputVehicleDetails(&details, (VehicleType)type);
				new_vehicle = CreateVehicle((VehicleType)type,  details, flags);
				vehicles = AddVehicle(vehicles, &count, new_vehicle);
				printf("Транспортное средство создано и добавлено в массв.\n");
				break;


			case 2:
				if (count == 0) {
					printf("Нет транспортных средств для удаления.\n");
					break;
				}
				printf("Введите индекс  для удаления (1-%d): ", count);
				scanf("%d", &vehicle_index);
				vehicle_index--;

				if (vehicle_index >= 0 && vehicle_index < count) {
					vehicles = DelVehicle(vehicles, &count, vehicle_index);
					printf("Транспортных средство удалено.\n");
				} else {
					printf("Неверный индекс");
				}
				break;


			case 3:
				if (count == 0) {
					printf("Нет транспортных средств для обновления.\n");
					break;
				}
				printf("Введите индекс  для обновления (1-%d): ", count);
				scanf("%d", &vehicle_index);
				vehicle_index--;
				if (vehicle_index >= 0 && vehicle_index < count) {
					printf("Введите новые данные для транспортного средства.\n");
					printf("Выберите тип траспортного средство\n");
					printf("0 - Машина  ");
					printf("1 - Грузовик  ");
					printf("2 - Мотоцикл  ");
					scanf("%d", &type);

					if (type < 0 || type > 2) {
						printf("Неверно.\n");
						break;
					}
					printf("Введите флаги состояния трансортного средства (введите значение в формате 0x..): ");
					scanf("%hhx", &flags);

					InputVehicleDetails(&details, (VehicleType)type);

					UpdateVehicle(vehicles[vehicle_index], (VehicleType)type, details, flags);

				}

				else {
					printf("Неверный индекс");
				}
				break;


			case 4:
				if (count == 0) {
					printf("Нет транспортных средств.");
					break;
				}
				printf("Все траспортные средства:\n");
				PrintAllVehicles(vehicles, count);
				break;


			case 5:
				printf("Введите маску флагов для фильтрации ТС: ");
				scanf("%hhx", &flags);
				printf("ТС с указанной комбинацией:\n");
				PrintVehicleByFlags(vehicles, count, flags);
				break;


			case 6:
				printf("Выход из программы. \n");
				int i;
				for (i = 0; i < count; i++) {
					free(vehicles[i]);
				}
				free(vehicles);
				return 0;

			default:
				printf("Неверный выбор. Повторите ввод");
		}
	}
}


