#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

struct Clientes{
  long long cpf;
  char nome[51];
};

struct Veiculos{
  char placa[8];
  char tipo;
  char modelo[31];
  int ano;
  int quilometragem;
  float valor_locacao;
};

struct Locacao{
  long long cpf_aux;
  char placa_aux[8];
  char nome_aux[51];
  char modelo_aux[31];
  char tipo_aux;
  int dia, mes, ano;
};

void data_hora_atual(int &dia, int &mes, int &ano){
  time_t t = time(NULL);
  struct tm lt = *localtime(&t);
  ano  = lt.tm_year + 1900;
  mes  = lt.tm_mon + 1;
  dia  = lt.tm_mday;
}

bool eh_bissexto(int ano){
    return(ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int numero_dias_mes(int mes, int ano){
    if(mes < 1 || mes > 12 || ano <= 0)
        return -1;

    if (mes == 1 || mes == 3 || mes == 5 || mes == 7 ||
        mes == 8 || mes == 10 || mes == 12)
            return 31;
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
        return 30;
    else if (eh_bissexto(ano))
        return 29;
    else
        return 28;
}

bool verifica_cpf(Clientes clie[], long long cpf){
  for(int j = 0; j < 50; j++){
    if(cpf == clie[j].cpf){
      return true;
    }
  }
  return false;
}

void cadastro_novo_cliente(Clientes clie[]){
  long long cpf;

  for(int i = 0; i < 50; i++){
    if(clie[i].cpf == 0 && clie[i].nome[i] == '\0'){
      do{
        printf("CPF:");
        scanf ("%lld", &cpf);
        getchar();
        if(cpf < 10000000000 || cpf > 99999999999 || verifica_cpf(clie, cpf) == true)
          puts("CPF invalido ou ja cadastrado!\n");
        else{
          clie[i].cpf = cpf;
          break;
        }
      }while(cpf < 10000000000 || cpf > 99999999999 || verifica_cpf(clie, cpf) == true);

      do{
        printf ("Nome: ");
        gets (clie[i].nome);
        strupr(clie[i].nome);
        if(strlen(clie[i].nome) > 50 || strlen(clie[i].nome) < 4)
          puts("Nome invalido!\n");
        }while(strlen(clie[i].nome) > 50 || strlen(clie[i].nome) < 4);
        printf("\nCliente cadastrado com sucesso!\n");
        break;
    }
  }
}

void excluir_cliente(Clientes clie[], Locacao loca[]){
  int qtd = 0;
  long long dlt = 0;
  bool clienteLocacao = false;
  bool cpfValido = false;

  for(int i = 0; i < 50; i++){
    dlt = 0;
    if(dlt == 0) {
      do{
        printf ("CPF:");
        scanf ("%lld", &dlt);
        getchar();
        if(dlt < 10000000000 || dlt > 99999999999)
          puts ("CPF invalido!\n");
      }while (dlt < 10000000000 || dlt > 99999999999);

      if(dlt == clie[i].cpf){
        cpfValido = true;
        for(int j = 0; j < 50; j++){
          if(dlt == loca[j].cpf_aux){
            clienteLocacao = true;
          }
          if(clienteLocacao == false){
            clie[i].cpf = 0;
            clie[i].nome[0] = '\0';
            qtd++;
          }
        }
        break;
      }
    }
    break;
  }

   if(cpfValido == false){
    printf("\nErro na exclusao. Cliente nao cadastrado!\n");
   }

   if(cpfValido && clienteLocacao){
     printf("\nErro na exclusao. Cliente tem uma locacao!\n");
   }

   if(cpfValido && clienteLocacao == false){
    printf("\nCliente excluido com sucesso!\n");
   }

    clienteLocacao = false;
    cpfValido = false;
}

void listar_cliente_cpf (Clientes clie[], Locacao loca[]){
    Clientes aux;
    for(int i = 0; i < 50; i++){
      for(int j = i + 1; j < 50; j++){
        if(clie[i].cpf > clie[j].cpf){
        aux = clie[i];
        clie[i] = clie[j];
        clie[j] = aux;
        }
      }
    }

    puts("------------------------------------------------------------");
    puts("CPF         Nome");
    puts("------------------------------------------------------------");
    for(int i = 0; i < 50; i++){
      if(clie[i].cpf != 0) {
          printf("%lld %s\n", clie[i].cpf, clie[i].nome);

        for(int j = 0; j < 50; j++){
          if(clie[i].cpf == loca[j].cpf_aux){
            printf("Placa: %s\n", loca[j].placa_aux);

            if(loca[j].tipo_aux == 'C'){
              printf ("Tipo: Carro\n");
            }
            else{
              printf ("Tipo: Moto\n");
            }

          printf("Modelo: %s\n", loca[j].modelo_aux);
          printf("Data de Locacao: %d/%d/%d\n\n", loca[j].dia, loca[j].mes, loca[j].ano);
          }
        }
      }
    }
puts("------------------------------------------------------------");

}
void listar_cliente_nome(Clientes clie[], Locacao loca[]){
  Clientes aux;

    for(int i = 1; i < 50; i++){
      for(int j = 0; j < 49; j++){
        if(strcmpi (clie[i].nome, clie[j].nome) == -1){
          aux = clie[i];
          clie[i] = clie[j];
          clie[j] = aux;
        }
      }
    }

    puts("------------------------------------------------------------");
    puts("NOME                            CPF ");
    puts("------------------------------------------------------------");

  for(int i = 0; i < 50; i++){
    if(clie[i].nome[0] != '\0'){
        printf("%-30s  %-30lld\n", clie[i].nome, clie[i].cpf);

      for(int j = 0; j < 50; j++){
        if(clie[i].cpf == loca[j].cpf_aux){
          printf ("Placa: %s\n", loca[j].placa_aux);

          if(loca[j].tipo_aux == 'C'){
            printf ("Tipo: Carro\n");
          }
          else{
            printf ("Tipo: Moto\n");
          }

        printf("Modelo: %s\n", loca[j].modelo_aux);
        printf("Data de Locacao: %d/%d/%d\n\n", loca[j].dia, loca[j].mes, loca[j].ano);
        }
      }
    }
  }
  puts("------------------------------------------------------------");
}

int cadastro_cliente(Clientes clie[],Locacao loca[]){
int menuCliente;

  puts("\nMenu do Cadastro de Clientes");
  printf(" 1-Cadastro novo cliente\n 2-Excluir cliente\n 3-Listar clientes(ordenado por CPF)\n 4-Listar clientes(ordenado por nome)\n 5-Voltar\n");
  scanf("%d", &menuCliente);

  switch(menuCliente){
    case 1: cadastro_novo_cliente(clie);
      break;
    case 2: excluir_cliente(clie,loca);
      break;
    case 3: listar_cliente_cpf(clie, loca);
      break;
    case 4: listar_cliente_nome(clie, loca);
      break;
    case 5: return 0;
    default: printf("Comando invalido\n");
      break;
  }
  return 0;
}

void cadastro_novo_veiculo(Veiculos veic[]){
  bool placaValida = false;
  bool tipoValido = false;
  int compara;

  for(int i = 0; i < 50; i++){
    for(int k = 0; k < 50; i++){
      if (veic[i].placa[0] == '\0'){
        do{
          fflush(stdin);
          printf ("Placa: ");
          gets(veic[i].placa);
          if(i == k ){
            k++;
          }
          compara = strcmpi (veic[i].placa, veic[k].placa);
          if (compara != 0){
            if (strlen(veic[i].placa) == 7){
              for (int j = 0; j < 7; j++){
                if (isalpha(veic[i].placa[j]) != 0 && isalpha(veic[i].placa[j+1]) != 0 && isalpha(veic[i].placa[j+2]) != 0){
                  if (isdigit(veic[i].placa[j+3]) != 0 && isdigit(veic[i].placa[j+4]) != 0 && isdigit(veic[i].placa[j+5]) != 0 && isdigit(veic[i].placa[j+6]) != 0){
                    placaValida = true;
                  }
                }
              }
            }
          }
          else{
            printf ("\nErro no cadastro. Veiculo ja cadastrado!\n");
            }
          if(placaValida == false){
            printf ("\nPlaca invalida!\n");
          }
        }while(placaValida == false);
      break;
    }
  }

      do{
        printf ("Tipo de veiculo (C) Carro ou (M) Moto: ");
        fflush(stdin);
        scanf ("%c", &veic[i].tipo);
        if(veic[i].tipo == 'C' || veic[i].tipo == 'M') {
          tipoValido = true;
        }
      }while(tipoValido == false);

      do{
        fflush(stdin);
        printf("Modelo: ");
        gets(veic[i].modelo);
        strupr(veic[i].modelo);
      }while(strlen(veic[i].modelo) > 30 || strlen(veic[i].modelo) < 4);

      do{
        printf("Ano: ");
        scanf("%d", &veic[i].ano);
      }while(veic[i].ano < 2000 || veic[i].ano > 2021);

      do{
        printf ("Valor da Locacao/Dia: ");
        scanf ("%f", &veic[i].valor_locacao);
      }while(veic[i].valor_locacao <= 0);

      do{
        printf ("Quilometragem do veiculo: ");
        scanf ("%d", &veic[i].quilometragem);
      }while(veic[i].quilometragem <= 0);

      if(placaValida){
        puts("Veiculo cadastrado com sucesso!");
      }
  break;
  }

        placaValida = false;
        tipoValido = false;
}

  void excluir_veiculo(Veiculos veic[], Locacao loca[]){
      char dlt[8];
      bool placaCadastrada = false;
      bool veiculoLocado = false;

      placaCadastrada = false;

      printf("Placa: ");
      fflush(stdin);
      gets(dlt);

      for(int i = 0; i < 50; i++){
        if(strcmpi (dlt, veic[i].placa) == 0){
          placaCadastrada = true;

          for(int j = 0; j < 50; j++){
            if(strcmpi (dlt, loca[j].placa_aux) == 0){
              veiculoLocado = true;
              printf ("\nErro na exclusao. Veiculo esta locado!\n");
            }
          }
        }
        if(placaCadastrada && veiculoLocado == false){
          veic[i].placa[0] = '\0';
          printf ("\nExclusao realizada com sucesso!\n");
          break;
        }
      }

      if(placaCadastrada == false){
          printf("\nErro na exclusao. Veiculo nao cadastrado!\n");
      }

      veiculoLocado = false;
}

void listar_veiculo_placa(Veiculos veic[], Locacao loca[]){
    Veiculos aux;

    for(int i = 1; i < 50; i++){
      for(int j = 0; j < 49; j++){
        if(strcmpi (veic[i].placa, veic[j].placa) == -1){
          aux = veic[i];
          veic[i] = veic[j];
          veic[j] = aux;
        }
      }
    }

    puts("------------------------------------------------------------");
    puts("PLACA   TIPO   MODELO       ANO    KM       VALOR");
    puts("------------------------------------------------------------");

    for(int i = 0; i < 50; i++){
      if(veic[i].placa[0] != '\0'){
        printf("%s   %c    %-10s   %d   %-3d    %.2f\n", veic[i].placa, veic[i].tipo, veic[i].modelo, veic[i].ano, veic[i].quilometragem, veic[i].valor_locacao);

        for(int j = 0; j < 50; j++){
          if(strcmpi (veic[i].placa, loca[j].placa_aux) == 0){
            printf("CPF: %lld\n", loca[j].cpf_aux);
            printf("Nome: %s\n", loca[j].nome_aux);
            printf("Data de Locacao: %d/%d/%d\n\n", loca[j].dia, loca[j].mes, loca[j].ano);
          }
        }
      }
    }
    puts("------------------------------------------------------------");
}

void listar_veiculo_modelo(Veiculos veic[], Locacao loca[]){
  Veiculos aux;

  for(int i = 1; i < 50; i++){
    for(int j = 0; j < 49; j++){
      if(strcmpi (veic[i].modelo, veic[j].modelo) == -1){
        aux = veic[i];
        veic[i] = veic[j];
        veic[j] = aux;
      }
    }
  }

  puts("----------------------------------------------------------------");
  puts("MODELO      TIPO   PLACA      ANO     VALOR    QUILOMETRAGEM");
  puts("----------------------------------------------------------------");
  for(int i = 0; i < 50; i++){
    if(veic[i].placa[0] != '\0'){
      printf("%-10s   %c     %s    %d     %.2f      %d\n", veic[i].modelo, veic[i].tipo, veic[i].placa, veic[i].ano, veic[i].valor_locacao, veic[i].quilometragem);

      for(int j = 0; j < 50; j++){
        if(strcmpi (veic[i].placa, loca[j].placa_aux) == 0){
          printf ("CPF: %lld\n", loca[j].cpf_aux);
          printf ("Nome: %s\n", loca[j].nome_aux);
          printf ("Data de Locacao: %d/%d/%d\n\n", loca[j].dia, loca[j].mes, loca[j].ano);
        }
      }
    }
  }
  puts ("----------------------------------------------------------------");

}

int cadastro_veiculo (Veiculos veic[], Locacao loca[]){

  int menuVeiculo;

  puts ("\nMenu do Cadastro de Veiculos");
  printf (" 1-Cadastrar novo veiculo\n 2-Excluir veiculo\n 3-Listar veiculos(ordenado por placa)\n 4-Listar veiculos(ordenado por modelo)\n 5-Voltar\n");
  scanf ("%d", &menuVeiculo);

  switch (menuVeiculo){
    case 1: cadastro_novo_veiculo(veic);
      break;
    case 2: excluir_veiculo(veic, loca);
      break;
    case 3: listar_veiculo_placa(veic, loca);
      break;
    case 4: listar_veiculo_modelo(veic, loca);
      break;
    case 5: return 0;
    default: printf("Comando invalido\n");
      break;
  }
  return 0;
}

void locar_veiculo (Clientes clie[], Veiculos veic[], Locacao loca[]){
  char placa_locar[8], modelo[31], nome[51], tipo;
  long long cpf_locar;
  bool clienteLocador = false;
  bool clienteCadastrado = false;
  bool veiculoLocado = false;
  bool veiculoCadastrado = false;
  int quilometragem;
  int dia, mes, ano;

  printf("CPF: ");
  scanf("%lld", &cpf_locar);

  for (int i = 0; i < 50; i++){
    if (cpf_locar == clie[i].cpf){
      clienteCadastrado = true;
      strcpy (nome, clie[i].nome);
    }
  }

  for (int i = 0; i < 50; i++){
    if (cpf_locar == loca[i].cpf_aux){
      clienteLocador = true;
    }
  }

  if(clienteLocador == false && clienteCadastrado == true){
    printf("Placa: ");
    scanf("%s", &placa_locar); 
  }
  else if(clienteLocador == true && clienteCadastrado == true){
    printf("\nCliente ja tem locacao!\n");
    return;
  }
  else{
    printf("\nErro na locacao. Cliente nao cadastrado!\n");
    return;
  }

  for (int i = 0; i < 50; i++){
    if (strcmp(placa_locar, veic[i].placa) == 0){
      veiculoCadastrado = true;
      strcpy (modelo, veic[i].modelo);
      tipo = veic[i].tipo;
      quilometragem = veic[i].quilometragem;
    }
  }

  for (int i = 0; i < 50; i++)
    if (strcmp(placa_locar, loca[i].placa_aux) == 0)
      veiculoLocado = true;

  if (veiculoCadastrado == true && veiculoLocado == false){
    for (int i = 0; i < 50; i++) {
      if (loca[i].cpf_aux == 0){
        loca[i].cpf_aux = cpf_locar;
        strcpy (loca[i].placa_aux, placa_locar);
        strcpy (loca[i].modelo_aux, modelo);
        strcpy (loca[i].nome_aux, nome);
        loca[i].tipo_aux = tipo;
        data_hora_atual(dia, mes, ano);
        loca[i].dia = dia;
        loca[i].mes = mes;
        loca[i].ano = ano;

        break;
      }
    }
    printf ("\nLocacao concedida!\n");

    printf ("\nNome: %s\n", nome);
    printf ("Modelo: %s\n", modelo);

    if (tipo == 'C'){
      printf ("Tipo: Carro\n");
    }
    else{
      printf ("Tipo: Moto\n");
    }

    printf ("Quilometragem: %d KM\n", quilometragem);
    printf ("Data de Locacao: %d/%d/%d\n\n", dia, mes, ano);
  }
  else if(veiculoCadastrado == true && veiculoLocado == true){
    printf("\nErro na locacao. Veiculo ja locado!\n");
    return;
  }
  else{
    printf("Erro na locacao. Veiculo nao encontrado! ");
    return;
  }

  clienteLocador = false;
  clienteCadastrado = false;
  veiculoLocado = false;
  veiculoCadastrado = false;

}

void devolver_veiculo (Veiculos veic[], Clientes clie[], Locacao loca []){


  bool clienteLocador = false;
  bool clienteCadastrado = false;
  bool dataInvalida = false;
  long long cpf_devolucao;
  int quilometragem_aux = 0, quilometragem_rodada = 0, quilometragem_total = 0;
  float valor_locacao, valor_quilometro, valor_dias, valor_total;
  char modelo[31], nome[51], placa[8];
  int dia_loca, mes_loca, ano_loca; 
  int dia_loca_aux, mes_loca_aux, ano_loca_aux, validador;
  int dia_devol, mes_devol, ano_devol; 
  int dias_totais = 0, dias_locados = 0; 
  int pv;

    do{
      clienteCadastrado = false;

      printf ("CPF: ");
      scanf ("%lld", &cpf_devolucao);

      for (int i = 0; i < 50; i++){ 
        if (cpf_devolucao == clie[i].cpf){
          clienteCadastrado = true;
          strcpy (nome, clie[i].nome);
        }
      }

      for (int i = 0; i < 50; i++){
        for (int j = 0; j < 50; j++){
          if (clienteCadastrado){
            if (cpf_devolucao == loca[i].cpf_aux){
              clienteLocador = true;

              if (strcmpi (loca[i].placa_aux, veic[j].placa) == 0){
                strcpy (placa, veic[j].placa);
                strcpy (modelo, veic[j].modelo);
                quilometragem_total = veic[j].quilometragem;
                valor_locacao = veic[j].valor_locacao;
                pv = j;
                dia_loca = loca[i].dia; 
                mes_loca = loca[i].mes; 
                ano_loca = loca[i].ano; 
                dia_loca_aux = dia_loca;
                mes_loca_aux = mes_loca;
                ano_loca_aux = ano_loca;
                loca[i].placa_aux[0] = '\0';
                loca[i].cpf_aux = 0;
              }
            }
          }
        }
      }

      if (clienteCadastrado == false){
        printf ("\nErro na devolucao. Cliente nao cadastrado!\n");
      }
      if ( clienteCadastrado && clienteLocador == false){
        printf ("\nErro na devolucao. Cliente nao possui locacao!\n");

      }
    } while (clienteLocador == false);

    clienteLocador = false;

    do {
      dataInvalida = false;
      dias_locados = 0;
      dias_totais = 0;

    printf("Data de Devolucao (DD MM AAAA): ");
    scanf("%d %d %d", &dia_devol, &mes_devol, &ano_devol);

    validador = numero_dias_mes(mes_devol, ano_devol);

    if (validador == -1 || validador < dia_devol) {
      dataInvalida = true;
    }

    for (int i = 0; i < ano_loca; i++){
      if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0))
        dias_totais += 366;
      else
       dias_totais += 365;
    }

    for (int i = 1; i < mes_loca; i++){
      if(i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
        dias_totais += 31;
      else if(i == 4 || i == 6 || i == 9 || i == 11)
        dias_totais += 30;
      else if((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0))
        dias_totais += 29;
      else
        dias_totais += 28;
    }

    dias_totais += dia_loca; 

    for (int i = 0; i < ano_devol; i++){
      if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0))
        dias_locados += 366;
      else
       dias_locados += 365;
    }

    for (int i = 1; i < mes_devol; i++){
      if(i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
        dias_locados += 31;
      else if(i == 4 || i == 6 || i == 9 || i == 11)
        dias_locados += 30;
      else if((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0))
        dias_locados += 29;
      else
        dias_locados += 28;
    }

    dias_locados += dia_devol; 
    dias_locados = dias_locados - dias_totais; 


    if (dias_locados < 0){
      printf ("\nErro na devolucao. Data da devolucao anterior a data da locacao %d/%d/%d\n", dia_loca_aux, mes_loca_aux, ano_loca_aux);
    }
    if (dataInvalida){
      printf ("\nErro. Data invalida!\n");
    }

   }while (dias_locados < 0 || dataInvalida);


    do {
      printf ("Quilometragem atual: ");
      scanf ("%d", &quilometragem_aux);

      if (quilometragem_aux <= quilometragem_total){
        printf ("\nErro na devolucao. Quilometragem menor que a quilometragem da locacao %d\n", quilometragem_total);
      }
    } while (quilometragem_aux <= quilometragem_total);

    quilometragem_rodada = quilometragem_aux - quilometragem_total;
    quilometragem_total = quilometragem_aux;
    veic[pv].quilometragem = quilometragem_total;

    valor_quilometro = quilometragem_rodada * 1.50;
    valor_dias = dias_locados * valor_locacao;
    valor_total = valor_dias + valor_quilometro;


    printf ("\nNome: %s\n", nome);
    printf ("Placa: %s\n", placa);
    printf ("Modelo: %s\n", modelo);
    printf ("Data de Locacao: %d %d %d\n", dia_loca_aux, mes_loca_aux, ano_loca_aux);
    printf ("Quilometragem: %d KM\n", quilometragem_total);

    printf ("\nDevolucao realizada com sucesso:\n");
    printf("No. de dias locado: %d\n", dias_locados);
    printf ("Quilometragem rodada: %d KM\n", quilometragem_rodada);
    printf ("Valor a pagar: R$ %.2f + R$ %.2f = R$ %.2f\n\n", valor_dias, valor_quilometro, valor_total);

}

