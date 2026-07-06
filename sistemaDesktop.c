#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define desconto 0.9
#define TF 10

//Structs
typedef struct{
	int id;
	bool assinatura;
	char nome[50], cpf[20], email[30], telefone[20], endereco[100], plano[15];
	char razaoSocial[50], nomeFantasia[50], cnpj[20];	//para PJ
	char tipoPessoa[30];
}Socios;

typedef struct{
	int id;
	char razaoSocial[50], nomeFantasia[50], cnpj[20], email[30], telefone[20], endereco[100];
}Fornecedores;

typedef struct{
	int quantidade, id;
	float preco;
	char nome[50], descricao[100], marca[50], categoria[50];
}Produtos;

typedef struct{
	int id;
	char nome[50], descricao[100];
}Marcas;

typedef struct{
	int idPedido, idSocio, idProdutos[TF], quantidades[TF], totalProdutos;
	float valorTotal;
	char opcaoEntrega[30], nomeProdutos[TF][50], nomeSocio[50];
}Pedidos;

typedef struct{
	int id;
	char nome[50], descricao[100];
}Categorias;

//Cabeçalhos
void menuPrincipal();
void menuGerenciar();
void menuClube();
void menuPedido();
void menuRelatorios();

//Submenus de CRUD Gerais
void sociosCRUD();
void fornecedoresCRUD();
void produtosCRUD();
void marcasCRUD();
void categoriasCRUD();

//FUNÇÕES DE VALIDAÇÃO
int validarSocios();
int validarFornecedores();
int validarProdutos();
int validarMarcas();

//Submenu CRUD Socios
void cadastrarSocios();
void alterarSocios();
void buscarSocios();
void excluirSocios();

//Submenu CRUD Fornecedores
void cadastrarFornecedores();
void alterarFornecedores();
void buscarFornecedores();
void excluirFornecedores();

//Submenu CRUD Produtos
void cadastrarProdutos();
void alterarProdutos();
void buscarProdutos();
void excluirProdutos();

//Submenu CRUD Marcas
void cadastrarMarcas();
void alterarMarcas();
void buscarMarcas();
void excluirMarcas();

//Submenu CRUD Categorias
void cadastrarCategorias();
void alterarCategorias();
void buscarCategorias();
void excluirCategorias();

//Submenus do Clube
void assinarClube();
void renovarClube();

//Submenus Desconto/Promocoes
void aplicarDescontos();
void aplicarPromocoes();

//Submenus Relatorios
void relatorioSocios();
void relatorioPedidos();
void relatorioFornecedores();
void relatorioProdutos();
void relatorioCategorias();
void relatorioMarcas();

//Relatórios de Socios
void exibirSocios();
void sociosComAssinatura();
void sociosSemAssinatura();
void idSocios();
void filtroSocios();

//Relatórios de Pedidos
void exibirPedidos();
void filtroPedidos();

//Relatórios de Fornecedores
void exibirFornecedores();
void contatoFornecedores();
void idFornecedores();

//Relatórios de Produtos
void exibirProdutos();
void idProdutos();
void estoqueBaixo();
void semEstoque();
void tabelaPrecos();
void filtroProdutos();
void filtroPorMarca();	

//Relatórios de Categorias
void exibirCategorias();
void idCategorias();
void ordenarCategorias();

//Relatórios de Marcas
void exibirMarcas();
void idMarcas();
void ordenarMarcas();

//Leitura de String, limpando o buffer
void lerString(char texto[], int tamanho){
	fgets(texto, tamanho, stdin);
	texto[strcspn(texto, "\n")] = '\0';
}

int main() {
	int opcao;
	srand(time(NULL));
	
	menuPrincipal();
	printf("\nEscolha uma opcao: ");
	scanf("%d", &opcao);
	system("cls");
	
	while (opcao != 5) {
		switch (opcao) {
			case 1: menuGerenciar(); break;
			case 2: menuClube(); break;
			case 3: menuPedido(); break;
			case 4: menuRelatorios(); break;
			default: printf("\nOpcao invalida."); break;
		}
		
		printf("\n");
		system("pause");
		system("cls");
		
		//sai lido
		menuPrincipal();
		printf("\nEscolha uma opcao: ");
		scanf("%d", &opcao);
		system("cls");
	}
}

void menuPrincipal() {
	printf("MENU PRINCIPAL\n");
	printf("\n1 - Gerenciar");
	printf("\n2 - Assinar/Renovar Clube");
	printf("\n3 - Efetuar Pedido");
	printf("\n4 - Relatorios");
	printf("\n5 - Sair");
}

//OPÇÃO 1 - GERENCIAR
void menuGerenciar() {
	int opcao;
	
	printf("MENU DE GERENCIAMENTO\n");
	printf("\n1 - Gerenciar Socios");
	printf("\n2 - Gerenciar Fornecedores");
	printf("\n3 - Gerenciar Produtos");
	printf("\n4 - Gerenciar Marcas");
	printf("\n5 - Gerenciar Categorias");
	printf("\n6 - Retornar ao Menu Principal");
	printf("\nEscolha uma opcao: ");
	scanf("%d", &opcao);
	system("cls");
	
	while (opcao != 6) {
		switch (opcao) {
			case 1: sociosCRUD(); break;
			case 2: fornecedoresCRUD(); break;
			case 3: produtosCRUD(); break;	
			case 4: marcasCRUD(); break;	
			case 5: categoriasCRUD(); break;	
			default: printf("\nOpcao invalida."); break;
		}
		
		printf("\n");
		system("pause");
		system("cls");
		
		//sai lido
		printf("MENU DE GERENCIAMENTO\n");
		printf("\n1 - Gerenciar Socios");
		printf("\n2 - Gerenciar Fornecedores");
		printf("\n3 - Gerenciar Produtos");
		printf("\n4 - Gerenciar Marcas");
		printf("\n5 - Gerenciar Categorias");
		printf("\n6 - Retornar ao Menu Principal");
		printf("\nEscolha uma opcao: ");
		scanf("%d", &opcao);
	}
}

//SÓCIOS
void sociosCRUD(){
	int opcao;
	
	printf("MENU DE SOCIOS\n");
	printf("\n1 - Cadastrar Socios");
	printf("\n2 - Alterar Socios");
	printf("\n3 - Buscar Socios");
	printf("\n4 - Excluir Socios");
	printf("\n5 - Retornar ao Menu de Gerenciamento");
	printf("\nEscolha uma opcao: ");
	scanf("%d", &opcao);
	
	while (opcao != 5){
		switch(opcao){
			case 1: cadastrarSocios(); break;
			case 2: alterarSocios(); break;
			case 3: buscarSocios(); break;
			case 4: excluirSocios(); break;
			default: printf("Opcao invalida."); break;
		}
		printf("\n");
		system("pause");
		system("cls");
		
		//sai lido
		printf("MENU DE SOCIOS\n");
		printf("\n1 - Cadastrar Socios");
		printf("\n2 - Alterar Socios");
		printf("\n3 - Buscar Socios");
		printf("\n4 - Excluir Socios");
		printf("\n5 - Retornar ao Menu de Gerenciamento");
		printf("\nEscolha uma opcao: ");
		scanf("%d", &opcao);
	}
}

void cadastrarSocios(){
	Socios socio;
	int pos, tipo;
	char resposta[8], respostaPlano[8];
	FILE *fp = fopen("cadastroSocios.bin", "ab+");
	if (fp == NULL){
		printf("Erro ao abrir ou criar arquivo.");
		return;
	}
	
	printf("Deseja cadastrar socio? (Sim/Nao): "); fflush(stdin);
	gets(resposta);
	
	while (stricmp(resposta, "sim") == 0) {
		printf("\n1 - Pessoa Fisica");
		printf("\n2 - Pessoa Juridica");
		printf("\nEscolha uma opcao: ");
		scanf("%d", &tipo);
		
		switch(tipo){
			case 1:
				printf("ID do Socio: ");
				scanf("%d", &socio.id);
				getchar();
				pos = validarSocios(fp, socio.id);
				if (pos == -1){
					printf("Nome do socio: ");
					lerString(socio.nome, sizeof(socio.nome));
					
					printf("CPF: ");
					lerString(socio.cpf, sizeof(socio.cpf));
					
					printf("Email: ");
					lerString(socio.email, sizeof(socio.email));
					
					printf("Telefone: ");
					lerString(socio.telefone, sizeof(socio.telefone));
					
					printf("Endereco: ");
					lerString(socio.endereco, sizeof(socio.endereco));
					
					socio.assinatura = false;
					strcpy(socio.plano, "");
					strcpy(socio.tipoPessoa, "Pessoa Fisica");
					fwrite(&socio, sizeof(Socios), 1, fp); fflush(fp);
					
					printf("Deseja assinar o clube? (Sim/Nao): "); fflush(stdin);
					gets(respostaPlano);
					if (stricmp(respostaPlano, "sim") == 0) assinarClube(socio.id);
					else printf("Dados cadastrados com sucesso.\n");
				}
				else printf("Esse ID ja foi cadastrado. Insira um ID diferente.\n");
				break;
				
			case 2:
				printf("ID do Socio: ");
				scanf("%d", &socio.id);
				getchar();
				pos = validarSocios(fp, socio.id);
				if (pos == -1){
					printf("Razao Social: ");
					lerString(socio.razaoSocial, sizeof(socio.razaoSocial));
					
					printf("Nome Fantasia: ");
					lerString(socio.nomeFantasia, sizeof(socio.nomeFantasia));
					
					printf("CNPJ: ");
					lerString(socio.cnpj, sizeof(socio.cnpj));
					
					printf("Email: ");
					lerString(socio.email, sizeof(socio.email));
					
					printf("Telefone: ");
					lerString(socio.telefone, sizeof(socio.telefone));
					
					printf("Endereco: ");
					lerString(socio.endereco, sizeof(socio.endereco));
					
					socio.assinatura = false;
					strcpy(socio.plano, "");
					strcpy(socio.tipoPessoa, "Pessoa Juridica");
					fwrite(&socio, sizeof(Socios), 1, fp); fflush(fp);
					
					printf("Deseja assinar o clube? (Sim/Nao): "); fflush(stdin);
					gets(respostaPlano);
					
					if (stricmp(respostaPlano, "sim") == 0) assinarClube(socio.id);
					else printf("Dados cadastrados com sucesso.\n");
				}
				else printf("Esse ID ja foi cadastrado. Insira um ID diferente.\n");
				break;
				
			default: printf("\nOpcao invalida."); break;
		}
		printf("Deseja cadastrar novo socio? (Sim/Nao): "); fflush(stdin);
		gets(resposta);
		system("cls");
	}
	fclose(fp);
}

