//Desenvolvido por Alex Brosso e Willian Sumida

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct musica // Struct Música
{
    int id;
    char titulo[200];
    char artista[200];
    char album[200];
    int duracao; //segundos
} musica;

typedef struct musica_no //Struct Músicas
{
    musica *musica;
    struct musica_no *ant;
    struct musica_no *prox;
} musica_no;
musica_no *iniMusica;

typedef struct playlist_no //Struct Playlist
{
    musica *musica;
    struct playlist_no *prox;
} playlist_no;
playlist_no *iniPlaylist;

typedef struct lplaylists_no //Struct Lista de Playlists
{
    int id;
    char nome[200];
    playlist_no *musicas;
    struct lplaylists_no *prox;
} lplaylists_no;
lplaylists_no *iniPastaPlaylist;

//FUNCAO MENU INICIAL
int menuInicio()
{
    int opcaoInicio; //Variavel que armazena uma opção desejada pelo usuário.
    printf("\n----------MENU INICIAL----------\n");
    printf("\n1- Cadastrar musica");
    printf("\n2- Imprimir musicas");
    printf("\n3- Criar playlist");
    printf("\n4- Inserir musica na playlist");
    printf("\n5- Imprimir playlists criadas");
    printf("\n6- Imprimir musicas das playlists criadas");
    printf("\n7- Excluir");
    printf("\n8- Shuffle");
    printf("\n0- Sair\n");
    scanf("%d", &opcaoInicio);

    return opcaoInicio; // Retorna a opção digitada pelo usuário
}

//FUNCAO CADASTRA MUSICA
int cadastraMusica(int id)
{
    system("cls"); //Limpa o terminal
    printf("\n----------CADASTRO DE MUSICA----------\n");
    //soma contador de id da musica
    id++;

    //variaveis
    int hr, min, seg;

    musica *c; /* o ponteiro para o espaço alocado */

    /* aloco um único byte na memória */
    c = malloc(sizeof(musica));

    c->id = id; //Atribui o id ao id de C
    printf("Nome da musica: ");
    scanf(" %[^\n]s", c->titulo); //Atribui o que foi digitado ao titulo de C

    printf("Nome do artista: ");
    scanf(" %[^\n]s", c->artista); //Atribui o que foi digitado ao arista de C

    printf("Nome do album: ");
    scanf(" %[^\n]s", c->album); //Atribui o que foi digitado ao album de C

    printf("Quantidade de horas da musica: ");
    scanf("%d", &hr); //Horas de música

    printf("Quantidade de minutos da musica: ");
    scanf("%d", &min); //Minutos de musica

    printf("Quantidade de segundos da musica: ");
    scanf("%d", &seg); //Segundos de música

    //conversao do tempo da musica para segundos
    c->duracao = converterSegundos(hr, min, seg);

    //Insere C (a música) na lista duplamente encadeada
    insereMusica(c);
    return id;
    system("pause");
}

//FUNÇÃO CONVERTE EM SEGUNDOS
int converterSegundos(int hr, int min, int seg)
{
    return (hr * 3600) + (min * 60) + seg; //Retorna em segundos
}

//FUNÇÃO CONVERTE NO FORMATO CORRETO
int converterHora(int segNconvertido)
{
    int hr, min, segundos, resto; //horas, minutos, segundos, resto

    resto = segNconvertido % 3600; //Resto para prosseguir com os demais cálculos
    hr = segNconvertido / 3600;    //Cálculo para converter os segundos em hora

    min = resto / 60;   //Cálculo para converter os segundos restantes em minutos
    resto = resto % 60; //Resto para prosseguir com os demais cálculos

    segundos = resto; //Segundos de música

    printf("%.2d:%.2d:%.2d", hr, min, segundos); //Imprime Tempo formatado
}

//FUNÇÃO INSERE MÚSICA
void insereMusica(musica *p)
{
    musica_no *novo;                  //Cria um novo ponteiro do tipo Música
    novo = malloc(sizeof(musica_no)); //Aloca o ponteiro em um espaço da memória

    novo->musica = p;             //As informações da música do novo ponteiro são iguais as de p(a música cadastrada na função cadastraMusica())
    novo->prox = iniMusica->prox; //Novo vai ser adicionado como próximo da cabeça
    novo->ant = iniMusica;        //Movo vai ter como anterior a cabeça

    if (iniMusica->prox != NULL) //Se a lista encadeada não estiver vazia
    {
        iniMusica->prox->ant = novo; //O valor que estava depois da cabeça, agora tem novo como anterior
    }
    iniMusica->prox = novo; //Próximo da cabeça é novo
}

