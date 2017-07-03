#include <stdio.h>
#include <string.h>
#include <locale.h>

struct PROFESSOR{
    int codigo;
    char nome[40];
    char titulo;
    int horas;
    float salario;
};

void abrirArquivo(struct PROFESSOR *prof,int max){
    int i;
    FILE *arq;
    arq= fopen("sistema.bin","rb");
    for(i=0;i<max;i++){
        fread(&prof[i],sizeof(struct PROFESSOR),1,arq);
        printf("%d %40s %c %d %f \n",prof[i].codigo,prof[i].nome,prof[i].titulo,prof[i].horas,prof[i].salario);
    }

    fclose(arq);

}

int num_linhas(){
    char c;
    int n=0;
    FILE *arq;
    arq= fopen("sistema.bin","rb");
    struct PROFESSOR linhas;

    while(fread(&linhas,sizeof(struct PROFESSOR),1,arq))
        n++;

    fclose(arq);
    return n;

}

void salvarArquivo(struct PROFESSOR *prof,int max){
    int i;

    FILE *arq;
    arq= fopen("sistema.bin","wb");

    for(i=0;i<max;i++)
        fwrite(&prof[i],sizeof(struct PROFESSOR),1,arq);

    printf("foi");
    fclose(arq);
}

void incluir(struct PROFESSOR *prof,int i){
    fflush(stdin);
    printf("Digite o código do professor: ");
    scanf("%d",&prof[i].codigo);
    fflush(stdin);
    printf("Digite o nome do professor: ");
    gets(prof[i].nome);
    prof[i].titulo = 'E';
    printf("Será iniciado com o título: %c \n",prof[i].titulo);
    printf("Digite o total de horas: ");
    scanf("%d",&prof[i].horas);
    prof[i].salario = prof[i].horas * 20.40 * 4.5;

}

void pesquisar(struct PROFESSOR *prof,int max){
    int codigo,i,existe=0;
    fflush(stdin);
    printf("Digite o código do professor: ");
    scanf("%d",&codigo);
    for(i=0;i<max;i++){
        if(prof[i].codigo == codigo){
            printf("\n----------------\n");
            printf("Código: %d\nNome: %s\nTítulo: %c\nHoras semanais: %d\nSalário: %.2f\n",prof[i].codigo,prof[i].nome,prof[i].titulo,prof[i].horas,prof[i].salario);
            existe++;
            printf("----------------\n\n");
            system("pause");
        }
    }
    if(existe == 0)
        printf("Não há professor cadastrado com esse código!");
    printf("\n");
}

void alterarT(struct PROFESSOR *prof,int max){
    int codigo,i,existe=0;
    char c;
    fflush(stdin);
    printf("Digite o código do professor: ");
    scanf("%d",&codigo);

    for(i=0;i<max;i++){
        if(prof[i].codigo == codigo){
            printf("\n----------------\n");
            printf("Nome: %s \nTitulo atual: %c\n",prof[i].nome,prof[i].titulo);
            printf("\nOpção de titulos: \n");
            switch(prof[i].titulo){
                case 'E':
                    printf(" [M] - Mestre \n");
                case 'M':
                    printf(" [D] - Doutor \n");
                case 'D':
                    printf(" [C] - Cancelar \n");
                    break;
                default:
                    printf("Algo está errado com o título, redefinindo para Especialista! \n");
                    prof[i].titulo = 'E';
                    return;
            }
            printf("\n----------------\n");

            switch(prof[i].titulo){
                case 'E':
                    do{
                        prof[i].titulo = toupper(getch());
                    }while(prof[i].titulo != 'M' && prof[i].titulo != 'D' && prof[i].titulo != 'C');
                    break;
                case 'M':
                    do{
                        prof[i].titulo = toupper(getch());
                    }while(prof[i].titulo != 'D' && prof[i].titulo != 'C');
                    break;
                case 'D':
                    do{
                        prof[i].titulo = toupper(getch());
                    }while(prof[i].titulo != 'C');
                    break;
            }

            printf("Título alterado com sucesso!\n\n");

            existe++;
        }
    }
    if(existe == 0)
        printf("Não há professor cadastrado com esse código!");
    printf("\n");
}

void alterarH(struct PROFESSOR *prof,int max){
    int codigo,i,existe=0;
    fflush(stdin);
    printf("Digite o código do professor: ");
    scanf("%d",&codigo);

    for(i=0;i<max;i++){
        if(prof[i].codigo == codigo){
                printf("\n----------------\n");
                printf("Nome: %s \nHoras atuais: %d",prof[i].nome,prof[i].horas);
                printf("\n----------------\n");
                do{
                printf("\nDigite o novo tempo:");
                scanf("%d",&prof[i].horas);
                }while(prof[i].horas > 168 || prof[i].horas < 0 ) ;
                printf("\nHoras alteradas com sucesso!\n\n");

        }
    }
}

void excluir(struct PROFESSOR *prof,int max){
    int codigo,i,existe=0;
    char c,nome[40];
    fflush(stdin);
    printf("Digite o código do professor: ");
    scanf("%d",&codigo);

    for(i=0;i<max;i++){
        if(prof[i].codigo == codigo){
            printf("Tem certeza que deseja excluir [%s] do sistema? [S/N]\n",prof[i].nome);
            do{
                switch(toupper(c)){
                    case 'S':
                        strcpy(nome,prof[i].nome);

                        printf("Professor [%s] deletado com sucesso!",)
                }
            }while(c != 'S' && c!= 'N');
          existe++
        }
    }
}

char menu(int max){
    char digitado;
    printf("Número de professores: %d\n\n",max);
    printf("Digite a opção: \n");
    printf("1- Incluir novo professor.\n");
    printf("2- Pesquisar dados de um professor.\n");
    printf("3- Alterar titulo.\n");
    printf("4- Alterar número de horas.\n");
    printf("5- Excluir professor.\n");
    printf("6- Imprimir folha de pagamento.\n");
    printf("7- Sair.\n\n");

    digitado = getch();
    return digitado;
}

int main(){
    struct PROFESSOR p[50];
    int max = num_linhas();
    abrirArquivo(p,max);
    setlocale(LC_ALL,"Portuguese");

    while(1){
        switch(menu(max)){
            case '1':
                incluir(p,max);
                max+=1;
                break;
            case '2':
                pesquisar(p,max);
                break;
            case '3':
                alterarT(p,max);
                break;
            case '4':
                alterarH(p,max);
                break;
            case '7':
                salvarArquivo(p,max);
                printf("\nfoi\n");
                return 0;
                break;
        }
    }

}