void alterarSocios(){
	Socios socio;
	int pos, opcao;
	char resposta[8];
	FILE *fp = fopen("cadastroSocios.bin", "rb+");
	if (fp == NULL){
		printf("Erro. Verifique se algum socio ja foi cadastrado.");
		return;
	}
	printf("Deseja alterar Socio? (Sim/Nao): "); fflush(stdin);
	gets(resposta);
	while (stricmp(resposta, "sim") == 0){
		printf("Insira o ID do Socio: ");
		scanf("%d", &socio.id);
		pos = validarSocios(fp, socio.id);
		if (pos == -1){
			printf("ID nao encontrado.\n");
		}
		
		else{
			fseek(fp, pos, 0);
			fread(&socio, sizeof(Socios), 1, fp);
			
			printf("\n----SOCIO----\n");
			printf("\nID: %d\n", socio.id);
			if (stricmp(socio.tipoPessoa, "Pessoa Fisica") == 0){
				printf("Nome: %s\n", socio.nome);
			}
			else if(stricmp(socio.tipoPessoa, "Pessoa Juridica") == 0){
				printf("Nome Fantasia: %s\n", socio.nomeFantasia);
			}
			printf("Telefone: %s\n", socio.telefone);
			printf("Endereco: %s\n", socio.endereco);
			printf("\n-------------");
			printf("\n\nALTERAR");
			printf("\n1 - Telefone");
			printf("\n2 - Endereco");
			printf("\nEscolha uma opcao: ");
			scanf("%d", &opcao);
			getchar();
			
			switch(opcao){
				case 1:
					printf("\nNovo telefone: ");
					fgets(socio.telefone, sizeof(socio.telefone), stdin);
					fseek(fp, pos, 0);
					fwrite(&socio, sizeof(Socios), 1, fp);
					printf("\nRegistro atualizado.");
					break;
					
				case 2:
					printf("\nNovo endereco: ");
					fgets(socio.endereco, sizeof(socio.endereco), stdin);
					fseek(fp, pos, 0);
					fwrite(&socio, sizeof(Socios), 1, fp);
					printf("\nRegistro atualizado.");
					break;
					
				default: printf("Opcao invalida.\n"); break;
			}		
		}
		//sai lido
		printf("\nDeseja alterar novo Socio? (Sim/Nao): "); fflush(stdin);
		gets(resposta);
	}
	fclose(fp);
}

void buscarSocios(){
	Socios socio;
	int id, pos;
	FILE *fp = fopen("cadastroSocios.bin", "rb");
	if (fp == NULL){
		printf("Erro. Verifique se algum socio ja foi cadastrado.");
		return;
	} 
	
	printf("Digite o ID do Socio que deseja buscar: ");
	scanf("%d", &id);
	pos = validarSocios(fp, id);
	if (pos == -1) printf("Socio nao encontrado.\n");
	else{
		fseek(fp, pos, 0);
		fread(&socio, sizeof(Socios), 1, fp);
		printf("ID: %d\n", socio.id);
		if (stricmp(socio.tipoPessoa, "Pessoa Fisica") == 0){
			printf("Nome: %s\n", socio.nome);
			printf("CPF: %s\n", socio.cpf);
		}
		else if(stricmp(socio.tipoPessoa, "Pessoa Juridica") == 0){
			printf("Nome Fantasia: %s\n", socio.nomeFantasia);
			printf("Razao Social: %s\n", socio.razaoSocial);
			printf("CNPJ: %s\n", socio.cnpj);
		}
		printf("Email: %s\n", socio.email);
		printf("Telefone: %s\n", socio.telefone);
		printf("Endereco: %s\n", socio.endereco);
		printf("Plano: %s\n", socio.plano);
	}
	fclose(fp);
}

void excluirSocios(){
	FILE *fp, *temporario;
	Socios socio;
	int pos, id;
	char resposta[8];
	fp = fopen("cadastroSocios.bin", "rb");
	if (fp == NULL){
		printf("Erro. Verifique se algum socio ja foi cadastrado.");
		return;
	} 
	
	printf("Digite o ID do Socio que deseja excluir: ");
	scanf("%d", &id);
	pos = validarSocios(fp, id);
	if (pos == -1) printf("ID nao encontrado.\n");
	else{
		fseek(fp, pos, 0);
		fread(&socio, sizeof(Socios), 1, fp);
		
		printf("\n----SOCIO----");
		printf("\nID: %d\n", socio.id);
		if (stricmp(socio.tipoPessoa, "Pessoa Fisica") == 0){
			printf("Nome do Socio: %s\n", socio.nome);
			printf("CPF: %s\n", socio.cpf);
		}
		else if(stricmp(socio.tipoPessoa, "Pessoa Juridica") == 0){
			printf("Nome Fantasia: %s\n", socio.nomeFantasia);
			printf("Razao Social: %s\n", socio.razaoSocial);
			printf("CNPJ: %s\n", socio.cnpj);
		}
		printf("Email: %s\n", socio.email);
		printf("Telefone: %s\n", socio.telefone);
		printf("Endereco: %s\n", socio.endereco);
		printf("Plano: %s\n", socio.plano);
		printf("\n-------------");
		
		printf("\nTem certeza que deseja excluir esse Socio? (Sim/Nao): "); fflush(stdin);
		gets(resposta);
		if (stricmp(resposta, "sim") == 0){
			temporario = fopen("temporario.bin", "wb");
			rewind(fp);
			while(fread(&socio, sizeof(Socios), 1, fp) == 1){
				if (id != socio.id){
					fwrite(&socio, sizeof(Socios), 1, temporario);
				}
			}
			fclose(temporario);
			fclose(fp);
			remove("cadastroSocios.bin");
			rename("temporario.bin", "cadastroSocios.bin");
			printf("\nSocio excluido com sucesso."); 
		}
	}
}

int validarSocios(FILE *fp, int id){
	Socios socio;
	rewind(fp);
	
	fread(&socio, sizeof(Socios), 1, fp);
	while (!feof(fp) && id != socio.id){
		fread(&socio, sizeof(Socios), 1, fp);
	}
	if (!feof(fp)){
		return (ftell(fp) - sizeof(Socios));
	} 
	else {
		return -1;
	}
}

//FORNECEDORES
void fornecedoresCRUD(){
	int opcao;
	
	printf("MENU DE FORNECEDORES \n");
	printf("\n1 - Cadastrar Fornecedores");
	printf("\n2 - Alterar Fornecedores");
	printf("\n3 - Buscar Fornecedores");
	printf("\n4 - Excluir Fornecedores");
	printf("\n5 - Retornar ao Menu de Gerenciamento");
	printf("\nEscolha uma opcao: ");
	scanf("%d", &opcao);
	
	while(opcao != 5){
		switch(opcao){
			case 1: cadastrarFornecedores(); break;	
			case 2: alterarFornecedores(); break;
			case 3: buscarFornecedores(); break;
			case 4: excluirFornecedores(); break;
			default: printf("Opcao invalida."); break;
		}
		printf("\n");
		system("pause");
		system("cls");
		
		//sai lido
		printf("MENU DE FORNECEDORES \n");
		printf("\n1 - Cadastrar Fornecedores");
		printf("\n2 - Alterar Fornecedores");
		printf("\n3 - Buscar Fornecedores");
		printf("\n4 - Excluir Fornecedores");
		printf("\n5 - Retornar ao Menu de Gerenciamento");
		printf("\nEscolha uma opcao: ");
		scanf("%d", &opcao);
	}
}

void cadastrarFornecedores() {
	Fornecedores fornecedor;
	int pos;
	char resposta[8];
	FILE *fp = fopen("cadastroFornecedores.bin", "ab+");
	
	if (fp == NULL){
		printf("Erro ao abrir ou criar arquivo.");
		return;
	}
	
	printf("Deseja cadastrar Fornecedor? (Sim/Nao): "); fflush(stdin);
	gets(resposta);
	
	while (stricmp(resposta, "sim") == 0) {
		printf("ID do Fornecedor: ");
		scanf("%d", &fornecedor.id);
		getchar();
		pos = validarFornecedores(fp, fornecedor.id);
		if (pos == -1){
			printf("Razao Social: ");
			lerString(fornecedor.razaoSocial, sizeof(fornecedor.razaoSocial));
			
			printf("Nome Fantasia: ");
			lerString(fornecedor.nomeFantasia, sizeof(fornecedor.nomeFantasia));
			
			printf("CNPJ: ");
			lerString(fornecedor.cnpj, sizeof(fornecedor.cnpj));
			
			printf("Email: ");
			lerString(fornecedor.email, sizeof(fornecedor.email));
			
			printf("Telefone: ");
			lerString(fornecedor.telefone, sizeof(fornecedor.telefone));
			
			printf("Endereco: ");
			lerString(fornecedor.endereco, sizeof(fornecedor.endereco));
			
			fwrite(&fornecedor, sizeof(Fornecedores), 1, fp);
			printf("Dados cadastrados com sucesso.\n");	
		}
		else printf("Esse ID ja foi cadastrado. Insira um ID diferente.\n");
		
		printf("Deseja cadastrar novo Fornecedor? (Sim/Nao): "); fflush(stdin);
		gets(resposta);
		system("cls");
	}
	fclose(fp);
}

void alterarFornecedores(){
	Fornecedores fornecedor;
	int pos, opcao;
	char resposta[8];
	FILE *fp = fopen("cadastroFornecedores.bin", "rb+");
	if (fp == NULL){
		printf("Erro. Verifique se algum fornecedor ja foi cadastrado.");
		return;
	}
	printf("Deseja alterar Fornecedor? (Sim/Nao): "); fflush(stdin);
	gets(resposta);
	while(stricmp(resposta, "sim") == 0){
		printf("Insira o ID do Fornecedor: ");
		scanf("%d", &fornecedor.id);
		pos = validarFornecedores(fp, fornecedor.id);
		if (pos == -1){
			printf("ID nao encontrado.\n");
		}
		else{
			fseek(fp, pos, 0);
			fread(&fornecedor, sizeof(Fornecedores), 1, fp);
			
			printf("\n----FORNECEDOR----\n");
			printf("\nID: %d\n", fornecedor.id);
			printf("Nome: %s\n", fornecedor.nomeFantasia);
			printf("Email: %s\n", fornecedor.email);
			printf("Endereco: %s\n", fornecedor.endereco);
			printf("\n-------------------");
			printf("\n\nALTERAR");
			printf("\n1 - Email");
			printf("\n2 - Telefone");
			printf("\nEscolha uma opcao: ");
			scanf("%d", &opcao);
			getchar();
			
			switch(opcao){
				case 1:
					printf("\nNovo email: ");
					fgets(fornecedor.email, sizeof(fornecedor.email), stdin);
					fseek(fp, pos, 0);
					fwrite(&fornecedor, sizeof(Fornecedores), 1, fp);
					printf("\nRegistro atualizado.");
					break;
				
				case 2:
					printf("\nNovo telefone: ");
					fgets(fornecedor.telefone, sizeof(fornecedor.telefone), stdin);
					fseek(fp, pos, 0);
					fwrite(&fornecedor, sizeof(Fornecedores), 1, fp);
					printf("\nRegistro atualizado.");
					break;
					
				default:printf("Opcao invalida.\n"); break;	
			}
		}
		//sai lido
		printf("Deseja alterar novo Fornecedor? (Sim/Nao): "); fflush(stdin);
		gets(resposta);
	}
	fclose(fp);
}

