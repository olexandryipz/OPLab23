#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <Windows.h>

struct Trip {
    char carBrand[50];
    char carNumber[20];
    char destination[50];
    double payloadCapacity;
    double costPerUnit;
    double totalCost;
};

void createTrips(struct Trip* trips, int* count) {
    printf("Марка автомобіля: ");
    scanf("%s", trips[*count].carBrand);

    printf("Номер автомобіля: ");
    scanf("%s", trips[*count].carNumber);

    printf("Пункт призначення: ");
    scanf("%s", trips[*count].destination);

    printf("Вантажопідйомність (у тонах): ");
    scanf("%lf", &trips[*count].payloadCapacity);

    printf("Вартість одиниці вантажу: ");
    scanf("%lf", &trips[*count].costPerUnit);

    trips[*count].totalCost = trips[*count].payloadCapacity * trips[*count].costPerUnit;

    (*count)++;
}

void displayTrips(struct Trip* trips, int count) {
    printf("---------------------------------------------------------------------\n");
    printf("Марка | Номер | Пункт призначення | Вантаж, т | Вартість | Загальна вартість\n");
    printf("---------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%s | %s | %s | %.2lf | %.2lf | %.2lf\n",
            trips[i].carBrand, trips[i].carNumber, trips[i].destination,
            trips[i].payloadCapacity, trips[i].costPerUnit, trips[i].totalCost);
    }

    printf("---------------------------------------------------------------------\n");
}

void searchTrips(struct Trip* trips, int count, const char* parameter) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(trips[i].carNumber, parameter) == 0 || strcmp(trips[i].destination, parameter) == 0) {
            found = 1;
            printf("Знайдено запис:\n");
            printf("Марка: %s\n", trips[i].carBrand);
            printf("Номер: %s\n", trips[i].carNumber);
            printf("Пункт призначення: %s\n", trips[i].destination);
            printf("Вантажопідйомність: %.2lf т\n", trips[i].payloadCapacity);
            printf("Вартість одиниці вантажу: %.2lf\n", trips[i].costPerUnit);
            printf("Загальна вартість вантажу: %.2lf\n", trips[i].totalCost);
            break;
        }
    }

    if (!found) {
        printf("Запис з параметром \"%s\" не знайдено.\n", parameter);
    }
}

void deleteTrips(struct Trip* trips, int* count, const char* carNumber) {
    for (int i = 0; i < *count; i++) {
        if (strcmp(trips[i].carNumber, carNumber) == 0) {
            for (int j = i; j < *count - 1; j++) {
                trips[j] = trips[j + 1];
            }
            (*count)--;
            printf("Запис з номером %s видалено.\n", carNumber);
            return;
        }
    }

    printf("Запис з номером %s не знайдено.\n", carNumber);
}

void sortTrips(struct Trip* trips, int count, int ascending) {
    struct Trip temp;

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if ((ascending && trips[j].totalCost > trips[j + 1].totalCost) ||
                (!ascending && trips[j].totalCost < trips[j + 1].totalCost)) {
                temp = trips[j];
                trips[j] = trips[j + 1];
                trips[j + 1] = temp;
            }
        }
    }

    printf("Масив відсортовано за %s.\n", ascending ? "зростанням" : "спаданням");
}

int main() {
    struct Trip trips[100];
    int count = 0;
    int choice;
    char parameter[20];

    do {
        printf("Оберіть опцію:\n");
        printf("1. Створення нового запису\n");
        printf("2. Виведення масиву структур на екран у вигляді таблиці\n");
        printf("3. Пошук запису за параметром\n");
        printf("4. Видалення запису із масиву\n");
        printf("5. Сортування масиву структур за деяким параметром\n");
        printf("0. Вихід\n");
        printf("Ваш вибір: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            createTrips(trips, &count);
            break;
        case 2:
            displayTrips(trips, count);
            break;
        case 3:
            printf("Введіть параметр для пошуку: ");
            scanf("%s", parameter);
            searchTrips(trips, count, parameter);
            break;
        case 4:
            printf("Введіть номер автомобіля для видалення: ");
            scanf("%s", parameter);
            deleteTrips(trips, &count, parameter);
            break;
        case 5:
            printf("Оберіть параметр для сортування (1 - за зростанням, 0 - за спаданням): ");
            scanf("%d", &choice);
            sortTrips(trips, count, choice);
            break;
        case 0:
            printf("Програма завершена.\n");
            break;
        default:
            printf("Неправильний вибір. Спробуйте ще раз.\n");
        }
    } while (choice != 0);

    return 0;
}
