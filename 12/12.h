#ifndef LAB12_H
#define LAB12_H
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

Vehicle *CreateVehicle(VehicleType type, VehicleDetails details, unsigned char flags);
Vehicle **AddVehicle(Vehicle **vehicles, int *count,Vehicle *NewVehicle);
Vehicle **DelVehicle(Vehicle **vehicles, int *count, int index);
void UpdateVehicle(Vehicle *vehicle, VehicleType new_type, VehicleDetails new_details, unsigned char new_flags);
#endif