//FUNÇÃO IMPRIME MÚSICA
void imprimeMusica(int id)
{
    system("cls");
    if (id > 0) //Caso exista músicas
    {
        printf("\n----------LISTA DE MUSICAS----------\n");
        musica_no *p; //Cria um noov ponteiro do tipo música

        p = iniMusica->prox; //p recebe a primeira música da lista
        while (p != NULL)    //Enquanto p não for Nulo/ Enquanto a lista duplamente encadeada não chegar ao fim
        {
            printf("\n%d | %s | %s | %s | ", p->musica->id, p->musica->titulo, p->musica->artista, p->musica->album); //Imprime as informações da música
            converterHora(p->musica->duracao);                                                                        //Converte o tempo no formato Hora:Min:Seg
            p = p->prox;                                                                                              // p recebe o próximo de p (próx da lista duplamente encadeada)
            printf("\n");
        }
    }
    else
    {
        printf("\nNenhuma musica cadastrada\n");
    }
    system("pause");
}

//FUNÇÃO CRIA PLAYLIST
int criaPlaylist(int id1)
{
    system("cls");
    //soma contador de id da Playlist
    id1++;
    //criacao cabeca para lista ligada circular de playlist
    iniPlaylist = malloc(sizeof(playlist_no)); //Aloca espaço na memória
    iniPlaylist->prox = iniPlaylist;           //o próx de iniPlaylist recebe iniPlaylist
    char nome[200];
    printf("\n----------CRIAR PLAYLIST----------\n");
    printf("Digite o nome da playlist: ");
    scanf(" %[^\n]s", &nome); //Nome da Playlist

    inserePlaylistPasta(id1, nome, iniPlaylist); //Insere Playlist na Pasta de Playlists

    return id1;
    system("pause");
}

//FUNÇÃO INSERE MÚSICA NA PLAYLIST
void insereMusicaNaPlaylist(int id, int id1)
{
    system("cls");
    if (id > 2 && id1 > 0) //Se id de músicas for maior que 2 E id de Playlist for maior que 0
    {
        int verificador1;
        verificador1 = buscaPlaylist(); //Busca a Playlist e recebe seu endereço de memória

        if (verificador1 != NULL) //Se verificador for diferente de nulo
        {
            printf("Digite os ids das musicas para serem adicionadas (de 3 em 3): ");
            musica_no *p = iniMusica; //Ponteiro p do tipo musica_no recebe a cabeça da lista duyplamente encadeada de músicas

            //biblioteca strtok();
            int vetor[3];
            char nums[512];                  //espaço para os numeros todos como um texto
            scanf(" %[^\n]", nums);          //lê todos os números como um texto
            char *token = strtok(nums, " "); //lê até ao primeiro espaço para a variavel token
            int pos = 0;                     //posição para guardar os numeros no vetor começa em 0

            //biblioteca atoi()
            while (token != NULL && pos < 3)
            {
                vetor[pos++] = atoi(token); //guarda o valor convertido em numero no vetor e avança
                token = strtok(NULL, " ");  //lê até ao próximo espaço a partir de onde terminou
            }

            int i, verificador;

            for (i = 0; i < 3; i++)
            {
                p = iniMusica->prox; //p recebe o próximo da lista
                verificador = 0;
                while (p) //Enquanto não chegar ao fim da lista
                {
                    if (vetor[i] == p->musica->id) //Se o ID da música estiver em vetor[i]
                    {
                        verificador = 1;
                        printf("\n%d | %s | %s | %s | ", p->musica->id, p->musica->titulo, p->musica->artista, p->musica->album); //Imprime informações da música
                        converterHora(p->musica->duracao);                                                                        //Converte a duração para o formato Hor:Min:Seg
                        printf("\n");
                        insereMusicaPlaylist(p->musica, verificador1); //Insere a música na playlist
                    }
                    if (p->prox == NULL && verificador == 0) //Se o próximo de p for o último da lista E verificador for igual a 0
                    {
                        printf("\nid %d nao encontrado\n", vetor[i]);
                    }
                    p = p->prox; //p recebe o próximo da lista
                }
            }
        }
        else
        {
            printf("\nNome da playlist nao encontrada\n");
        }
    }
    else
    {
        printf("\nMusicas insuficientes para colocar na playlist ou nenhuma playlist cadastrada\n");
    }
    system("pause");
}