void buscarFornecedores(){
	Fornecedores fornecedor;
	int id, pos;
	FILE *fp = fopen("cadastroFornecedores.bin", "rb");
	if (fp == NULL){
		printf("Erro. Verifique se algum fornecedor ja foi cadastrado.");
		return;
	} 
	
	printf("ID do Fornecedor: ");
	scanf("%d", &id);
	pos = validarFornecedores(fp, id);
	if (pos == -1) printf("Fornecedor nao encontrado.");
	else{
		fseek(fp, pos, 0);
		fread(&fornecedor, sizeof(Fornecedores), 1, fp);
		printf("\nID: %d", fornecedor.id);
		printf("\nRazao Social: %s", fornecedor.razaoSocial);
		printf("\nNome Fantasia: %s", fornecedor.nomeFantasia);
		printf("\nCNPJ: %s", fornecedor.cnpj);
		printf("\nEmail: %s", fornecedor.email);
		printf("\nTelefone: %s", fornecedor.telefone);
		printf("\nEndereco: %s", fornecedor.endereco);
	}
	fclose(fp);
}

void excluirFornecedores(){
	FILE *fp, *temporario;
	Fornecedores fornecedor;
	int pos, id;
	char resposta[8];
	fp = fopen("cadastroFornecedores.bin", "rb");
	if (fp == NULL){
		printf("Erro. Verifique se algum fornecedor ja foi cadastrado.");
		return;
	} 
	
	printf("Digite o ID do Fornecedor que deseja excluir: ");
	scanf("%d", &id);
	pos = validarFornecedores(fp, id);
	if (pos == -1) printf("ID nao encontrado.\n");
	else{
		fseek(fp, pos, 0);
		fread(&fornecedor, sizeof(Fornecedores), 1, fp);
		
		printf("\n----FORNECEDOR----\n");
		printf("\nID: %d\n", fornecedor.id);
		printf("Razao Social: %s\n", fornecedor.razaoSocial);
		printf("Nome Fantasia: %s\n", fornecedor.nomeFantasia);
		printf("CNPJ: %s\n", fornecedor.cnpj);
		printf("Email: %s\n", fornecedor.email);
		printf("Telefone: %s\n", fornecedor.telefone);
		printf("Endereco: %s\n", fornecedor.endereco);
		printf("\n--------------------");
		printf("\nTem certeza que deseja excluir esse Fornecedor? (Sim/Nao): "); fflush(stdin);
		gets(resposta);
		if (stricmp(resposta, "sim") == 0){
			temporario = fopen("temporario.bin", "wb");
			rewind(fp);
			while(fread(&fornecedor, sizeof(Fornecedores), 1, fp) == 1){
				if (id != fornecedor.id){
					fwrite(&fornecedor, sizeof(Fornecedores), 1, temporario);
				}
			}
			fclose(temporario);
			fclose(fp);
			remove("cadastroFornecedores.bin");
			rename("temporario.bin", "cadastroFornecedores.bin");
			printf("\nFornecedor excluido com sucesso.");
		}
	}
}

int validarFornecedores(FILE *fp, int id){
	Fornecedores fornecedor;
	rewind(fp);
	
	fread(&fornecedor, sizeof(Fornecedores), 1, fp);
	while (!feof(fp) && id != fornecedor.id){
		fread(&fornecedor, sizeof(Fornecedores), 1, fp);
	}
	if (!feof(fp)){
		return (ftell(fp) - sizeof(Fornecedores));
	}
	else{
		return -1;
	}
}

//PRODUTOS
void produtosCRUD(){
	int opcao;
	
	printf("MENU DE PRODUTOS\n");
	printf("\n1 - Cadastrar Produtos");
	printf("\n2 - Alterar Produtos");
	printf("\n3 - Buscar Produtos");
	printf("\n4 - Excluir Produtos");
	printf("\n5 - Retornar ao Menu de Gerenciamento");
	printf("\nEscolha uma opcao: ");
	scanf("%d", &opcao);
	
	while(opcao != 5){
		switch(opcao){
			case 1: cadastrarProdutos(); break;
			case 2: alterarProdutos(); break;	
			case 3: buscarProdutos(); break;		
			case 4: excluirProdutos(); break;
			default: printf("Opcao invalida."); break;
		}
		printf("\n");
		system("pause");
		system("cls");
		
		//sai lido
		printf("MENU DE PRODUTOS\n");
		printf("\n1 - Cadastrar Produtos");
		printf("\n2 - Alterar Produtos");
		printf("\n3 - Buscar Produtos");
		printf("\n4 - Excluir Produtos");
		printf("\n5 - Retornar ao Menu de Gerenciamento");
		printf("\nEscolha uma opcao: ");
		scanf("%d", &opcao);
	}
}

void cadastrarProdutos() {
	Produtos produto;
	int pos;
	char resposta[8];
	FILE *fp = fopen("cadastroProdutos.bin", "ab+");
	
	if (fp == NULL) {
		printf("Erro ao abrir ou criar arquivo.");
		return;
	}
	
	printf("Deseja cadastrar Produto? (Sim/Nao): "); fflush(stdin);
	gets(resposta);
	
	while(stricmp(resposta, "sim") == 0){
		printf("ID: ");
		scanf("%d", &produto.id);
		getchar();
		pos = validarProdutos(fp, produto.id);
		if (pos == -1){
			printf("Nome do produto: ");
			lerString(produto.nome, sizeof(produto.nome));
			
			printf("Descricao do produto: ");
			lerString(produto.descricao, sizeof(produto.descricao));
			
			printf("Quantidade: ");
			scanf("%d", &produto.quantidade);
			
			printf("Preco: ");
			scanf("%f", &produto.preco); getchar();
			
			/*printf("\nPreco lido: %.2f\n", produto.preco);

			int c;
			while ((c = getchar()) != '\n' && c != EOF)
			{
			    printf("Restou no buffer: %c\n", c);
			}
			*/
			
			
			printf("Categoria: ");
			lerString(produto.categoria, sizeof(produto.categoria));
			
			printf("Marca: ");
			lerString(produto.marca, sizeof(produto.marca));
			
			fwrite(&produto, sizeof(Produtos), 1, fp);
			printf("Dados cadastrados com sucesso.\n");
		}
		else printf("Esse ID ja foi cadastrado. Insira um ID diferente.\n");
		
		printf("Deseja cadastrar novo Produto? (Sim/Nao): "); fflush(stdin);
		gets(resposta);
		system("cls");
	}
	fclose(fp);
}

void alterarProdutos(){
	Produtos produto;
	int pos, opcao;
	char resposta[8];
	FILE *fp = fopen("cadastroProdutos.bin", "rb+");
	if (fp == NULL){
		printf("Erro. Verifique se algum produto ja foi cadastrado.");
		return;
	}
	printf("Deseja alterar Produto? (Sim/Nao): "); fflush(stdin);
	gets(resposta);
	while (stricmp(resposta, "sim") == 0){
		printf("Insira o ID do Produto: ");
		scanf("%d", &produto.id);
		pos = validarProdutos(fp, produto.id);
		if (pos == -1){
			printf("ID nao encontrado.\n");
		}
		else{
			fseek(fp, pos, 0);
			fread(&produto, sizeof(Produtos), 1, fp);
			
			printf("\n----PRODUTO----");
			printf("\nID: %d\n", produto.id);
			printf("Nome: %s\n", produto.nome);
			printf("Quantidade: %d\n", produto.quantidade);
			printf("Preco: %.2f\n", produto.preco);
			printf("------------------");
			printf("\n\nALTERAR");
			printf("\n1 - Quantidade");
			printf("\n2 - Preco");
			printf("\nEscolha uma opcao: ");
			scanf("%d", &opcao);
			
			switch(opcao){
				case 1:
					printf("\nNova quantidade: ");
					scanf("%d", &produto.quantidade);
					fseek(fp, pos, 0);
					fwrite(&produto, sizeof(Produtos), 1, fp);
					printf("\nRegistro atualizado.");
					break;
				
				case 2:
					printf("\nNovo preco: ");
					scanf("%f", &produto.preco);
					fseek(fp, pos, 0);
					fwrite(&produto, sizeof(Produtos), 1, fp);
					printf("\nRegistro atualizado.");
					break;
					
				default: printf("Opcao invalida.\n"); break;
			}
		}
		//sai lido
		printf("Deseja alterar novo Produto? (Sim/Nao): "); fflush(stdin);
		gets(resposta);
	}
	fclose(fp);
}

void buscarProdutos(){
	Produtos produto;
	int pos, id;
	FILE *fp = fopen("cadastroProdutos.bin", "rb");
	if (fp == NULL){
		printf("Erro. Verifique se algum produto ja foi cadastrado.");
		return;
	} 
	
	printf("Digite o ID do Produto que deseja buscar: ");
	scanf("%d", &id);
	pos = validarProdutos(fp, id);
	if (pos == -1) printf("\nID nao encontrado.");
	else{
		fseek(fp, pos, 0);
		fread(&produto, sizeof(Produtos), 1, fp);
		printf("Nome: %s\n", produto.nome);
		printf("Descricao: %s\n", produto.descricao);
		printf("Quantidade: %d", produto.quantidade);
		printf("\nPreco: %.2f\n", produto.preco);
	}
	fclose(fp);
}

