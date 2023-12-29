#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct date {
    int j;
    int m;
    int a;
};

struct Car {
    char matricule[50];
    char brand[50];
    char model[50];
    char status[20];  // Disponible, Louée, En panne, etc.
};

struct Rental {
    int rentalID;
    char matricule[50];
    struct date date;  // Format : JJ/MM/AAAA
    int duree;
};

void addCarToFile(struct Car *newCar) {
    FILE *file = fopen("car.txt", "a");

    if (file != NULL) {
        fprintf(file, "%s %s %s %s\n", newCar->matricule, newCar->brand, newCar->model, newCar->status);
        fclose(file);
        printf("Voiture ajoutée avec succès.\n");
    } else {
        printf("Erreur lors de l'ouverture de car.txt en écriture.\n");
    }
}

void displayCarDescription(const char *matricule) {
    FILE *file = fopen("car.txt", "r");

    if (file != NULL) {
        struct Car car;
        while (fscanf(file, "%s %s %s %s\n", car.matricule, car.brand, car.model, car.status) != EOF) {
            if (strcmp(car.matricule, matricule) == 0) {
                printf("Car ID: %s\n", car.matricule);
                printf("Marque: %s\n", car.brand);
                printf("Modèle: %s\n", car.model);
                printf("Statut: %s\n", car.status);
                fclose(file);
                return;
            }
        }
        fclose(file);
        printf("Voiture non trouvée.\n");
    } else {
        printf("Erreur lors de l'ouverture de car.txt en lecture.\n");
    }
}

void removeFaultyCarFromFile(char matricule[50]) {
    FILE *inputfile = fopen("car.txt", "r");
    FILE *outputfile = fopen("temp.txt", "a");

    if (inputfile != NULL ) {
        struct Car car;
        while (fscanf(inputfile, "%s %s %s %s\n", car.matricule, car.brand, car.model, car.status) != EOF) {
            if (strcmp(car.matricule, matricule) == 1 || strcmp(car.status, "En panne") ==1) {
                fprintf(outputfile, "%s %s %s %s\n", car.matricule, car.brand, car.model, car.status);
            }
        }

        fclose(inputfile);
        fclose(outputfile);

        remove("car.txt");
        rename("temp.txt", "car.txt");
        printf("Voiture supprimée avec succès.\n");
    } else {
        printf("Erreur lors de l'ouverture des fichiers.\n");
    }
}

void modifyCarStatus( char matricule[50], const char *newStatus) {
    FILE *inputFile = fopen("car.txt", "r");
    FILE *outputFile = fopen("temp.txt", "w");

    if (inputFile != NULL && outputFile != NULL) {
        struct Car car;
        while (fscanf(inputFile, "%s %s %s %s\n", car.matricule, car.brand, car.model, car.status) != EOF) {
            if (strcmp(car.matricule, matricule) == 0) {
                fprintf(outputFile, "%s %s %s %s\n", car.matricule, car.brand, car.model, newStatus);
            } else {
                fprintf(outputFile, "%s %s %s %s\n", car.matricule, car.brand, car.model, car.status);
            }
        }

        fclose(inputFile);
        fclose(outputFile);

        remove("car.txt");
        rename("temp.txt", "car.txt");
        printf("Statut de la voiture modifié avec succès.\n");
    } else {
        printf("Erreur lors de l'ouverture des fichiers.\n");
    }
}