//FUNÇÃO INSERE MÚSICA NA PLAYLIST
void insereMusicaPlaylist(musica_no *p, playlist_no *q)
{
    playlist_no *novo;                  //Cria um novo ponteiro do tipo playlist_no
    novo = malloc(sizeof(playlist_no)); //Aloca espaço na memória para esse ponteiro
    novo->musica = p;                   //Novo recebe p como música
    novo->prox = q->prox;               //O próximo de novo recebe o primeiro item da playlist
    q->prox = novo;                     //O primeiro item da playlist recebe novo
}

//FUNÇÃO INSERE PLAYLIST NA PASTA
void inserePlaylistPasta(int id, char nome[200], playlist_no *p)
{
    lplaylists_no *novo;                  //Cria um novo ponteiro do tipo lplaylist_mp
    novo = malloc(sizeof(lplaylists_no)); //Aloca espaço na memória para novo
    novo->id = id;                        //O ID de novo recebe ID da playlist
    strcpy(novo->nome, nome);             //Nome de novo é igual a Nome *(Essa função foi utilizada devido a erros na atribuição devido ao tipo)*
    novo->musicas = p;                    //Musicas de novo recebe p
    novo->prox = iniPastaPlaylist->prox;  //Próximo de novo recebe o próximo da cabeça
    iniPastaPlaylist->prox = novo;        //Próximo da cabeça recebe novo
}

//FUNÇÃO IMPRIME LISTA DE PLAYLISTS
void imprimePlaylistPasta(int id)
{
    system("cls");
    if (id > 0) //Se existir ao menos uma playlist
    {
        printf("\n----------LISTA DE PLAYLISTS----------\n");
        lplaylists_no *p;           //Cria um novo ponteiro do tipo lplaylist_no
        p = iniPastaPlaylist->prox; //p recebe o próximo da cabeça
        while (p)
        {
            printf("\n%d | %s \n", p->id, p->nome); //Imprime informações da playlist atual
            p = p->prox;                            //p recebe o próximo
        }
    }
    else
    {
        printf("\nNenhuma playlist cadastrada\n");
    }
    system("pause");
}

//FUNÇÃO BUSCA PLAYLIST
int buscaPlaylist()
{
    system("cls");
    char nome[200];
    printf("Digite o nome da playlist: ");
    scanf(" %[^\n]", &nome);    //Nome da Playlist
    lplaylists_no *p;           //Cria um novo ponteiro do tipo lPlaylists_no
    p = iniPastaPlaylist->prox; //p recebe o próximo da cabeça
    while (p)
    {
        if (strcmp(p->nome, nome) == 0) //Se o nome da playlist atual for igual ao nome digitado
        {
            return p->musicas; //true
        }
        p = p->prox; //p recebe o próximo
    }
}

//FUNÇÃO IMPRIME MÚSICAS DA PLAYLIST
void imprimeMusicaPlaylist(int id)
{
    system("cls");
    if (id > 0) //Se existir ao menos uma playlist
    {
        char nome[200];
        printf("\n----------LISTA DE MUSICAS NA PLAYLIST----------\n");
        printf("Digite o nome da playlist para exibir as musicas: ");
        scanf(" %[^\n]s", &nome); //Nome da playlist

        int verificador = 0; //para verificar a existência da música

        lplaylists_no *p; //Cria um novo ponteiro p do tipo lplaylist_no
        lplaylists_no *q; //Cria um novo ponteiro q do tipo lplaylist_no

        p = iniPastaPlaylist->prox; //p recebe próximo da cabeça
        while (p)                   //Enquanto não chegar ao fim da lista
        {
            if (strcmp(p->nome, nome) == 0) //Se o nome da playlist atual for igual ao nome digitado
            {
                verificador = 1; // true
                q = p->musicas;  // q recebe as músicas dessa playlist
            }
            p = p->prox; // p recebe o próximo da lista
        }
        if (verificador == 1) //Se for verdade
        {
            imprimeDentroPlaylist(q, nome); //Imprime as músicas presentes na playlist
        }
        else
        {
            printf("Playlist nao encontrada");
        }
    }
    else
    {
        printf("Nenhuma playlist cadastrada");
    }
    system("pause");
}

//FUNÇÃO IMPRIME MÚSICAS DA PLAYLIST 2
void imprimeDentroPlaylist(playlist_no *p, char nome[200])
{
    system("cls");
    printf("\n----------PLAYLIST: %s ----------\n", nome);
    playlist_no *q; //Cria um novo ponteiro do tipo Playlist_no
    q = p->prox;    //q recebe a primeiro item da playlist
    while (q != p)  //Enquanto q for diferente de p
    {
        printf("\n%d | %s | %s | %s | ", q->musica->id, q->musica->titulo, q->musica->artista, q->musica->album); //Imrpime as informações da playlist
        converterHora(q->musica->duracao);                                                                        //Converte a duração para o formato Hor:Min:Seg
        printf("\n");
        q = q->prox; //q recebe o próximo da lista
    }
}

