

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
    char status[50];  
};

struct Rental {
    int rentalID;
    char matricule[50];
    struct date date;  
    int duree;
};

void addCarToFile(struct Car car) {
    FILE *file = fopen("car.txt", "a");

    if (file != NULL) {
        fprintf(file, "%s %s %s %s\n", car.matricule, car.brand, car.model, car.status);
        fclose(file);
    } else {
        printf("Error opening the file.\n");
    }
}

void displayCarDescription(char  matricule [50]) {
    FILE *file = fopen("car.txt", "r");

    if (file != NULL) {
        struct Car car;
        while (fscanf(file, "%s %s %s %49s\n", car.matricule, car.brand, car.model, car.status) != EOF) {
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

void deleteCarFromFile(char matricule[50]) {
    FILE *inputFile = fopen("car.txt", "r");
    FILE *outputFile = fopen("temp.txt", "w");

    if (inputFile != NULL) {
        struct Car car;
        int found = 0;

        while (fscanf(inputFile, "%s %s %s %s\n", car.matricule, car.brand, car.model, car.status) != EOF) {
            if ((strcmp(car.matricule, matricule) == 0) && (strcmp(car.status,"enpanne")==0 )){
                found = 1;
            } else {
                fprintf(outputFile, "%s %s %s %s\n", car.matricule, car.brand, car.model, car.status);
            }
        }

        fclose(inputFile);
        fclose(outputFile);

        remove("car.txt");
        rename("temp.txt", "car.txt");
        printf("Voiture supprimée avec succès.\n");
        
    } else {
        printf("Erreur lors de l'ouverture des fichiers.\n");
    }
}

void modifyCarStatus( char matricule[50], char newStatus[50]) {
    FILE *inputFile = fopen("car.txt", "r");
    FILE *outputFile = fopen("temp.txt", "w");

    if (inputFile != NULL && outputFile != NULL) {
        struct Car car;
        while (fscanf(inputFile, "%s %s %s %49s\n", car.matricule, car.brand, car.model, car.status) != EOF ) {
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
        printf("Statut de la voiture modifié avec succes.\n");
    } else {
        printf("Erreur lors de l ouverture des fichiers.\n");
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
        int availableCars = 0;

        printf("Cars Available for Rent:\n");

        while (fscanf(file, "%s %s %s %s\n", car.matricule, car.brand, car.model, car.status) != EOF) {
            if (strcmp(car.status, "disponible") == 0) {
                printf("Car ID: %s\n", car.matricule);
                printf("Brand: %s\n", car.brand);
                printf("Model: %s\n", car.model);
                printf("Status: %s\n", car.status);
                printf("--------------\n");
                availableCars++;
            }
        }

        fclose(file);

        if (availableCars == 0) {
            printf("No cars available for rent.\n");
        }
    } else {
        printf("Error opening car.txt for reading.\n");
    }
}


void returnCarInCaseOfClaim(char matricule[50]) {
    FILE *inputFile = fopen("rental.txt", "r");
    FILE *outputFile = fopen("temp.txt", "w");

    if (inputFile != NULL && outputFile != NULL) {
        struct Rental rental;
        while (fscanf(inputFile, "%d %s %d/%d/%d %d\n", &rental.rentalID, rental.matricule,
                      &rental.date.j, &rental.date.m, &rental.date.a, &rental.duree) != EOF) {
            if (strcmp(rental.matricule, matricule) == 0) {
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
    
    



        fclose(inputFile);
        fclose(outputFile);

        remove("rental.txt");
        rename("temp.txt", "rental.txt");
        printf("Voiture retournée avec succès.\n");
     }else {
        printf("Erreur lors de l'ouverture des fichiers.\n");
    }
}

void rentCarFromFile(char matricule[50]) {
 

    FILE *file = fopen("car.txt", "r+");

    if (file != NULL) {
        struct Car car;
        int found = 0;

        while (fscanf(file, "%s %s %s %49s\n", car.matricule, car.brand, car.model, car.status) != EOF) {
            if (strcmp(car.matricule, matricule) == 0 && strcmp(car.status, "disponible") == 0) {
                
                found =1;
                FILE *rentalFile = fopen("rental.txt", "a");
                if (rentalFile != NULL) {
                    struct Rental rental;
                    rental.rentalID = rand();  
                    strcpy(rental.matricule, car.matricule);
                    printf("Entrez la date de location (JJ/MM/AAAA): ");
                    scanf("%d/%d/%d", &rental.date.j, &rental.date.m, &rental.date.a);
                    printf("Entrez la durée de location en jours : ");
                    scanf("%d", &rental.duree);

                    fprintf(rentalFile, "%d %s %d/%d/%d %d\n", rental.rentalID, rental.matricule,
                            rental.date.j, rental.date.m, rental.date.a, rental.duree);

                    printf("Voiture louée avec succès.\n");
                    fclose(rentalFile);
                } else {
                    printf("Erreur lors de l'ouverture de rental.txt en écriture.\n");
                }
            }
        }

        fclose(file);
        char newstatus[50];
        strcpy(newstatus,"louee");
        modifyCarStatus(matricule, newstatus);

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
        printf("6. Retour d une voiture en cas de reclamation\n");
        printf("7.louer une voiture\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                struct Car car;
                printf("Matricule : ");
                scanf("%s", car.matricule);
                printf("Marque : ");
                scanf("%s", car.brand);
                printf("Modele : ");
                scanf("%49s", car.model);
                strcpy(car.status,"disponible");
                addCarToFile(car);
                break;
  
            }
            case 2: {
                printf("Entrez le matricule de la voiture à afficher : ");
                scanf("%s",matricule);
                displayCarDescription(matricule);
                break;
            }
            case 3: {
                printf("Entrez le matricule de la voiture à supprimer : ");
                scanf("%s",matricule);
                deleteCarFromFile(matricule);
                break;
            }
            case 4: {
                char newStatus[50];
                printf("Entrez le matricule de la voiture à modifier : ");
                scanf("%s",matricule);
                printf("Nouveau statut : ");
                scanf("%s",newStatus);
                modifyCarStatus(matricule, newStatus);
                break;
            }
            case 5:
                printf("Historique des locations :\n");
                displayRentalsHistory();
                break;
            case 6: {
                printf("Entrez le matricule de la voiture à retourner (réclamation) : ");
               scanf("%s",matricule);
                returnCarInCaseOfClaim(matricule);
                break;
            }
            case 7:{
                 displayAvailableCars() ;
                 printf("donner un matricule");
                 scanf("%s",matricule);
                 rentCarFromFile(matricule);
                 
                  break;


            }
          
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }

    } while (choice != 0);

    return 0;
}