void excluirProdutos(){
	FILE *fp, *temporario;
	Produtos produto;
	int pos, id;
	char resposta[8];
	fp = fopen("cadastroProdutos.bin", "rb");
	if (fp == NULL){
		printf("Erro. Verifique se algum produto ja foi cadastrado.");
		return;
	} 
	
	printf("Digite o ID do Produto que deseja excluir: ");
	scanf("%d", &id);
	pos = validarProdutos(fp, id);
	if (pos == -1) printf("ID nao encontrado.\n");
	else{
		fseek(fp, pos, 0);
		fread(&produto, sizeof(Produtos), 1, fp);
		
		printf("\n----PRODUTO----\n");
		printf("ID: %d\n", produto.id);
		printf("Nome: %s\n", produto.nome);
		printf("Descricao: %s\n", produto.descricao);
		printf("Quantidade: %d\n", produto.quantidade);
		printf("Preco: %.2f\n", produto.preco);
		printf("-------------------");
		printf("\nTem certeza que deseja excluir esse Produto? (Sim/Nao): "); fflush(stdin);
		gets(resposta);
		if (stricmp(resposta, "sim") == 0){
			temporario = fopen("temporario.bin", "wb");
			rewind(fp);
			while(fread(&produto, sizeof(Produtos), 1, fp) == 1){
				if (id != produto.id){
					fwrite(&produto, sizeof(Produtos), 1, temporario);
				}
			}
			fclose(temporario);
			fclose(fp);
			remove("cadastroProdutos.bin");
			rename("temporario.bin", "cadastroProdutos.bin");
			printf("\nProduto excluido com sucesso.");
		}
	}
}

int validarProdutos(FILE *fp, int id){
	Produtos produto;
	rewind(fp);
	
	fread(&produto, sizeof(Produtos), 1, fp);
	while (!feof(fp) && id != produto.id){
		fread(&produto, sizeof(Produtos), 1, fp);
	}
	if (!feof(fp)){
		return (ftell(fp) - sizeof(Produtos));
	}
	else{
		return -1;
	}
}

//MARCAS
void marcasCRUD(){
	int opcao;
	
	printf("MENU DE MARCAS\n");
	printf("\n1 - Cadastrar Marcas");
	printf("\n2 - Alterar Marcas");
	printf("\n3 - Buscar Marcas");
	printf("\n4 - Excluir Marcas");
	printf("\n5 - Retornar ao Menu de Gerenciamento");
	printf("\nEscolha uma opcao: ");
	scanf("%d", &opcao);
	
	while(opcao != 5){
		switch(opcao){
			case 1: cadastrarMarcas(); break;
			case 2: alterarMarcas(); break;	
			case 3: buscarMarcas();	break;	
			case 4: excluirMarcas(); break;
			default: printf("Opcao invalida."); break;
		}
		printf("\n");
		system("pause");
		system("cls");
		
		//sai lido
		printf("MENU DE MARCAS\n");
		printf("\n1 - Cadastrar Marcas");
		printf("\n2 - Alterar Marcas");
		printf("\n3 - Buscar Marcas");
		printf("\n4 - Excluir Marcas");
		printf("\n5 - Retornar ao Menu de Gerenciamento");
		printf("\nEscolha uma opcao: ");
		scanf("%d", &opcao);
	}
}

void cadastrarMarcas() {
	Marcas marca;
	int pos;
	char resposta[8];
	FILE *fp = fopen("cadastroMarcas.bin", "ab+");
	
	if (fp == NULL){
		printf("Erro ao abrir ou criar arquivo.");
		return;
	}
	
	printf("Deseja cadastrar Marca? (Sim/Nao): "); fflush(stdin);
	gets(resposta);
	
	while (stricmp(resposta, "sim") == 0){
		printf("ID da Marca: ");
		scanf("%d", &marca.id);
		getchar();
		pos = validarMarcas(fp, marca.id);
		if (pos == -1){
			printf("Nome da marca: ");
			lerString(marca.nome, sizeof(marca.nome));
			
			printf("Descricao: ");
			lerString(marca.descricao, sizeof(marca.descricao));
			
			fwrite(&marca, sizeof(Marcas), 1, fp);
			printf("Dados cadastrados com sucesso.");	
		}
		else printf("Esse ID ja foi cadastrado. Insira um ID diferente.\n");
		
		printf("Deseja cadastrar nova Marca? (Sim/Nao): "); fflush(stdin);
		gets(resposta);
		system("cls");
	}
	fclose(fp);
}

void alterarMarcas(){
	Marcas marca;
	int pos, opcao;
	char resposta[8];
	FILE *fp = fopen("cadastroMarcas.bin", "rb+");
	if (fp == NULL){
		printf("Erro. Verifique se alguma marca ja foi cadastrada.");
		return;
	} 
	
	printf("Deseja alterar Marca? (Sim/Nao): "); fflush(stdin);
	gets(resposta);
	while(stricmp(resposta, "sim") == 0){
		printf("Insira o ID da Marca: ");
		scanf("%d", &marca.id);
		pos = validarMarcas(fp, marca.id);
		if (pos == -1) printf("\nID nao encontrado.");
		else{
			fseek (fp, pos, 0);
			fread(&marca, sizeof(Marcas), 1, fp);
			
			printf("\n----MARCA----\n");
			printf("ID: %d\n", marca.id);
			printf("Nome: %s\n", marca.nome);
			printf("Descricao: %s\n", marca.descricao);
			printf("----------------\n");
			printf("\nALTERAR");
			printf("\n1 - Nome");
			printf("\n2 - Descricao");
			printf("\nEscolha uma opcao: ");
			scanf("%d", &opcao);
			getchar();
			
			switch(opcao){
				case 1:
					printf("\nNovo nome: ");
					fgets(marca.nome, sizeof(marca.nome), stdin);
					fseek(fp, pos, 0);
					fwrite(&marca, sizeof(Marcas), 1, fp);
					printf("\nRegistro atualizado.");
					break;
					
				case 2:
					printf("\nNova descricao: ");
					fgets(marca.descricao, sizeof(marca.descricao), stdin);
					fseek(fp, pos, 0);
					fwrite(&marca, sizeof(Marcas), 1, fp);
					printf("\nRegistro atualizado.");
					break;
					
				default: printf("Opcao invalida."); break;
			}
		}
		//sai lido
		printf("Deseja alterar nova Marca? (Sim/Nao): "); fflush(stdin);
		gets(resposta);
	}
	fclose(fp);
}

void buscarMarcas(){
	Marcas marca;
	int id, pos;
	FILE *fp = fopen("cadastroMarcas.bin", "rb");
	if (fp == NULL){
		printf("Erro. Verifique se alguma marca ja foi cadastrada.");
		return;
	} 
	
	printf("\nDigite o ID da Marca que deseja buscar: ");
	scanf("%d", &id);
	
	pos = validarMarcas(fp, id);
	if (pos == -1) printf("Marca nao encontrada.");
	else{
		fseek(fp, pos, 0);
		fread(&marca, sizeof(Marcas), 1, fp);
		printf("\nID: %d", marca.id);
		printf("\nNome: %s", marca.nome);
		printf("\nDescricao: %s", marca.descricao);
	}
	fclose(fp);
}

void excluirMarcas(){
	FILE *fp, *temporario;
	Marcas marca;
	int pos, id;
	char resposta[8];
	fp = fopen("cadastroMarcas.bin", "rb");
	if (fp == NULL){
		printf("Erro. Verifique se alguma marca ja foi cadastrada.");
		return;
	} 
	
	printf("Digite o ID da Marca que deseja excluir: ");
	scanf("%d", &id);
	pos = validarMarcas(fp, id);
	if (pos == -1) printf("Erro ao ler arquivo.");
	else{
		fseek(fp, pos, 0);
		fread(&marca, sizeof(Marcas), 1, fp);
		
		printf("\n----MARCA----\n");
		printf("ID: %d\n", marca.id);
		printf("Nome: %s\n", marca.nome);
		printf("Descricao: %s\n", marca.descricao);
		printf("----------------\n");
		printf("Tem certeza que deseja excluir essa Marca? (Sim/Nao): "); fflush(stdin);
		gets(resposta);
		if (stricmp(resposta, "sim") == 0){
			temporario = fopen("temporario.bin", "wb");
			rewind(fp);
			while (fread(&marca, sizeof(Marcas), 1, fp) == 1){
				if (id != marca.id){
					fwrite(&marca, sizeof(Marcas), 1, temporario);
				}
			}
			fclose(temporario);
			fclose(fp);
			remove("cadastroMarcas.bin");
			rename("temporario.bin", "cadastroMarcas.bin");
			printf("\nMarca excluida com sucesso.");
		}
	}
}

int validarMarcas(FILE *fp, int id){
	Marcas marca;
	rewind(fp);
	
	fread(&marca, sizeof(Marcas), 1, fp);
	while (!feof(fp) && id != marca.id){
		fread(&marca, sizeof(Marcas), 1, fp);
	}
	if (!feof(fp)){
		return (ftell(fp) - sizeof(Marcas));
	}
	else{
		return -1;
	}
}

//CATEGORIAS
void categoriasCRUD(){
	int opcao;
	
	printf("MENU DE CATEGORIAS\n");
	printf("\n1 - Cadastrar Categorias");
	printf("\n2 - Alterar Categorias");
	printf("\n3 - Buscar Categorias");
	printf("\n4 - Excluir Categorias");
	printf("\n5 - Retornar ao Menu de Gerenciamento");
	printf("\nEscolha uma opcao: ");
	scanf("%d", &opcao);
	
	while(opcao != 5){
		switch(opcao){
			case 1: cadastrarCategorias(); break;
			case 2: alterarCategorias(); break;
			case 3: buscarCategorias(); break;
			case 4: excluirCategorias();break;
			default: printf("Opcao invalida."); break;
		}
		printf("\n");
		system("pause");
		system("cls");
		
		//sai lido
		printf("MENU DE CATEGORIAS\n");
		printf("\n1 - Cadastrar Categorias");
		printf("\n2 - Alterar Categorias");
		printf("\n3 - Buscar Categorias");
		printf("\n4 - Excluir Categorias");
		printf("\n5 - Retornar ao Menu de Gerenciamento");
		printf("\nEscolha uma opcao: ");
		scanf("%d", &opcao);
	}
}

void cadastrarCategorias(){
	Categorias categoria;
	int pos;
	char resposta[8];
	FILE *fp = fopen("cadastroCategorias.bin", "ab+");
	if (fp == NULL) {
		printf("Erro ao criar ou abrir arquivo.");
		return;
	}
	
	printf("Deseja cadastrar Categoria? (Sim/Nao): "); fflush(stdin);
	gets(resposta);
	
	while(stricmp(resposta,"sim") == 0){
		printf("ID da Categoria: ");
		scanf("%d", &categoria.id);
		getchar();
		pos = validarCategorias(fp, categoria.id);
		if (pos == -1){
			printf("Nome da Categoria: ");
			lerString(categoria.nome, sizeof(categoria.nome));
			
			printf("Descricao: ");
			lerString(categoria.descricao, sizeof(categoria.descricao));
			
			fwrite(&categoria, sizeof(Categorias), 1, fp);
			printf("Categoria cadastrada com sucesso.\n");
		}
		else printf("\nEsse ID ja foi cadastrado. Insira um ID diferente.\n");
		
		printf("Deseja cadastrar nova Categoria? (Sim/Nao): "); fflush(stdin);
		gets (resposta);
		system("cls");
	}
	fclose(fp);
}