void displayRentalsHistory() {
    FILE *file = fopen("rental.txt", "r");

    if (file != NULL) {
        struct Rental rental;
        while (fscanf(file, "%d %s %d/%d/%d %d\n", &rental.rentalID, rental.matricule,
                      &rental.date.j, &rental.date.m, &rental.date.a, &rental.duree) != EOF) {
            printf("Rental ID: %d\n", rental.rentalID);
            printf("Matricule: %s\n", rental.matricule);
            printf("Date: %02d/%02d/%04d\n", rental.date.j, rental.date.m, rental.date.a);
            printf("Durée: %d jours\n", rental.duree);
            printf("--------------\n");
        }
        fclose(file);
    } else {
        printf("Erreur lors de l'ouverture de rental.txt en lecture.\n");
    }
}
void displayAvailableCars() {
    FILE *file = fopen("car.txt", "r");

    if (file != NULL) {
        struct Car car;
        while (fscanf(file, "%s %s %s %s\n", car.matricule, car.brand, car.model, car.status) != EOF) {
            if (strcmp(car.status, "Disponible") == 0) {
                printf("Car ID: %s\n", car.matricule);
                printf("Marque: %s\n", car.brand);
                printf("Modèle: %s\n", car.model);
                printf("Statut: %s\n", car.status);
                printf("--------------\n");
            }
        }
        fclose(file);
    } else {
        printf("Erreur lors de l'ouverture de car.txt en lecture.\n");
    }
}
void returnCarInCaseOfClaim(const char *matricule) {
    FILE *inputFile = fopen("rental.txt", "r");
    FILE *outputFile = fopen("temp.txt", "w");

    if (inputFile != NULL && outputFile != NULL) {
        struct Rental rental;
        while (fscanf(inputFile, "%d %s %d/%d/%d %d\n", &rental.rentalID, rental.matricule,
                      &rental.date.j, &rental.date.m, &rental.date.a, &rental.duree) != EOF) {
            if (strcmp(rental.matricule, matricule) == 0) {
                // Handle the return of the car and any other necessary actions
            } else {
                fprintf(outputFile, "%d %s %d/%d/%d %d\n", rental.rentalID, rental.matricule,
                        rental.date.j, rental.date.m, rental.date.a, rental.duree);
            }
        }

        fclose(inputFile);
        fclose(outputFile);

        remove("rental.txt");
        rename("temp.txt", "rental.txt");
        printf("Voiture retournée avec succès.\n");
    } else {
        printf("Erreur lors de l'ouverture des fichiers.\n");
    }
}
void rentCarFromFile(char m[50]) {
    FILE *file = fopen("car.txt", "r+");

    if (file != NULL) {
        struct Car car;
        int found=0;
        while (fscanf(file, "%s %s %s %s\n", car.matricule, car.brand, car.model, car.status) != EOF) {
            if (strcmp(car.matricule, m) == 0 && strcmp(car.status, "Disponible") == 0) {
                found=1;
                modifyCarStatus(car.matricule,"louée");
                FILE *rentalFile = fopen("rental.txt", "a");
                if (rentalFile != NULL) {
                    struct Rental rental;
                    rental.rentalID = rand();  // Generate a random rental ID
                    strcpy(rental.matricule, car.matricule);
                    printf("Entrez la date de location (JJ/MM/AAAA): ");
                    scanf("%d/%d/%d", &rental.date.j, &rental.date.m, &rental.date.a);
                    printf("Entrez la durée de location en jours : ");
                    scanf("%d", &rental.duree);
                    fwrite(&rental,sizeof(struct Rental),1,rentalFile);

                    printf("Voiture louée avec succès.\n");
                    fclose(rentalFile);
                } else {
                    printf("Erreur lors de l'ouverture de rental.txt en écriture.\n");
                }
            }
        }

        fclose(file);

        if (found==0) {
            printf("Voiture non trouvée ou déjà louée.\n");
        }
    } else {
        printf("Erreur lors de l'ouverture de car.txt en lecture et écriture.\n");
    }
}

int main() {
    int choice;
    char matricule[50];

    do {
        printf("\nMenu :\n");
        printf("1. ajouter une voiture\n");
        printf("2. Afficher la description d'une voiture\n");
        printf("3. Supprimer une voiture en panne\n");
        printf("4. Modifier la description et l état d une voiture\n");
        printf("5. Afficher l historique des locations\n");
        printf("6. Retour d'une voiture en cas de réclamation\n");
        printf("7.louer une voiture\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                struct Car newCar;
                printf("Matricule : ");
                scanf("%s", newCar.matricule);
                printf("Marque : ");
                scanf("%s", newCar.brand);
                printf("Modèle : ");
                scanf("%s", newCar.model);
                strcpy(newCar.status,"disponible");
                addCarToFile(&newCar);
                break;
            }
            case 2: {
                printf("Entrez le matricule de la voiture à afficher : ");
                scanf("%s", matricule);
                displayCarDescription(matricule);
                break;
            }
            case 3: {
                printf("Entrez le matricule de la voiture à supprimer : ");
                scanf("%s", matricule);
                removeFaultyCarFromFile(matricule);
                break;
            }
            case 4: {
                char newStatus[20];
                printf("Entrez le matricule de la voiture à modifier : ");
                scanf("%s", matricule);
                printf("Nouveau statut : ");
                scanf("%s", newStatus);
                modifyCarStatus(matricule, newStatus);
                break;
            }
            case 5:
                printf("Historique des locations :\n");
                displayRentalsHistory();
                break;
            case 6: {
                printf("Entrez le matricule de la voiture à retourner (réclamation) : ");
                scanf("%s", matricule);
                returnCarInCaseOfClaim(matricule);
                break;
            }
            case 7:{
                 displayAvailableCars() ;
                 printf("donner le matricule");
                 scanf("%s",matricule);
                 rentCarFromFile(matricule);

            }
            case 0:
                printf("Programme terminé.\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }

    } while (choice != 0);

    return 0;
}
