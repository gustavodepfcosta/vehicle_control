#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int array_size = 20;

typedef struct vehicle { //Definição do modelo de dados para cada instância de um veículo
    char brand[20];
    char model[20];
    char license_plate[9];
    int year_of_fabrication;
    struct vehicles *next;
} Vehicle; 


void title_printer() { 
    printf("\n------------------------------\n");
    printf("Seja bem-vindo ao Sistema de Controle de Veículos\nInsira o número da opção desejada:\n"); 
    printf("(1) Listar veículos cadastrados\n");
    printf("(2) Inserir um novo veículo\n");
    printf("(3) Listar os veículos filtrando-se por ano de fabricação\n");
    printf("(4) Listar por ano de fabricação específico\n");
    printf("(5) Listrar os veículos filtrando-se pelo modelo\n");
    puts("Digite qualquer letra para sair");
};


int menu_choice() {
    int choice = 0; 
    printf("Digite o número da opção desejada: ");
    scanf("%d", &choice);

    return choice;
}


Vehicle model_instanciator(char* brand, char* model, char* license_plate, int year_of_fabrication) {  
    //Instanciando veículos
    Vehicle new_vehicle;
        strcpy(new_vehicle.brand, brand);   
        strcpy(new_vehicle.model, model); 
        strcpy(new_vehicle.license_plate, license_plate); 
        new_vehicle.year_of_fabrication = year_of_fabrication;

    return new_vehicle;
};


void model_printer(Vehicle car_instance) { //Função para imprimir cada instância de maneira organizada! 
    printf("\n------------------------------");
    printf("\n - Marca: %s\n - Modelo: %s\n - Placa: %s\n - Ano de fabricação: %d", car_instance.brand, car_instance.model, car_instance.license_plate, car_instance.year_of_fabrication);
    printf("\n------------------------------\n");
};


int main() {
    int i, j;  
    int newYearOfFabrication;
    int chosenYearOfFabrication;
    int choice = 1;
    int register_counter = 5;
    int sumExistChecker = 0;
    int existChecker[20];
    char newBrand[20];
    char newModel[20];
    char chosenModel[20];
    char newLicensePlate[9];
    Vehicle car[array_size], temp;

    //Iniciando um pequeno banco de dados
    car[0] = model_instanciator("Chevrolet", "Cobalt", "FMJ-0870", 2014);
    car[1] = model_instanciator("Honda", "Civic", "EVF-3581", 2014);
    car[2] = model_instanciator("Volkswagen", "Golf", "EGQ-1234", 2014);
    car[3] = model_instanciator("Chevrolet", "Tracker", "DZA-7533", 2007);
    car[4] = model_instanciator("Ford", "Mustang", "SEX-6666", 2019);
    car[5] = model_instanciator("Hyundai", "HB20", "EAF-1297", 2017);

    while (choice > 0 && choice <= 5) {
        // Importante frisar que o caminho mais correto seria utilizar o método fgets() e sem utilizar fflush(), visto que pode ser considerado um UNDEFINED BEHAVIOUR.
        fflush(stdin);
        title_printer();
        choice = menu_choice();

        switch(choice) {
            case 1: //Listagem de veículos
                printf("\n------------------------------\n");
                for (i = 0; i <= register_counter; i++) {
                    model_printer(car[i]); 
                    printf("\n");   
                };
                
                break;

            case 2: //Inserção de novos veículos
                printf("\n------------------------------\n");
                printf("Temos espaço para mais %d veículos", array_size - register_counter);
                printf("\nDigite as informações do veículo que deseja cadastrar:");
                printf("\n------------------------------\n");

                fflush(stdin);
                printf("\nMarca: "); 
                scanf("%19[^\n]", newBrand);
                
                fflush(stdin);
                printf("\nModelo: ");
                scanf("%19[^\n]", newModel);
                
                fflush(stdin);
                printf("\nPlaca (XXX-YYYY): "); 
                scanf("%8[^\n]", newLicensePlate);
                
                fflush(stdin);
                printf("\nAno de fabricação: "); 
                scanf("%d", &newYearOfFabrication);

                register_counter++;
                car[register_counter] = model_instanciator(newBrand, newModel, newLicensePlate, newYearOfFabrication);
                printf("\nVocê registrou:\n");
                model_printer(car[register_counter]); printf("\n");

                break;

            case 3: //Listagem de veículo por ordem crescente de ano de fabricação
                //Técnica de BubbleSort
                printf("\n------------------------------\n");
                puts("Listando de acordo com o ano de fabricação");
                for (i = 0; i <= register_counter; ++i) {
                    for (j = i + 1; j <= register_counter; ++j) {
                        if (car[i].year_of_fabrication > car[j].year_of_fabrication) {
                            temp = car[i];
                            car[i] = car[j];
                            car[j] = temp; 
                            
                        }
                    }
                }
                
                for (i = 0; i <= register_counter; i++) {
                    model_printer(car[i]); 
                    printf("\n");   
                }

                break;

            case 4: //Lista apenas veículos com o ano de fabricação especificado
                printf("\n------------------------------\n");
                printf("Deseja visualizar veículos fabricados em qual ano? ");
                scanf("%d", &chosenYearOfFabrication);
                printf("\n------------------------------\n");
                
                sumExistChecker = 0;

                for (i = 0; i <= register_counter; i++) {
                    if (car[i].year_of_fabrication == chosenYearOfFabrication) {
                        existChecker[i] = 1;
                    }
                    else {
                        existChecker[i] = 0;
                    }
                    sumExistChecker = sumExistChecker + existChecker[i];
                }

                if (sumExistChecker == 0) {
                    printf("\nNão há veículos de %d registrados em nosso sistema", chosenYearOfFabrication);
                }

                else {
                    printf("Listando veículos fabricados em %d", chosenYearOfFabrication);
                    for (i = 0; i <= register_counter; i++) {
                        if (existChecker[i] == 1) {
                            model_printer(car[i]);
                        }
                    }
                }

                break;

            case 5: //Listando apenas veículos de acordo com o modelo
                printf("\nDigite o modelo do veículo que deseja buscar exatamente do jeito que foi registrado: ");
                fflush(stdin);
                scanf("%s", chosenModel);

                sumExistChecker = 0;

                for (i = 0; i <= register_counter; i++) {
                    if (strcmp(car[i].model, chosenModel) == 0) {
                        existChecker[i] = 1;
                    }
                    else {
                        existChecker[i] = 0;
                    }
                    sumExistChecker = sumExistChecker + existChecker[i];
                }

                if (sumExistChecker == 0) {
                    printf("\nNão há veículos modelo %s registrados em nosso sistema\n", chosenModel);
                }

                else {
                    printf("\nListando veículos com nome %s", chosenModel);
                    for (i = 0; i <= register_counter; i++) {
                        if (existChecker[i] == 1) {
                            model_printer(car[i]);
                        }
                    }
                }

                break;

        }
    }

    return 0;
}