void alterarCategorias(){
	Categorias categoria;
	int pos, opcao;
	char resposta[8];
	FILE *fp = fopen("cadastroCategorias.bin", "rb+");
	if (fp == NULL){
		printf("Erro. Verifique se alguma categoria ja foi cadastrada.");
		return;
	} 
	
	printf("Deseja alterar Categoria? (Sim/Nao): "); fflush(stdin);
	gets(resposta);
	
	while(stricmp(resposta,"sim") == 0){
		printf("Insira o ID da Categoria: ");
		scanf("%d", &categoria.id);
		pos = validarCategorias(fp, categoria.id);
		if (pos == -1) printf("ID nao encontrado.\n");
		
		else{
			fseek(fp, pos, 0);
			fread(&categoria, sizeof(Categorias), 1, fp);
			printf("\n----CATEGORIA----\n");
			printf("ID: %d\n", categoria.id);
			printf("Nome: %s\n", categoria.nome);
			printf("Descricao: %s\n", categoria.descricao);
			printf("--------------------\n");
			printf("\nALTERAR");
			printf("\n1 - Nome");
			printf("\n2 - Descricao");
			printf("\nEscolha uma opcao: ");
			scanf("%d", &opcao);
			getchar();
			
			switch(opcao){
				case 1:
					printf("\nNovo nome: ");
					fgets(categoria.nome, sizeof(categoria.nome), stdin);
					fseek(fp, pos, 0);
					fwrite(&categoria, sizeof(Categorias), 1, fp);
					printf("\nRegistro atualizado.");
					break;
					
				case 2:
					printf("\nNova descricao: ");
					fgets(categoria.descricao, sizeof(categoria.descricao), stdin);
					fseek(fp, pos, 0);
					fwrite(&categoria, sizeof(Categorias), 1, fp);
					printf("\nRegistro atualizado.");
					break;
					
				default: printf("\nOpcao invalida."); break;
			}
		}
		//sai lido
		printf("\nDeseja alterar nova Categoria? (Sim/Nao): "); fflush(stdin);
		gets(resposta);
	}
	fclose(fp);
}

void buscarCategorias(){
	Categorias categoria;
	int id, pos;
	FILE *fp = fopen("cadastroCategorias.bin", "rb");
	if (fp == NULL){
		printf("Erro. Verifique se alguma categoria ja foi cadastrada.");
		return;
	} 
	
	printf("\nDigite o ID da Categoria que deseja buscar: ");
	scanf("%d", &id);
	pos = validarCategorias(fp, id);
	if (pos == -1) printf("Categoria nao encontrada.");
	else{
		fseek(fp, pos, 0);
		fread(&categoria, sizeof(Categorias), 1, fp);
		printf("\nID: %d", categoria.id);
		printf("\nNome: %s", categoria.nome);
		printf("\nDescricao: %s", categoria.descricao);
	}
	fclose(fp);	
}

void excluirCategorias(){
	Categorias categoria;
	int pos, id;
	char resposta[8];
	FILE *fp, *temporario;
	
	fp = fopen("cadastroCategorias.bin", "rb");
	if (fp == NULL){
		printf("Erro. Verifique se alguma categoria ja foi cadastrada.");
		return;
	} 
	
	printf("Digite o ID da Categoria que deseja excluir: ");
	scanf("%d", &id);
	pos = validarCategorias(fp, id);
	if (pos == -1) printf("Erro ao ler arquivo.");
	
	else{
		fseek(fp, pos, 0);
		fread(&categoria, sizeof(Categorias), 1, fp);
		printf("\n----CATEGORIA----\n");
		printf("ID: %d\n", categoria.id);
		printf("Nome: %s\n", categoria.nome);
		printf("Descricao: %s\n", categoria.descricao);
		printf("--------------------\n");
		printf("Tem certeza que deseja excluir essa Categoria? (Sim/Nao): "); fflush(stdin);
		gets(resposta);
		if (stricmp(resposta, "sim") == 0){
			temporario = fopen("temporario.bin", "wb");
			rewind(fp);
			while (fread(&categoria, sizeof(Categorias), 1, fp) == 1){
				if (id != categoria.id){
					fwrite(&categoria, sizeof(Categorias), 1, temporario);
				}
			}
			fclose(temporario);
			fclose(fp);
			remove("cadastroCategorias.bin");
			rename("temporario.bin", "cadastroCategorias.bin");
			printf("\nCategoria excluida com sucesso.");
		}
	}
}

int validarCategorias(FILE *fp, int id){
	Categorias categoria;
	rewind(fp);
	
	fread(&categoria, sizeof(Categorias), 1, fp);
	while (!feof(fp) && id != categoria.id){
		fread(&categoria, sizeof(Categorias), 1, fp);
	}
	if (!feof(fp)){
		return (ftell(fp) - sizeof(Categorias));
	}
	else{
		return -1;
	}
}

//OPÇÃO 2 - CLUBE
void menuClube() {
	int opcao, id;
	
	printf("MENU DO CLUBE\n");
	printf("\n1 - Assinar Clube");
	printf("\n2 - Renovar Clube");
	printf("\n3 - Retornar ao Menu Principal");
	printf("\nEscolha uma opcao: ");
	scanf("%d", &opcao);
	
	while (opcao != 3) {
		switch (opcao) {
			case 1:
				printf("\nDigite o ID do Socio que deseja assinar o clube: ");
				scanf("%d", &id);
				assinarClube(id); 
				break;	
			case 2: renovarClube(); break;	
			default: printf("\nOpcao invalida."); break;
		}
		
		printf("\n");
		system("pause");
		system("cls");
		
		//sai lido
		printf("MENU DO CLUBE\n");
		printf("\n1 - Assinar Clube");
		printf("\n2 - Renovar Clube");
		printf("\n3 - Retornar ao Menu Principal");
		printf("\nEscolha uma opcao: ");
		scanf("%d", &opcao);
	}
}

void assinarClube(int id) {
	int pos, plano;
	FILE *fp = fopen("cadastroSocios.bin", "rb+");
	if (fp == NULL) {
		printf("Erro ao ler arquivo.");
		return;
	}
	pos = validarSocios(fp, id);
	if (pos == -1) printf("ID nao encontrado.\n");
	else{
		Socios socio;
		fseek(fp, pos, 0);
		fread(&socio, sizeof(Socios), 1, fp);
		if (socio.assinatura) printf("\nEsse socio ja possui assinatura.");
		
		else{
			printf("\nPLANOS");
			printf("\n1 - Semestral");
			printf("\n2 - Anual");
			printf("\nEscolha o tipo de assinatura: ");
			scanf("%d", &plano);
			
			switch(plano){
				case 1: strcpy(socio.plano, "Semestral"); break;
				case 2: strcpy(socio.plano, "Anual"); break;
				default: 
					printf("Opcao invalida."); 
					fclose(fp);
					break;	
			}
			socio.assinatura = true;
			fseek(fp, pos, 0);
			fwrite(&socio, sizeof(Socios), 1, fp);
			printf("\nAssinatura realizada com sucesso.");
		}
	}
	fclose(fp);
}

void renovarClube() {
	int pos, id, plano;
	FILE *fp = fopen("cadastroSocios.bin", "rb+");
	if (fp == NULL) {
		printf("Erro ao ler arquivo.");
		return;
	}
	printf("Digite o ID do Socio que deseja renovar o clube: ");
	scanf("%d", &id);
	pos = validarSocios(fp, id);
	if (pos == -1) printf("\nID nao encontrado.");
	else{
		Socios socio;
		fseek(fp, pos, 0);
		fread(&socio, sizeof(Socios), 1, fp);
		if (!socio.assinatura) printf("\nEsse socio nao possui assinatura. E necessario ter uma assinatura ativa para renovar o clube.");
		else{
			printf("\nPLANOS");
			printf("\n1 - Semestral");
			printf("\n2 - Anual");
			printf("\nEscolha o tipo de assinatura: ");
			scanf("%d", &plano);
			
			switch(plano){
				case 1:strcpy(socio.plano, "Semestral"); break;
				case 2:strcpy(socio.plano, "Anual"); break;
				default: 
					printf("\nOpcao invalida.");
					fclose(fp); 
					break;
			}
			fseek(fp, pos, 0);
			fwrite(&socio, sizeof(Socios), 1, fp);
			printf("\nAssinatura renovada com sucesso.");
		}
	}
	fclose(fp);
}

