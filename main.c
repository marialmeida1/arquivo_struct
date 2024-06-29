#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Constantes
#define MAX 100
#define MAX_LINE 256

// Struct Colaborador
typedef struct Collaborator {
    int code;
    char name[MAX];
    char email[MAX];
    float salary;
} Collaborator;

// Protótipos
void remove_line(char *);
int menu();
void register_collaborator(FILE *);
void print_file_collaborator(Collaborator, FILE *);
void search_collaborator_menu(FILE *);
int search_collaborator_code(FILE *, int);
int search_collaborator_name(FILE *, char[]);
int search_collaborator_menu_salary(FILE *);
void change_salary(int, FILE *);

int main()
{

    // Cria e fecha arquivo
    FILE *file;

    file = fopen("collaborators.txt", "a+");

    if (file == NULL) {
        printf("O arquivo não pode ser acessado");
        exit(0);
    }

    fclose(file);

    // Funcionamento do sistema
    int opc;
    do {

    opc = menu();
    system("cls");

    switch(opc) {
    case 1:
        file = fopen("collaborators.txt", "a");
        register_collaborator(file);
        fclose(file);
        break;
     case 2:
        file = fopen("collaborators.txt", "r");
        search_collaborator_menu(file);
        fclose(file);
        system("cls");
        break;
     case 3:
        file = fopen("collaborators.txt", "r+");
        int code = search_collaborator_menu_salary(file);
        system("cls");
        change_salary(code, file);
        system("cls");
        break;
     case 4:
        printf("Remover\n");
        break;
     case 5:
        printf("Imprimir\n");
        break;
     case 0:
         printf("Programa encerrado!\n");
        break;
     default:
        printf("Programa encerrado!\n");
        break;
    }

    } while(opc != 0 && opc < 6);
}

