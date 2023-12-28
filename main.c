#include <stdio.h>
#include <stdlib.h>

void EcrireFichier(){
FILE* fichier = NULL;
 
    fichier = fopen("test.txt", "w");
 
    if (fichier != NULL)
    {
      char text [50];
       scanf("%s",text); 

        fprintf(fichier, text); // Écriture du caractère A
        fclose(fichier);

    }
}

void LireFichier(){
   
    FILE *f;
    char c;
    f=fopen("test.txt","rt");

    while((c=fgetc(f))!=EOF){
        printf("%c",c);
    }

    fclose(f);
}


int main() {
   EcrireFichier();
   LireFichier();
    
    return 0;
}