//OPÇÃO 3 - PEDIDO
void menuPedido() {
	int pos, idSocio, opcao, i = 0;
	char resposta[8];
	FILE *fpSocio = fopen("cadastroSocios.bin", "rb");
	if (fpSocio == NULL) {
		printf("Erro ao ler arquivo.");
		return;
	}
	printf("Digite o ID do Socio que deseja realizar o pedido: ");
	scanf("%d", &idSocio);
	pos = validarSocios(fpSocio, idSocio);
	if(pos == -1) printf("\nSocio nao encontrado.");
	else{
		Socios socio;
		fseek(fpSocio, pos, 0);
		fread(&socio, sizeof(Socios), 1, fpSocio);
		if (!socio.assinatura) printf("\nEsse socio nao possui assinatura ativa. Compra nao autorizada.");
		else{
			int idProduto;
			Produtos produto;
			FILE *fpProduto = fopen("cadastroProdutos.bin", "rb+");
			if (fpProduto == NULL) {
				printf("Erro ao ler arquivo.");
				return;
			}
			
			FILE *fpPedido = fopen("cadastroPedidos.bin", "rb+");
			if (fpPedido == NULL){
				fpPedido = fopen("cadastroPedidos.bin", "wb+");
			}
			Pedidos pedido;
			pedido.valorTotal = 0;
			int qtdPedido, j;
			float subtotal = 0;
						
			do{
				printf("\nDigite o ID do Produto que deseja comprar: ");
				scanf("%d", &idProduto);
				pos = validarProdutos(fpProduto, idProduto);
				if (pos == -1) printf("\nProduto nao encontrado.");
				else{
					fseek(fpProduto, pos, 0);
					fread(&produto, sizeof(Produtos), 1, fpProduto);
					printf("\nProduto encontrado.");
					printf("\n%s", produto.nome);
					printf("\nPreco original: %.2f\n", produto.preco);
					printf("\nPreco com desconto do Clube: %.2f\n", produto.preco * desconto);
					printf("\nInsira a quantidade desejada: ");
					scanf("%d", &qtdPedido);
					
					if (produto.quantidade >= qtdPedido){
						subtotal = qtdPedido * produto.preco * desconto;
						printf("\nValor: %.2f\n", subtotal);
						printf("\nProduto adicionado no carrinho.");
						
						//atualiza o estoque
						produto.quantidade -= qtdPedido;
						fseek(fpProduto, pos, 0);
						fwrite(&produto, sizeof(Produtos), 1, fpProduto);
						
						//salva na struct de pedidos
						pedido.idProdutos[i] = produto.id;
						pedido.quantidades[i] = qtdPedido;
						strcpy(pedido.nomeProdutos[i], produto.nome); 
						pedido.valorTotal += subtotal;
						i++;
					}
					else printf("\nQuantidade acima do estoque.");
				}
				if (i < TF) {
					printf("\nDeseja comprar mais produtos? (Sim/Nao): "); fflush(stdin);
					gets(resposta);
				}
			}while(stricmp(resposta, "sim") == 0 && i < TF);
			
			if (i == TF){
				printf("\nCarrinho cheio. Limite de %d itens atingido.\n", TF);
			}
			
			if (i == 0) printf("\nCarrinho vazio. Seu pedido nao foi registrado.");
			else{
				printf("\nRESUMO DA COMPRA");
				for (j = 0; j < i; j++){
					printf("\n%s", pedido.nomeProdutos[j]);
					printf("\nQuantidade: %d\n", pedido.quantidades[j]);
				}
				printf("\nTotal de produtos no carrinho: %d", i);
				printf("\nValor total da compra: %.2f\n", pedido.valorTotal);
				
				//gera numero aleatorio do pedido
				pedido.idPedido = rand() % 10000;
				
				printf("\nENTREGA DO PEDIDO");
				printf("\n1 - Receber em casa");
				printf("\n2 - Retirar pessoalmente");
				printf("\nEscolha uma opcao: ");
				scanf("%d", &opcao);
						
				switch(opcao){
						case 1:
							printf("\nPedido sera entregue no endereco: %s", socio.endereco); 
							printf("\nCodigo do Pedido: %d", pedido.idPedido);
							printf("\nInforme o codigo quando receber o pedido.");
							printf("\nObrigado por comprar conosco.");
							strcpy(pedido.opcaoEntrega, "A Domicilio");
							break;
						
						case 2:
							printf("\nCodigo do Pedido: %d", pedido.idPedido); 
							printf("\nInforme o codigo no balcao para retirar o pedido.");
							printf("\nObrigado por comprar conosco.");
							strcpy(pedido.opcaoEntrega, "Retirada");
							break;
							
						default: printf("\nOpcao invalida.\n"); break;
				}
				if (opcao == 1 || opcao == 2){
					pedido.totalProdutos = i;
					pedido.idSocio = socio.id;
					
					if (stricmp(socio.tipoPessoa, "Pessoa Fisica") == 0){
						strcpy(pedido.nomeSocio, socio.nome);
					}
					else if(stricmp(socio.tipoPessoa, "Pessoa Juridica") == 0){
						strcpy(pedido.nomeSocio, socio.nomeFantasia);
					}
					fwrite(&pedido, sizeof(Pedidos), 1, fpPedido);
				}
				else printf("Pedido nao registrado.");
			}
			fclose(fpPedido);
			fclose(fpProduto);
		}	
	}
	fclose(fpSocio);
}

//OPÇÃO 4 - RELATÓRIOS
void menuRelatorios() {
	int opcao;
	
	printf("MENU DE RELATORIOS\n");
	printf("\n1 - Relatorios de Socios");
	printf("\n2 - Relatorios de Pedidos");
	printf("\n3 - Relatorios de Fornecedores");
	printf("\n4 - Relatorios de Produtos");
	printf("\n5 - Relatorios de Marcas");
	printf("\n6 - Relatorios de Categorias");
	printf("\n7 - Retornar ao Menu Principal");
	printf("\nEscolha sua opcao: ");
	scanf("%d", &opcao);
	system("cls");
	
	while (opcao != 7) {
		switch(opcao) {
			case 1: relatorioSocios(); break;
			case 2: relatorioPedidos(); break;
			case 3: relatorioFornecedores(); break;
			case 4: relatorioProdutos(); break;
			case 5: relatorioMarcas(); break;
			case 6: relatorioCategorias(); break;
			default: printf("\nOpcao invalida"); break;
		}
		
		printf("\n");
		system("pause");
		system("cls");
		
		//sai lido
		printf("MENU DE RELATORIOS\n");
		printf("\n1 - Relatorios de Socios");
		printf("\n2 - Relatorios de Pedidos");
		printf("\n3 - Relatorios de Fornecedores");
		printf("\n4 - Relatorios de Produtos");
		printf("\n5 - Relatorios de Marcas");
		printf("\n6 - Relatorios de Categorias");
		printf("\n7 - Retornar ao Menu Principal");
		printf("\nEscolha sua opcao: ");
		scanf("%d", &opcao);
		system("cls");
	}
}

//1 - SÓCIOS
void relatorioSocios() {
	int opcao;
	
	printf("RELATORIOS DE SOCIOS\n");
	printf("\n1 - Exibir todos os Socios");
	printf("\n2 - Exibir Socios com Assinatura");
	printf("\n3 - Exibir Socios sem Assinatura");
	printf("\n4 - Exibir IDs Cadastrados");
	printf("\n5 - Filtrar por tipo de Socio");
	printf("\n6 - Retornar ao Menu de Relatorios");
	printf("\nEscolha uma opcao: ");
	scanf("%d", &opcao);
	
	while (opcao != 6){
		switch(opcao){
			case 1: exibirSocios(); break;
			case 2: sociosComAssinatura(); break;
			case 3: sociosSemAssinatura(); break;
			case 4: idSocios(); break;
			case 5: filtroSocios(); break;
			default: printf("Opcao invalida."); break;
		}
		printf("\n");
		system("pause");
		system("cls");
		
		//sai lido
		printf("RELATORIOS DE SOCIOS\n");
		printf("\n1 - Exibir todos os Socios");
		printf("\n2 - Exibir Socios com Assinatura");
		printf("\n3 - Exibir Socios sem Assinatura");
		printf("\n4 - Exibir IDs Cadastrados");
		printf("\n5 - Filtrar por tipo de Socio");
		printf("\n6 - Retornar ao Menu de Relatorios");
		printf("\nEscolha uma opcao: ");
		scanf("%d", &opcao);
	}
}

void exibirSocios() {
	FILE *fp = fopen("cadastroSocios.bin", "rb");
	if (fp == NULL) {
		printf("Erro ao ler arquivo.");
		return;
	}
	Socios socio;
	while (fread(&socio, sizeof(Socios), 1, fp) == 1) {
		printf("\nID: %d\n", socio.id);
		
		//Se for Pessoa Fisica
		if (stricmp(socio.tipoPessoa, "Pessoa Fisica") == 0){
			printf("%s\n", socio.tipoPessoa);
			printf("Nome: %s\n", socio.nome);
			printf("CPF: %s\n", socio.cpf);
		}
		//Se for Pessoa Juridica
		else if (stricmp(socio.tipoPessoa, "Pessoa Juridica") == 0){
			printf("%s\n", socio.tipoPessoa);
			printf("Razao Social: %s\n", socio.razaoSocial);
			printf("Nome Fantasia: %s\n", socio.nomeFantasia);
			printf("CNPJ: %s\n", socio.cnpj);
		}
		printf("Email: %s\n", socio.email);
		printf("Telefone: %s\n", socio.telefone);
		printf("Endereco: %s\n", socio.endereco);
		printf("Tipo do Plano: %s\n", socio.plano);
		if (!socio.assinatura) printf("Nao possui assinatura ativa.\n");
		else printf("Possui assinatura.\n");
	}
	fclose(fp);
}

void sociosComAssinatura(){
	int cont = 0;
	FILE *fp = fopen("cadastroSocios.bin", "rb");
	if (fp == NULL) {
		printf("Erro ao ler arquivo.");
		return;
	}
	Socios socio;
	while (fread(&socio, sizeof(Socios), 1, fp) == 1){
		if (socio.assinatura){
			printf("\nID: %d\n", socio.id);
			
			if (stricmp(socio.tipoPessoa,"Pessoa Fisica") == 0){
				printf("Nome: %s\n", socio.nome);
				printf("CPF: %s\n", socio.cpf);
			}
			else if (stricmp(socio.tipoPessoa, "Pessoa Juridica") == 0){
				printf("Razao Social: %s\n", socio.razaoSocial);
				printf("Nome Fantasia: %s\n", socio.nomeFantasia);
				printf("CNPJ: %s\n", socio.cnpj);
			}
			printf("Email: %s\n", socio.email);
			printf("Telefone: %s\n", socio.telefone);
			printf("Endereco: %s\n", socio.endereco);
			printf("Tipo do Plano: %s\n", socio.plano);
			cont++;
		}
	}
	printf("\nExiste(m) %d Socio(s) com assinatura ativa.", cont);
	fclose(fp);
}

void sociosSemAssinatura(){
	int cont = 0;
	FILE *fp = fopen("cadastroSocios.bin", "rb");
	if (fp == NULL) {
		printf("Erro ao ler arquivo.");
		return;
	}
	Socios socio;
	while (fread(&socio, sizeof(Socios), 1, fp) == 1){
		if (!socio.assinatura){
			printf("\nID: %d\n", socio.id);
			
			if (stricmp(socio.tipoPessoa, "Pessoa Fisica") == 0){
				printf("Nome: %s\n", socio.nome);
				printf("CPF: %s\n", socio.cpf);
			}
			else if(stricmp(socio.tipoPessoa, "Pessoa Juridica") == 0){
				printf("Razao Social: %s\n", socio.razaoSocial);
				printf("Nome Fantasia: %s\n", socio.nomeFantasia);
				printf("CNPJ: %s\n", socio.cnpj);
			}
			printf("Email: %s\n", socio.email);
			printf("Telefone: %s\n", socio.telefone);
			printf("Endereco: %s\n", socio.endereco);
			printf("Tipo do Plano: %s\n", socio.plano);
			cont++;
		}
	}
	printf("\nExiste(m) %d Socio(s) sem assinatura ativa.", cont);
	fclose(fp);
}

void idSocios(){
	FILE *fp = fopen("cadastroSocios.bin", "rb");
	if (fp == NULL) {
		printf("Erro ao ler arquivo.");
		return;
	}
	Socios socio;
	printf("\nIDs em uso: \n");
	while (fread(&socio, sizeof(Socios), 1, fp) == 1){
		if (stricmp(socio.tipoPessoa, "Pessoa Fisica") == 0){
			socio.nome[strcspn(socio.nome, "\n")] = '\0';
			printf("\n%d - %s - %s", socio.id, socio.nome, socio.tipoPessoa);
		}
		
		else if(stricmp(socio.tipoPessoa, "Pessoa Juridica") == 0){
			socio.nomeFantasia[strcspn(socio.nomeFantasia, "\n")] = '\0';
			printf("\n%d - %s - %s", socio.id, socio.nomeFantasia, socio.tipoPessoa);
		}
	}
	fclose(fp);
}