void listar_locacoes (Locacao loca[]){
  Locacao aux;

  for (int i = 0; i < 50; i++){
    for (int j = i + 1; j < 50; j++){
      if (loca[i].cpf_aux > loca[j].cpf_aux){
        aux = loca[i];
        loca[i] = loca[j];
        loca[j] = aux;
      }
    }
  }

  puts ("-----------------------------------------------------------------------------");
  printf (" CPF          NOME                           PLACA     MODELO      DATA\n");
  puts ("-----------------------------------------------------------------------------");
  for (int i = 0; i < 50; i++) {
    if (loca[i].cpf_aux != 0) {
      printf ("%lld  %-30s %s    %-10s %d/%d/%d\n", loca[i].cpf_aux, loca[i].nome_aux, loca[i].placa_aux, loca[i].modelo_aux, loca[i].dia, loca[i].mes, loca[i].ano);
    }
  }
  puts ("-----------------------------------------------------------------------------");
}

int locacao_devolucao (Clientes clie[], Veiculos veic[], Locacao loca[]){

  int menuLocacao;

  puts ("\nMenu da Locacao/Devolucao de Veiculos");
  printf (" 1-Locar veiculo\n 2-Devolver veiculo\n 3-Listar locacoes\n 4-Voltar\n");
  scanf ("%d", &menuLocacao);

  switch (menuLocacao) {
    case 1: locar_veiculo(clie, veic, loca);
      break;
    case 2: devolver_veiculo(veic, clie, loca);
      break;
    case 3: listar_locacoes(loca);
      break;
    case 4: return 0;
    default: printf("Comando invalido\n");
      break;
  }
  return 0;
}

int menu_principal (Clientes clie[], Veiculos veic[], Locacao loca[]){
  int menuPrincipal;

  puts ("\nMenu Principal");
  printf (" 1-Cadastro de clientes\n 2-Cadastro de veiculos\n 3-Locacao/devolucao de veiculos\n 4-Fim\n");
  scanf ("%d", &menuPrincipal);

  switch (menuPrincipal){
    case 1: cadastro_cliente(clie, loca);
      break;
    case 2: cadastro_veiculo(veic, loca);
      break;
    case 3: locacao_devolucao(clie, veic, loca);
      break;
    case 4: return 0; 
    default: printf("Comando invalido\n");
      break;
  }

  return menu_principal(clie, veic, loca);
}

int main (){
  struct Clientes clie[50]; 
  struct Veiculos veic[50]; 
  struct Locacao loca[50];

  for (int i = 0; i < 50; i++) {
    clie[i].cpf = 0;
    clie[i].nome[0] = '\0';
    veic[i].placa[0] = '\0';
    veic[i].modelo[0] = '\0';
    loca[i].placa_aux[0] = '\0';
    loca[i].cpf_aux = 0;
  }

  menu_principal(clie, veic, loca);
}