//FUNÇÃO REMOVE DA LISTA
void removerLista(int id)
{
    system("cls");
    musica_no *p, *q;    //Cria dois ponteriros (p e q) do tipo musica_no
    p = iniMusica->prox; //p recebe o próximo da cabeça
    q = iniMusica;       //q recebe a cabeça;
    while (p != NULL)    //Enquanto não chegar ao fim da lista
    {
        if (p->musica->id == id) //Se o ID for igual ao ID digitado
        {
            q->prox = p->prox; // Exclui a música da lista
            free(p->musica);   // o espaço reservado para aquela música se torna livre
        }
        else
        {
            q = q->prox; //q recebe o próximo
        }
        p = p->prox; //p recebe o próximo
    }
}

//FUNÇÃO REMOVE DA PLAYLIST
void removerPlaylist(int id)
{
    int enderecoPlaylist;
    enderecoPlaylist = buscaPlaylist(); //Busca a Playlist e recebe seu endereço de memória

    playlist_no *p = enderecoPlaylist; //Cria um novo ponteiro p do tipo playlist_no e recebe endereço de memória
    playlist_no *q = enderecoPlaylist; //Cria um novo ponteiro q do tipo playlist_no e recebe endereço de memória
    p = p->prox;                       //p recebe o próximo para ficar a frente do q
    while (p != enderecoPlaylist)      //Enquanto p for diferente do inicio da playlist
    {
        if (p->musica->id == id) //Se o id da música e o id digitado forem iguais
        {
            q->prox = p->prox; //Exclui a música da playlist
        }
        else
        {
            q = q->prox; //q recebe o próximo
        }
        p = p->prox; //p recebe o próximo
    }
}

//FUNÇÃO REMOVE DE TUDO
int removerTudo(int id, int id1)
{
    system("cls");
    printf("\n----------REMOCAO DE MUSICA----------\n");

    musica_no *p = iniMusica->prox; //Cria um novo ponteiro p do tipo music_no e recebe o próximo da cabeça
    musica_no *q = iniMusica;       //Cria um novo ponteiro p do tipo music_no e recebe a cabeça
    while (p)                       //Enquanto não acabar a lista
    {
        if (p->musica->id == id)
        {                      // A MUSICA EXISTE
            int v = p->musica; // ENDEREÇO DA MUSICA
            lplaylists_no *q;
            playlist_no *r, *s;
            q = iniPastaPlaylist->prox;
            while (q)
            { // Percorre PastaPlaylist
                r = q->musicas->prox;
                s = q->musicas;
                while (r != q->musicas)
                { // Percorre Playlist
                    if (r->musica == v)
                    {                      // Localizou a música
                        s->prox = r->prox; //a musica da playlist é excluida
                    }
                    else
                    {
                        s = s->prox; // Vai para a próxima
                    }
                    r = r->prox; //Vai para a próxima
                }
                q = q->prox; //Vai para a próxima
            }
            p = NULL; //Corta o While
        }
        else
        {
            p = p->prox; //Vai para a próxima
        }
    }
    removerLista(id); //Remove da lista
    system("pause");
    return id1--;
}

//FUNÇÃO RETORNA QUANTIDADE DE MÚSICAS
int qntdMusicaPlaylist(playlist_no *r)
{
    int count = 1;
    if (r != NULL)
    {
        playlist_no *q, *p;
        p = r;       // p recebe a playlist
        q = p->prox; // q recebe o primeiro item da playlist
        while (q != p)
        {
            count++;     //Adiciona 1 ao contador
            q = q->prox; //q recebe o próximo
        }
        return count; //retorna contadador com a quantidade músicas na playlist
    }
    else
    {
        return count = 0;
    }
}

//FUNÇÃO ACHA VALORES PARA TROCA
int acharTroca(int playlist, int count)
{
    int x;

    x = (rand() % count + 1); //Seleciona um número randomizado dentre a quantidade de musicas exitentes na playlist

    int contador;
    contador = 0;
    playlist_no *p, *q;
    p = playlist;         // p recebe playlist
    while (contador <= x) //Enquanto o contador for menor ou igual ao número randomizado
    {
        if (contador == x)
        {
            return p; //retorna a música selecionada pela randomização
        }
        p = p->prox; //p recebe próximo
        contador++;  // adiciona 1 ao contador
    }
}