void filtroSocios(){
	FILE *fp = fopen("cadastroSocios.bin", "rb");
	if (fp == NULL){
		printf("Erro ao ler arquivo.");
		return;
	}
	Socios socio;
	int i = 0;
	char busca[30];
	
	printf("Digite o tipo de Socio que deseja filtrar (Pessoa Fisica ou Pessoa Juridica): "); fflush(stdin);
	gets(busca);
	
	while(fread(&socio, sizeof(Socios), 1, fp) == 1){
		if (stricmp(busca, socio.tipoPessoa) == 0){
			printf("\nID: %d", socio.id);
			
			if (stricmp(socio.tipoPessoa, "Pessoa Fisica") == 0){
				printf("\nNome: %s", socio.nome);
				printf("\nCPF: %s", socio.cpf);
			}
			else if(stricmp(socio.tipoPessoa, "Pessoa Juridica") == 0){
				printf("\nRazao Social: %s", socio.razaoSocial);
				printf("\nNome Fantasia: %s", socio.nomeFantasia);
				printf("\nCNPJ: %s", socio.cnpj);
			}
			
			printf("\nEmail: %s", socio.email);
			printf("\nTelefone: %s", socio.telefone);
			printf("\nEndereco: %s", socio.endereco);
			printf("\nTipo do plano: %s\n", socio.plano);
			i = 1;
		}
	}
	if (i == 0) printf("Nao existem Socios cadastrados com esse tipo.");
	fclose(fp);
}

//2 - PEDIDOS
void relatorioPedidos() {
	int opcao;
	
	printf("RELATORIOS DE PEDIDOS\n");
	printf("\n1 - Exibir todos os Pedidos");
	printf("\n2 - Filtrar por tipo de Entrega");
	printf("\n3 - Retornar ao menu de Relatorios");
	printf("\nEscolha uma opcao: ");
	scanf("%d", &opcao);
	
	while(opcao != 3){
		switch(opcao){
			case 1: exibirPedidos(); break;
			case 2: filtroPedidos(); break;
			default: printf("Opcao invalida."); break;
		}
		printf("\n");
		system("pause");
		system("cls");
		
		//sai lido
		printf("RELATORIOS DE PEDIDOS\n");
		printf("\n1 - Exibir todos os Pedidos");
		printf("\n2 - Filtrar por tipo de Entrega");
		printf("\n3 - Retornar ao menu de Relatorios");
		printf("\nEscolha uma opcao: ");
		scanf("%d", &opcao);
	}
}

void exibirPedidos(){
	int i;
	Pedidos pedido;
	FILE *fp = fopen("cadastroPedidos.bin", "rb");
	if (fp == NULL) {
		printf("Erro ao ler arquivo.");
		return;
	}
	while (fread(&pedido, sizeof(Pedidos), 1, fp) == 1){
		printf("\nID do Pedido: %d", pedido.idPedido);
		printf("\nID do Socio: %d", pedido.idSocio);
		printf("\nNome do Socio: %s", pedido.nomeSocio);
		
		printf("\n%-15s %-20s %-10s\n", "ID do Produto","Produto","Quantidade");
		printf("_______________________________________________\n");
		for (i = 0; i < pedido.totalProdutos; i++){
			pedido.nomeProdutos[i][strcspn(pedido.nomeProdutos[i], "\n")] = '\0';
			
			printf("%-15d", pedido.idProdutos[i]);
			printf(" %-20s", pedido.nomeProdutos[i]);
			printf(" %-10d\n", pedido.quantidades[i]);
			
		}
		printf("\nTotal de produtos: %d", pedido.totalProdutos);
		printf("\nValor total: %.2f", pedido.valorTotal);
		printf("\nOpcao de entrega: %s", pedido.opcaoEntrega);
	}
	fclose(fp);
}

void filtroPedidos(){
	FILE *fp = fopen("cadastroPedidos.bin", "rb");
	if (fp == NULL){
		printf("Erro ao ler arquivo.");
		return;
	}
	int i = 0;
	Pedidos pedido;
	char busca[30];
	
	printf("Digite o tipo de Entrega que deseja filtrar (Retirada ou A Domicilio): "); fflush(stdin);
	gets(busca);
	
	while (fread(&pedido, sizeof(Pedidos), 1, fp) == 1){
		if (stricmp(busca, pedido.opcaoEntrega) == 0){
			printf("\nID do Pedido: %d", pedido.idPedido);
			printf("\nID do Socio: %d", pedido.idSocio);
			printf("\nNome do Socio: %s", pedido.nomeSocio);
			printf("Valor total da compra: %.2f", pedido.valorTotal);
			i = 1;
		}
	}
	if (i == 0) printf("Nao existem pedidos cadastrados com esse tipo de Entrega.");
	fclose(fp);
}

//3 - FORNECEDORES
void relatorioFornecedores() {
	int opcao;
	
	printf("RELATORIOS DE FORNECEDORES\n");
	printf("\n1 - Exibir todos os Fornecedores");
	printf("\n2 - Exibir Contatos de Fornecedores");
	printf("\n3 - Exibir IDs Cadastrados");
	printf("\n4 - Retornar ao Menu de Relatorios");
	printf("\nEscolha uma opcao: ");
	scanf("%d", &opcao);
	
	while(opcao != 4){
		switch(opcao){
			case 1: exibirFornecedores(); break;
			case 2: contatoFornecedores(); break;	
			case 3: idFornecedores(); break;
			default: printf("Opcao invalida."); break;
		}
		printf("\n");
		system("pause");
		system("cls");
		
		//sai lido
		printf("RELATORIOS DE FORNECEDORES\n");
		printf("\n1 - Exibir todos os Fornecedores");
		printf("\n2 - Exibir Contatos de Fornecedores");
		printf("\n3 - Exibir IDs Cadastrados");
		printf("\n4 - Retornar ao Menu de Relatorios");
		printf("\nEscolha uma opcao: ");
		scanf("%d", &opcao);
	}
}

void exibirFornecedores(){
	int cont = 0;
	Fornecedores fornecedor;
	FILE *fp = fopen("cadastroFornecedores.bin", "rb");
	if (fp == NULL) {
		printf("Erro ao ler arquivo.");
		return;
	}
	
	while (fread(&fornecedor, sizeof(Fornecedores), 1, fp) == 1) {
		printf("\nID: %d\n", fornecedor.id);
		printf("Razao Social: %s", fornecedor.razaoSocial);
		printf("Nome Fantasia: %s", fornecedor.nomeFantasia);
		printf("CNPJ: %s", fornecedor.cnpj);
		printf("Email: %s", fornecedor.email);
		printf("Telefone: %s", fornecedor.telefone);
		printf("Endereco: %s", fornecedor.endereco);
		cont++;
	}
	printf("\n%d Fornecedores cadastrados.",cont);
	fclose(fp);
}

void contatoFornecedores(){
	Fornecedores fornecedor;
	FILE *fp = fopen("cadastroFornecedores.bin", "rb");
	if (fp == NULL) {
		printf("Erro ao ler arquivo.");
		return;
	}
	printf("\nFORNECEDORES - CONTATOS\n");
	while (fread(&fornecedor, sizeof(Fornecedores), 1, fp) == 1){
		printf("Nome Fantasia: %s", fornecedor.nomeFantasia);
		printf("Email: %s", fornecedor.email);
		printf("Telefone: %s", fornecedor.telefone);
		printf("\n");
	}
	fclose(fp);
}

void idFornecedores(){
	Fornecedores fornecedor;
	FILE *fp = fopen("cadastroFornecedores.bin", "rb");
	if (fp == NULL) {
		printf("Erro ao ler arquivo.");
		return;
	}
	printf("\nIDs em uso: \n");
	while (fread(&fornecedor, sizeof(Fornecedores), 1, fp) == 1){
		printf("%d - %s", fornecedor.id, fornecedor.nomeFantasia);
	}
	fclose(fp);
}

//4 - PRODUTOS
void relatorioProdutos() {
	int opcao;
	
	printf("RELATORIOS DE PRODUTOS\n");
	printf("\n1 - Exibir todos os Produtos");
	printf("\n2 - Exibir IDs Cadastrados");
	printf("\n3 - Exibir Produtos com estoque baixo");
	printf("\n4 - Exibir Produtos sem estoque");
	printf("\n5 - Exibir Tabela de Precos");
	printf("\n6 - Filtrar por Categoria");
	printf("\n7 - Filtrar por Marca");
	printf("\n8 - Retornar ao menu de Relatorios");
	printf("\nEscolha uma opcao: ");
	scanf("%d", &opcao);
	
	while(opcao != 8){
		switch(opcao){
			case 1: exibirProdutos(); break;
			case 2: idProdutos(); break;
			case 3: estoqueBaixo(); break;
			case 4: semEstoque(); break;
			case 5: tabelaPrecos(); break;
			case 6: filtroProdutos(); break;
			case 7: filtroPorMarca(); break;
			default: printf("Opcao invalida."); break;
		}
		printf("\n");
		system("pause");
		system("cls");
		
		//sai lido
		printf("RELATORIOS DE PRODUTOS\n");
		printf("\n1 - Exibir todos os Produtos");
		printf("\n2 - Exibir IDs Cadastrados");
		printf("\n3 - Exibir Produtos com estoque baixo");
		printf("\n4 - Exibir Produtos sem estoque");
		printf("\n5 - Exibir Tabela de Precos");
		printf("\n6 - Filtrar por Categoria");
		printf("\n7 - Filtrar por Marca");
		printf("\n8 - Retornar ao menu de Relatorios");
		printf("\nEscolha uma opcao: ");
		scanf("%d", &opcao);
	}
}

void exibirProdutos() {
	Produtos produto;
	FILE *fp = fopen("cadastroProdutos.bin", "rb");
	if (fp == NULL){
		printf("Erro ao ler arquivo.");
		return;
	}
	
	while (fread(&produto, sizeof(Produtos), 1, fp) == 1) {
		printf("\nID: %d\n", produto.id);
		printf("Nome do produto: %s\n", produto.nome);
		printf("Descricao: %s\n", produto.descricao);
		printf("Quantidade: %d\n", produto.quantidade);
		printf("Preco: %.2f\n", produto.preco);
		printf("Categoria: %s\n", produto.categoria);
		printf("Marca: %s\n", produto.marca);
	}
	fclose(fp);
}