// Funções
void remove_line(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

int menu() {
    int opc;

    printf("==============================\n");
    printf("              MENU            \n");
    printf("==============================\n");
    printf(" 1 - Cadastrar colaborador\n");
    printf(" 2 - Consultar trabalhador\n");
    printf(" 3 - Alterar salario\n");
    printf(" 4 - Remover colaborador\n");
    printf(" 5 - Imprimir soma de salarios\n");
    printf(" 0 - Sair do programa\n");
    printf("==============================\n");
    printf(" Sua opcao: ");
    scanf("%d", &opc);
    printf("==============================\n");

    return opc;
}

void register_collaborator(FILE *file){

    Collaborator c;

    printf("==============================\n");
    printf("    CADASTRO DE COLABORADOR   \n");
    printf("==============================\n");

    printf(" Insira o codigo: ");
    scanf("%d", &c.code);
    while(getchar() != '\n'); // limpa buffer

    printf(" Insira o nome: ");
    fgets(c.name, MAX, stdin);
    remove_line(c.name); // remove /n

    printf(" Insira o email: ");
    fgets(c.email, MAX, stdin);
    remove_line(c.email); // remove /n

    printf(" Insira o salario: ");
    scanf("%f", &c.salary);

    printf("==============================\n");

    print_file_collaborator(c, file);
}

void print_file_collaborator(Collaborator c, FILE *file){
    fprintf(file, "%d|", c.code);
    fprintf(file, "%s|", c.name);
    fprintf(file, "%s|", c.email);
    fprintf(file, "%.2f\n", c.salary);
    printf("Cadastro realizado com sucesso!\n\n");
}

void search_collaborator_menu(FILE *file){
    int opc;

    do {
        int cod = 0;
        char name[MAX];

        printf("==============================\n");
        printf("       FORMA DE PESQUISA      \n");
        printf("==============================\n");
        printf(" 1 - Codigo do colaborador\n");
        printf(" 2 - Nome do colaborador\n");
        printf(" 0 - Sair\n");
        printf("==============================\n");
        printf(" Sua opcao: ");
        scanf("%d", &opc);
        printf("==============================\n");

        switch(opc) {
        case 1:
            printf(" Digite o codigo do colaborador: ");
            scanf("%d", &cod);
            search_collaborator_code(file, cod);
            break;
         case 2:
            printf(" Digite o nome do colaborador: ");
            while(getchar() != '\n'); // limpa buffer

            fgets(name, MAX, stdin);
            remove_line(name);

            search_collaborator_name(file, name);
            break;
         case 0:
             printf("Saindo da funcao!\n\n");
            break;
         default:
            printf("Saindo da funcao!\n\n");
            break;
        }
    } while(opc != 0 && opc < 3);
}

int search_collaborator_code(FILE *file, int query){

    Collaborator c;
    int find = 0;
    int code_collaborator;


    while(fscanf(file, "%d|%99[^|]|%99[^|]|%f\n", &c.code, c.name, c.email, &c.salary) == 4 ){

        if(query == c.code){
            printf("==============================\n");
            printf("           INFORMACOES        \n");
            printf("==============================\n");
            printf("Codigo: %d\n", c.code);
            printf("Nome: %s\n", c.name);
            printf("Email: %s\n", c.email);
            printf("Salario: %.2f\n", c.salary);
            printf("==============================\n\n");

            code_collaborator = c.code;
            find++;
        }
    }

    fseek(file, 0, SEEK_SET);

    if(find == 0){
        printf("==============================\n");
        printf(" Colaborador nao encontrado\n");
        printf("==============================\n\n");

        code_collaborator = 0;
    }

    return code_collaborator;
}

int search_collaborator_name(FILE *file, char query[]){

    Collaborator c;
    int find = 0;
    int code_colaborator;


    while(fscanf(file, "%d|%99[^|]|%99[^|]|%f\n", &c.code, c.name, c.email, &c.salary) == 4 ){

        int result = strcmp(query, c.name);

        if(result == 0){
            printf("==============================\n");
            printf("           INFORMACOES        \n");
            printf("==============================\n");
            printf("Codigo: %d\n", c.code);
            printf("Nome: %s\n", c.name);
            printf("Email: %s\n", c.email);
            printf("Salario: %.2f\n", c.salary);
            printf("==============================\n\n");

            code_colaborator = c.code;
            find++;
        }
    }

    fseek(file, 0, SEEK_SET);

    if(find == 0){
        printf("==============================\n");
        printf(" Colaborador nao encontrado\n");
        printf("==============================\n\n");

        code_colaborator = 0;
    }

    return code_colaborator;
}

int search_collaborator_menu_salary(FILE *file){
    int cod = 0;
    int opc = 0;
    char name[MAX];
    int code_collaborator;

    printf("==============================\n");
    printf("       FORMA DE PESQUISA      \n");
    printf("==============================\n");
    printf(" 1 - Codigo do colaborador\n");
    printf(" 2 - Nome do colaborador\n");
    printf(" 0 - Sair\n");
    printf("==============================\n");
    printf(" Sua opcao: ");
    scanf("%d", &opc);
    printf("==============================\n");

    switch(opc) {
    case 1:
        printf(" Digite o codigo do colaborador: ");
        scanf("%d", &cod);

        code_collaborator = search_collaborator_code(file, cod);

        break;
     case 2:
        printf(" Digite o nome do colaborador: ");
        while(getchar() != '\n'); // limpa buffer

        fgets(name, MAX, stdin);
        remove_line(name);

        code_collaborator = search_collaborator_name(file, name);
        break;
     case 0:
         printf("Saindo da funcao!\n\n");
        break;
     default:
        printf("Saindo da funcao!\n\n");
        break;
    }

    return code_collaborator;
}

void change_salary(int code_collaborator, FILE *file) {

    // Criando arquivo temp
    FILE *temp_file = fopen("collaborators.tmp", "w");
    if (temp_file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    Collaborator c;
    int line_number = 0;
    int found = 0;
    float new_salary;

    while (fscanf(file, "%d|%99[^|]|%99[^|]|%f\n", &c.code, c.name, c.email, &c.salary) == 4) {
        line_number++;

        if (code_collaborator == c.code) {
            found = 1;

            printf("==============================\n");
            printf("Digite o novo salario: ");
            scanf("%f", &new_salary);
            printf("==============================\n");
            c.salary = new_salary;
        }

        fprintf(temp_file, "%d|%s|%s|%.2f\n", c.code, c.name, c.email, c.salary);
    }

    fclose(file);
    fclose(temp_file);


    // Colaborador não encontrado
    if (!found) {
        remove("collaborators.tmp");
        return;
    }

    // Remover o arquivo original
    remove("collaborators.txt");

    // Renomear o arquivo temporário
    if (rename("collaborators.tmp", "collaborators.txt") != 0) {
        perror("Erro ao renomear arquivo");
        return;
    }

    printf("Salario atualizado para o colaborador de codigo %d.\n", code_collaborator);
}