//FUNÇÃO TROCA
void troca(playlist_no *q, playlist_no *r)
{
    playlist_no *aux;
    aux->musica = q->musica; //aux recebe 1º musica
    q->musica = r->musica;   // q recebe 2º musica
    r->musica = aux->musica; // r recebe 1º musica
}

//FUNÇÃO SHUFFLE
void shuffle()
{
    int playlist;
    int count;
    playlist = buscaPlaylist();           //Busca playlist e retorna seu endereço de memória
    count = qntdMusicaPlaylist(playlist); // Define a quantidade de músicas na playlist

    count -= 1; //Contador reduzido para não interferir na randomização

    int i = 1;

    if (count > 0)
    {

        playlist_no *w;
        w = playlist; // w recebe playlist
        w = w->prox;  // w recebe o primeiro item da playlist
        printf("------------1--------------");
        while (w != playlist)
        {
            printf("\n%d | %s | %s | %s | ", w->musica->id, w->musica->titulo, w->musica->artista, w->musica->album); //imprime os dados das músicas antes do shuffle
            converterHora(w->musica->duracao);                                                                        //converte a duração para Hor:Min:Seg
            printf("\n");
            w = w->prox; //w recebe o próximo
        }

        playlist_no *q, *r;

        while (i <= count / 2)
        {
            q = acharTroca(playlist, count); //Acha uma música aleatória para realizar a troca
            r = acharTroca(playlist, count); //Acha outra música aleatória para realizar a troca
            troca(q, r);                     //realiza a troca
            i++;
        }

        w = playlist; // w recebe playlist
        w = w->prox;  // w recebe o primeiro item da playlist
        printf("------------2--------------");
        while (w != playlist)
        {
            printf("\n%d | %s | %s | %s | ", w->musica->id, w->musica->titulo, w->musica->artista, w->musica->album); // imprime os dados das músicas depois do shuffle
            converterHora(w->musica->duracao);                                                                        //converte a duração para Hor:Min:Seg
            printf("\n");
            w = w->prox; //w recebe o próximo
        }
    }
    else
    {
        printf("Playlist nao encontrada");
    }

    system("pause");
}

//FUNÇÃO PRINCIPAL
int main()
{
    system("cls");     //Limpa o terminal
    srand(time(NULL)); //Insere uma "semente" (utilizada devido da randomização presente na função shuffle())
    int opc;           //para a escolha de remoção ser mais precisa
    int startMenu;     //para o menu funcionar com o while

    //start contador de id de musica
    int idMusica = 0;
    //start contador de id playlist
    int idPlaylist = 0;

    //criacao cabeca para lista duplamente ligada de musica
    iniMusica = malloc(sizeof(musica_no)); //Aloca espaço na memória
    iniMusica->prox = NULL;                //inicia prox em NULL
    iniMusica->ant = NULL;                 //Inicia ant em NULL

    //criacao cabeca para lista ligada pasta de playlist
    iniPastaPlaylist = malloc(sizeof(lplaylists_no)); //Aloca espaço na memória
    iniPastaPlaylist->prox = NULL;                    //Inicia prox em NULL

    while (startMenu)
    {
        startMenu = menuInicio(); //Retorna a startMenu a opção do usuário

        switch (startMenu) //reproduz o que foi solicitado pela escolha do usuário
        {
        case 1:
            idMusica = cadastraMusica(idMusica);
            break;

        case 2:
            imprimeMusica(idMusica);
            break;

        case 3:
            idPlaylist = criaPlaylist(idPlaylist);
            break;

        case 4:
            insereMusicaNaPlaylist(idMusica, idPlaylist);
            break;

        case 5:
            imprimePlaylistPasta(idPlaylist);
            break;

        case 6:
            imprimeMusicaPlaylist(idPlaylist);
            break;

        case 7:
            system("cls");
            printf("\n1- Excluir musica da playlist\n2- Excluir musica\nEscolha: ");
            scanf("%d", &opc); //Armazena a opção de remoção

            if (opc == 1)
            {
                int id1;
                printf("\nId da musica a ser excluida: ");
                scanf("%d", &id1); //ID da música escolhida para ser excluida da Playlist

                removerPlaylist(id1);
            }
            else if (opc == 2)
            {
                int id1;
                system("cls");
                printf("\nId da musica a ser excluida: ");
                scanf("%d", &id1); //ID da música escolhida para ser excluida de toods os lugares possíveis

                idMusica = removerTudo(id1, idMusica);
            }
            else
            {
                printf("\nOpcao invalida!\n");
                system("pause");
            }
            break;

        case 8:
            shuffle();
            break;
        }
        system("cls");
    }
    printf("\nPROGRAMA ENCERRADO!");
}