void idProdutos(){
	Produtos produto;
	FILE *fp = fopen("cadastroProdutos.bin", "rb");
	if (fp == NULL) {
		printf("Erro ao ler arquivo.");
		return;
	}
	printf("\nIDs em uso: \n");
	while (fread(&produto, sizeof(Produtos), 1, fp) == 1){
		printf("%d - %s\n", produto.id, produto.nome);
	}
	fclose(fp);
}

void estoqueBaixo(){
	Produtos produto;
	bool estoque = false;
	FILE *fp = fopen("cadastroProdutos.bin", "rb");
	if (fp == NULL) {
		printf("Erro ao ler arquivo.");
		return;
	}
	printf("\nProdutos com estoque baixo: \n");
	while (fread(&produto, sizeof(Produtos), 1, fp) == 1){
		if (produto.quantidade <= 20){
			printf("%d - %s\n", produto.id, produto.nome);
			estoque = true;
		}
	}
	if (!estoque) printf("Nao existem produtos com estoque baixo.");
	fclose(fp);
}

void semEstoque(){
	Produtos produto;
	bool estoque = false;
	FILE *fp = fopen("cadastroProdutos.bin", "rb");
	if (fp == NULL) {
		printf("Erro ao ler arquivo.");
		return;
	}
	printf("\nProdutos sem estoque: \n");
	while (fread(&produto, sizeof(Produtos), 1, fp) == 1){
		if (produto.quantidade == 0){
			printf("%d - %s\n", produto.id, produto.nome);
			estoque = true;
		}
	}
	if (!estoque) printf("Nao existem produtos sem estoque.\n");
	fclose(fp);
}

void tabelaPrecos(){
	Produtos produto;
	FILE *fp = fopen("cadastroProdutos.bin", "rb");
	if (fp == NULL) {
		printf("Erro ao ler arquivo.");
		return;
	}
	printf("\nTabela de precos: \n");
	while(fread(&produto, sizeof(Produtos), 1, fp) == 1){
		produto.nome[strcspn(produto.nome, "\n")] = '\0';
		printf("%s - %.2f\n", produto.nome, produto.preco);
	}
	fclose(fp);
}

void filtroProdutos(){
	FILE *fp = fopen("cadastroProdutos.bin", "rb");
	if (fp == NULL){
		printf("Erro ao ler arquivo.");
		return;
	}
	int i = 0;
	Produtos produto;
	char busca[50];
	
	printf("Digite a categoria que deseja filtrar: "); fflush(stdin);
	gets(busca);
	
	while (fread(&produto, sizeof(Produtos), 1, fp) == 1){
		if (stricmp(busca, produto.categoria) == 0){
			printf("\nID: %d", produto.id);
			printf("\nNome: %s", produto.nome);
			printf("\nDescricao: %s", produto.descricao);
			printf("\nPreco: %.2f", produto.preco);
			printf("\nQuantidade: %d\n", produto.quantidade);
			printf("Marca: %s\n", produto.marca);
			i = 1;
		}
	}
	
	if (i == 0) printf("Nao existem produtos cadastrados com essa categoria.");
	fclose(fp);
}

void filtroPorMarca(){
	FILE *fp = fopen("cadastroProdutos.bin", "rb");
	if (fp == NULL){
		printf("Erro ao ler arquivo.");
		return;
	}
	
	int i = 0;
	Produtos produto;
	char busca[50];
	
	printf("Digite a marca que deseja filtrar: "); fflush(stdin);
	gets(busca);
	
	while (fread(&produto, sizeof(Produtos), 1, fp) == 1){
		if (stricmp(busca, produto.marca) == 0){
			printf("\nID: %d", produto.id);
			printf("\nNome: %s", produto.nome);
			printf("\nDescricao: %s", produto.descricao);
			printf("\nPreco: %.2f", produto.preco);
			printf("\nQuantidade: %d", produto.quantidade);
			printf("\nCategoria: %s\n", produto.categoria);
			i = 1;
		}
	}
	
	if (i == 0) printf("Nao existem produtos cadastrados com essa marca.");
	fclose(fp);
}

//5 - MARCAS
void relatorioMarcas(){
	int opcao;
	
	printf("RELATORIOS DE MARCAS\n");
	printf("\n1 - Exibir todas as Marcas");
	printf("\n2 - Exibir IDs Cadastrados");
	printf("\n3 - Ordenar Marcas por Ordem Alfabetica");
	printf("\n4 - Retornar ao menu de Relatorios");
	printf("\nEscolha uma opcao: ");
	scanf("%d", &opcao);
	
	while(opcao != 4){
		switch(opcao){
			case 1: exibirMarcas(); break;
			case 2: idMarcas(); break;
			case 3: ordenarMarcas(); break;
			default: printf("Opcao invalida."); break;
		}
		printf("\n");
		system("pause");
		system("cls");
		
		//sai lido
		printf("RELATORIOS DE MARCAS\n");
		printf("\n1 - Exibir todas as Marcas");
		printf("\n2 - Exibir IDs Cadastrados");
		printf("\n3 - Ordenar Marcas por Ordem Alfabetica");
		printf("\n4 - Retornar ao menu de Relatorios");
		printf("\nEscolha uma opcao: ");
		scanf("%d", &opcao);
	}
}

void exibirMarcas(){
	Marcas marca;
	FILE *fp = fopen("cadastroMarcas.bin", "rb");
	if (fp == NULL) {
		printf("Erro ao ler arquivo.");
		return;
	}
	
	while(fread(&marca, sizeof(Marcas), 1, fp) == 1){
		printf("ID: %d\n", marca.id);
		printf("Nome: %s", marca.nome);
		printf("Descricao: %s\n", marca.descricao);
	}
	fclose(fp);
}

void idMarcas(){
	Marcas marca;
	FILE *fp = fopen("cadastroMarcas.bin", "rb");
	if (fp == NULL) {
		printf("Erro ao ler arquivo.");
		return;
	}
	printf("\nIDs em uso: \n");
	while(fread(&marca, sizeof(Marcas), 1, fp) == 1){
		printf("%d - %s", marca.id, marca.nome);
	}
	fclose(fp);
}

void ordenarMarcas(){
	int i, quantidade = 0;
	Marcas marca, marca_a;
	FILE *fp = fopen("cadastroMarcas.bin", "rb+");
	if (fp == NULL){
		printf("\nErro ao ler arquivo.");
		return;
	}
	else{
		fseek(fp, 0, 2);
		quantidade = ftell(fp)/sizeof(Marcas);
		while (quantidade > 1){
			for (i = 0; i < quantidade-1; i++){
				fseek(fp, i * sizeof(Marcas), 0);
				fread(&marca, sizeof(Marcas), 1, fp);
				
				fseek(fp, (i+1) * sizeof(Marcas), 0);
				fread(&marca_a, sizeof(Marcas), 1, fp);
				
				if (stricmp(marca.nome, marca_a.nome) > 0){
					fseek(fp, i*sizeof(Marcas), 0);
					fwrite(&marca_a, sizeof(Marcas), 1, fp);
					
					fseek(fp, (i+1) * sizeof(Marcas), 0);
					fwrite(&marca, sizeof(Marcas), 1, fp);
				}
			}
			quantidade--;
		}
	}
	fclose(fp);
	printf("\nArquivo ordenado com sucesso.");
	system("pause");
}

//6 - CATEGORIAS	
void relatorioCategorias() {
	int opcao;
	
	printf("RELATORIOS DE CATEGORIAS\n");
	printf("\n1 - Exibir todas as Categorias");
	printf("\n2 - Exibir IDs Cadastrados");
	printf("\n3 - Ordenar Categorias por Ordem Alfabetica");
	printf("\n4 - Retornar ao menu de Relatorios");
	printf("\nEscolha uma opcao: ");
	scanf("%d", &opcao);
	
	while(opcao != 4){
		switch(opcao){
			case 1: exibirCategorias(); break;
			case 2: idCategorias(); break;
			case 3: ordenarCategorias(); break;
			default: printf("Opcao invalida."); break;
		}
		printf("\n");
		system("pause");
		system("cls");
		
		//sai lido
		printf("RELATORIOS DE CATEGORIAS\n");
		printf("\n1 - Exibir todas as Categorias");
		printf("\n2 - Exibir IDs Cadastrados");
		printf("\n3 - Ordenar Categorias por Ordem Alfabetica");
		printf("\n4 - Retornar ao menu de Relatorios");
		printf("\nEscolha uma opcao: ");
		scanf("%d", &opcao);
	}
}

void exibirCategorias(){
	Categorias categoria;
	FILE *fp = fopen("cadastroCategorias.bin", "rb");
	if (fp == NULL) {
		printf("Erro ao ler arquivo.");
		return;
	}
	while(fread(&categoria, sizeof(Categorias), 1, fp) == 1){
		printf("ID: %d\n", categoria.id);
		printf("Nome: %s", categoria.nome);
		printf("Descricao: %s\n", categoria.descricao);
	}
	fclose(fp);
}

void idCategorias(){
	Categorias categoria;
	FILE *fp = fopen("cadastroCategorias.bin", "rb");
	if (fp == NULL) {
		printf("Erro ao ler arquivo.");
		return;
	}
	printf("\nIDS em uso: \n");
	while(fread(&categoria, sizeof(Categorias), 1, fp) == 1){
		printf("%d - %s", categoria.id, categoria.nome);
	}
	fclose(fp);
}

void ordenarCategorias(){
	int i, quantidade = 0;
	Categorias categoria, categoria_a;
	FILE *fp = fopen("cadastroCategorias.bin", "rb+");
	if (fp == NULL){
		printf("Erro ao ler arquivo.");
		return;
	}
	else{
		fseek(fp, 0, 2);
		quantidade = ftell(fp)/sizeof(Categorias);
		while (quantidade > 1){
			for (i = 0; i < quantidade-1; i++){
				fseek(fp, i * sizeof(Categorias), 0);
				fread(&categoria, sizeof(Categorias), 1, fp);
				
				fseek(fp, (i+1) * sizeof(Categorias), 0);
				fread(&categoria_a, sizeof(Categorias), 1, fp);
				
				if (stricmp(categoria.nome, categoria_a.nome) > 0){
					fseek(fp, i*sizeof(Categorias), 0);
					fwrite(&categoria_a, sizeof(Categorias), 1, fp);
					
					fseek(fp, (i+1) * sizeof(Categorias), 0);
					fwrite(&categoria, sizeof(Categorias), 1, fp);
				}
			}
			quantidade--;
		}
	}
	fclose(fp);
	printf("\nArquivo ordenado com sucesso.");
	system("pause");
}
