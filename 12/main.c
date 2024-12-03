#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <locale.h>
#include "11.h"
#include "12.h"


// 8. Вывод
void print_rectangle(Rectangle rect)
{
	printf("(%.1f, %.1f)  (%.1f, %.1f)\n", rect.x1, rect.y1, rect.x2, rect.y1);
    printf("(%.1f, %.1f)  (%.1f, %.1f)\n", rect.x1, rect.y2, rect.x2, rect.y2);
    printf("[%s]\n", rect.square ? "Квадрат" : "Прямоугольник");
}

// Меню 
void choose_menu(int *choose)
{
	printf("\n");
	printf("1. Создать структуру\n");
	printf("2. Переместить прямоугольник по X и Y\n");
	printf("3. Изменить ширину и высоту\n");
	printf("4. Вычислить площадь и периметр\n");
	printf("5. Найти минимальный прямоугольник, содержащий все точки\n");
	printf("6. Найти пересечение двух прямоугольников\n");
	printf("7. Найти прямоугольник, вписанный в окружность\n");
	printf("8. Вывести прямоугольник\n");
    printf("9. Выход\n");
	printf("Выберите действие: ");
	scanf("%d", choose);
	printf("\n");
}

void lab11() {
	setlocale(LC_ALL, "Russian");
	int choose;
	Rectangle rectangle = Create_rectangle(0, 0, 0, 0);
    do {
        do {
            choose_menu(&choose);
        } while (choose < 1 || choose > 9);
        
        if (choose == 1) {
            point_type x1, y1, x2, y2;
            printf("Введите первую точку (x, y):\n");
            scanf(string_type " " string_type, &x1, &y1);
            printf("Введите вторую точку (x, y):\n");
            scanf(string_type " " string_type, &x2, &y2);
            rectangle = Create_rectangle(x1, y1, x2, y2);
            print_rectangle(rectangle);
        }
        else if (choose == 2) {
            point_type dx, dy;
            printf("Введите смещение по X:\n");
            scanf(string_type, &dx);
            printf("Введите смещение по Y:\n");
            scanf(string_type, &dy);
            move_rectangle(&rectangle, dx, dy);
            print_rectangle(rectangle);
        }
        else if (choose == 3) {
            point_type newWidth, newHeight;
            printf("Введите новую ширину:\n");
            scanf(string_type, &newWidth);
            printf("Введите новую высоту:\n");
            scanf(string_type, &newHeight);
            change_rectangle(&rectangle, newWidth, newHeight);
            print_rectangle(rectangle);
        }
        else if (choose == 4) {
            point_type a = 0; 
            point_type p = 0;
            calculate(&rectangle, &a, &p);
            print_rectangle(rectangle);
            printf("Площадь = ");
            printf(string_type "\n", a);
            printf("Периметр = ");
            printf(string_type "\n", p);
        }
        else if (choose == 5) {
            Rectangle new_rectangle;
            int count = 0;
            int i;
            point_type x = 0;
            point_type y = 0;
            do {
                printf("Введите количество точек: ");
                scanf("%d", &count);
            } while (count <= 0);

            point_type array[count][2];
            for (i = 0; i < count; i++) {
                printf("Введите координаты точки %d (x, y):\n", i + 1);
                scanf(string_type " " string_type, &x, &y);
                array[i][0] = x;
                array[i][1] = y;
            }
            rectangle = min_rectangle(array, count);
            print_rectangle(rectangle);
        }
        else if (choose == 6) {
            point_type x1, y1, x2, y2;
            point_type x3, y3, x4, y4;
            Rectangle rect1, rect2;
            printf("Введите первую точку первого прямоугольника (x, y):\n");
            scanf(string_type " " string_type, &x1, &y1);
            printf("Введите вторую точку первого прямоугольника (x, y):\n");
            scanf(string_type " " string_type, &x2, &y2);
            rect1 = Create_rectangle(x1, y1, x2, y2);

            printf("Введите первую точку второго прямоугольника (x, y):\n");
            scanf(string_type " " string_type, &x3, &y3);
            printf("Введите вторую точку второго прямоугольника (x, y):\n");
            scanf(string_type " " string_type, &x4, &y4);
            rect2 = Create_rectangle(x3, y3, x4, y4);

            rectangle = intersection_rectangles(rect1, rect2);
            print_rectangle(rectangle);		
        }
        else if (choose == 7) {
            point_type x, y, r;
            printf("Введите координаты центра окружности (x, y):\n");
            scanf(string_type " " string_type, &x, &y);
            printf("Введите радиус:\n");
            scanf(string_type, &r);
            rectangle = inscribed_circle(x, y, r);
            print_rectangle(rectangle);
        }
        else if (choose == 8) {
            print_rectangle(rectangle);
        }
    } while (choose != 9);
    
	exit(0);
}


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



void lab12() {
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
				exit(0);

			default:
				printf("Неверный выбор. Повторите ввод");
		}
	}
}


int main()
{
    setlocale(LC_ALL, "Russian");
    int choice;

    while (true)
    {
        printf("Выберите лабораторную работу:\n"
        "1. Лабораторная работа 11\n"
        "2. Лабораторная работа 12\n"
        "3. Выход\n");
        printf("\n");
        printf("Введите номер: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
            case 1:
                lab11();
                break;
            case 2:
                lab12();
                break;
            case 3:
                printf("Выход из программы.\n");
                return 0;
            default:
                printf("Некорректный выбор. Пожалуйста, попробуйте снова.\n");
        }
    }
}
