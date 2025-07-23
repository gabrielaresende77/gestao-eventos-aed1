#include <iostream>
#include <locale.h>
#include <string>

using namespace std;

const int MAX = 100; // Define uma constante para o tamanho máximo dos arrays

// Estrutura para armazenar dados dos participantes
struct Participante {
    string nome, matricula, curso, email, celular, genero;
    int semestre, idade;
    string tipoParticipante;	
    bool participaDeAtividadesEsportivas;
};

// Estrutura para armazenar dados das atividades
struct Atividade {
    string nome, tipo, local, data, hora;
    int vagas;
};

// Estrutura para armazenar dados das inscrições
struct Inscricao {
    string matriculaParticipante;
    string nomeAtividade;
    string dataInscricao;
    bool presencaConfirmada;
};

// Arrays para armazenar os registros
Participante participantes[MAX];
Atividade atividades[MAX];
Inscricao inscricoes[MAX];

// Variáveis para controlar a quantidade atual de registros em cada array
int totalParticipantes = 0, totalAtividades = 0, totalInscricoes = 0;

// Declaração das funções
void menu();
void cadastrarParticipante();
void cadastrarAtividade();
void cadastrarInscricao();
void alterarDados();
void alterarParticipante();
void alterarAtividade();
void alterarInscricao();
void listarAtividadesPorTipo();
void listarParticipantesEsportivos();
void listarInscricoesPorData();

// Função principal
int main() {
	setlocale(LC_ALL, "portuguese");
    menu();
    return 0;
}

// Menu principal
void menu() {
    int opcao;
    do {
        cout << "\n===================== MENU =====================\n";
        cout << "1. Cadastrar Participante\n";
        cout << "2. Cadastrar Atividade\n";
        cout << "3. Cadastrar Inscrição\n";
        cout << "4. Alterar Dados\n";
        cout << "5. Listar Atividades por Tipo\n";
        cout << "6. Listar Participantes em Atividades Esportivas\n";
        cout << "7. Listar Inscrições por Data\n";
        cout << "0. Sair\nEscolha uma opção: ";
        cin >> opcao;
        cin.ignore();

        switch(opcao) {
            case 1: cadastrarParticipante(); break;
            case 2: cadastrarAtividade(); break;
            case 3: cadastrarInscricao(); break;
            case 4: alterarDados(); break;
            case 5: listarAtividadesPorTipo(); break;
            case 6: listarParticipantesEsportivos(); break;
            case 7: listarInscricoesPorData(); break;
            case 0: cout << "Sistema encerrado.\n"; break;
            default: cout << "Opção inválida!\n";
        }
    } while (opcao != 0);
}

// Cadastra um novo participante
void cadastrarParticipante() {
    if (totalParticipantes >= MAX) {
        cout << "Limite de participantes atingido.\n";
        return;
    }

    Participante &p = participantes[totalParticipantes];
    cout << "Nome: "; getline(cin, p.nome);
    
    string matriculaTemp;
    bool matriculaRepetida;
    do {
		matriculaRepetida = false;
		cout << "Matrícula: "; getline(cin, matriculaTemp);
		
		for (int i = 0; i < totalParticipantes; i++) {
			if (participantes[i].matricula == matriculaTemp) {
				cout << "Matrícula já cadastrada. Digite outra.\n";
				matriculaRepetida = true;
				break;
			}
		}
	} while (matriculaRepetida);
	p.matricula = matriculaTemp;
    
    cout << "Curso: "; getline(cin, p.curso);
    cout << "Semestre: "; cin >> p.semestre;
    cin.ignore();
    cout << "E-mail: "; getline(cin, p.email);
    cout << "Celular: "; getline(cin, p.celular);
    
    do {
		cout << "Gênero (M/F): "; getline(cin, p.genero);
		if (p.genero != "M" && p.genero != "F") {
			cout << "Entrada inválida! Digite novamente.\n";
		} else {
			break;
		}
	} while (true);
    
    cout << "Idade: "; cin >> p.idade;
    cin.ignore();
    
    do {
		cout << "Tipo de Participante (organizador/palestrante/ouvinte): ";
		getline(cin, p.tipoParticipante);
		if (p.tipoParticipante != "organizador" &&
			p.tipoParticipante != "palestrante" &&
			p.tipoParticipante != "ouvinte") {
				cout << "Tipo inválido! Digite novamente.\n";
		} else {
			break;
		}
	} while(true);
	
	string esporteTemp;
	bool entradaValida = false;
	do {
		cout << "Participa de atividades esportivas? (1 - Sim | 0 - Não): ";
		getline(cin, esporteTemp);
		if (esporteTemp == "1") {
			p.participaDeAtividadesEsportivas = true;
			entradaValida = true;
		} else if (esporteTemp == "0") {
			p.participaDeAtividadesEsportivas = false;
			entradaValida = true;
		} else {
			cout << "Entrada inválida. Digite 1 para sim ou 0 para não.\n";
		}
	} while (!entradaValida);
	
    totalParticipantes++;
    cout << "Participante cadastrado!\n";
}

// Cadastra uma nova atividade
void cadastrarAtividade() {
    if (totalAtividades >= MAX) {
        cout << "Limite de atividades atingido.\n";
        return;
    }

    Atividade &a = atividades[totalAtividades];
    cout << "Nome da Atividade: "; getline(cin, a.nome);
    
    do {
		cout << "Tipo (palestra, oficina, competição, festa): "; getline(cin, a.tipo);
		if (a.tipo != "palestra" &&
			a.tipo != "oficina" &&
			a.tipo != "competição" &&
			a.tipo != "festa") {
				cout << "Tipo inválido! Digite novamente.\n";
			} else {
				break;
			}
	} while (true);
    
    cout << "Local: "; getline(cin, a.local);
    cout << "Data (DD/MM/AAAA): "; getline(cin, a.data);
    cout << "Hora: "; getline(cin, a.hora);
    cout << "Vagas Disponíveis: "; cin >> a.vagas;
    cin.ignore();

    totalAtividades++;
    cout << "Atividade cadastrada!\n";
}

// Cadastra uma inscrição de participante em uma atividade
void cadastrarInscricao() {
    if (totalInscricoes >= MAX) {
        cout << "Limite de inscrições atingido.\n";
        return;
    }

    string matricula, nomeAtividade;
    cout << "Matrícula do participante: "; getline(cin, matricula);
    cout << "Nome da atividade: "; getline(cin, nomeAtividade);

	// Busca participante
    int i;
    for (i = 0; i < totalParticipantes; i++) {
        if (participantes[i].matricula == matricula) {
            break;
        }
    }
    if (i == totalParticipantes) {
        cout << "Participante não encontrado.\n";
        return;
    }
    
    // Busca atividade
    int j;
    for (j = 0; j < totalAtividades; j++) {
        if (atividades[j].nome == nomeAtividade) {
            break;
        }
    }
    if (j == totalAtividades) {
        cout << "Atividade não encontrada.\n";
        return;
    }

    if (atividades[j].vagas <= 0) {
        cout << "Não há vagas disponíveis para esta atividade.\n";
        return;
    }
    
	// Cadastro da inscrição
    Inscricao &ins = inscricoes[totalInscricoes];
    ins.matriculaParticipante = matricula;
    ins.nomeAtividade = nomeAtividade;
    cout << "Data da Inscrição (DD/MM/AAAA): "; getline(cin, ins.dataInscricao);
    cout << "Presença confirmada? (1-sim / 0-não): "; cin >> ins.presencaConfirmada;
    cin.ignore();

    atividades[j].vagas--;
    totalInscricoes++;
    cout << "Inscrição realizada!\n";
}

// Menu de alteração de dados
void alterarDados() {
    int opcao;
    cout << "Qual dado deseja alterar?\n";
    cout << "1. Participante\n2. Atividade\n3. Inscrição\nEscolha: ";
    cin >> opcao;
    cin.ignore();
    switch (opcao) {
        case 1: alterarParticipante(); break;
        case 2: alterarAtividade(); break;
        case 3: alterarInscricao(); break;
        default: cout << "Opção inválida.\n";
    }
}

// Altera dados do participante
void alterarParticipante() {
    string matricula;
    cout << "Digite a matrícula do participante: "; getline(cin, matricula);

    for (int i = 0; i < totalParticipantes; i++) {
        if (participantes[i].matricula == matricula) {
            cout << "Novo nome: "; getline(cin, participantes[i].nome);
            cout << "Novo curso: "; getline(cin, participantes[i].curso);
            cout << "Novo semestre: "; cin >> participantes[i].semestre;
            cin.ignore();
            cout << "Novo e-mail: "; getline(cin, participantes[i].email);
            cout << "Novo celular: "; getline(cin, participantes[i].celular);
            
            do {
				cout << "Novo gênero (M/F): "; getline(cin, participantes[i].genero);
				if (participantes[i].genero != "M" && participantes[i].genero != "F") {
					cout << "Entrada inválida! Digite novamente.\n";
				} else {
					break;
				}
			} while (true);
			
            cout << "Nova idade: "; cin >> participantes[i].idade;
            cin.ignore();
            
            do {
				cout << "Novo tipo de participante (organizador/palestrante/ouvinte): ";
				getline(cin, participantes[i].tipoParticipante);
				if (participantes[i].tipoParticipante != "organizador" &&
					participantes[i].tipoParticipante != "palestrante" &&
					participantes[i].tipoParticipante != "ouvinte") {
						cout << "Tipo inválido! Digite novamente.\n";
				} else {
						break;
					}
			} while (true);
			
			
		string esporteTemp;
		bool entradaValida = false;
		do {
			cout << "Participa de atividades esportivas? (1 - Sim | 0 - Não): ";
			getline(cin, esporteTemp);
			if (esporteTemp == "1") {
				participantes[i].participaDeAtividadesEsportivas = true;
				entradaValida = true;
			} else if (esporteTemp == "0") {
				participantes[i].participaDeAtividadesEsportivas = false;
				entradaValida = true;
			} else {
				cout << "Entrada inválida. Digite 1 para sim ou 0 para não.\n";
			}
		} while (!entradaValida);
			
        cout << "Dados do participante atualizados.\n";
        return;
        }
    }
    cout << "Participante não encontrado.\n";
}

// Altera dados da atividade
void alterarAtividade() {
    string nome;
    cout << "Digite o nome da atividade: "; getline(cin, nome);

    for (int i = 0; i < totalAtividades; i++) {
        if (atividades[i].nome == nome) {
        	
        	do {
				cout << "Novo tipo (palestra, oficina, competição, festa): "; getline(cin, atividades[i].tipo);
				if (atividades[i].tipo != "palestra" &&
					atividades[i].tipo != "oficina" &&
					atividades[i].tipo != "competição" &&
					atividades[i].tipo != "festa") {
						cout << "Tipo inválido! Digite novamente.\n";
					} else {
						break;
					}
			} while (true);
			
            cout << "Novo local: "; getline(cin, atividades[i].local);
            cout << "Nova data (DD/MM/AAAA): "; getline(cin, atividades[i].data);
            cout << "Nova hora: "; getline(cin, atividades[i].hora);
            cout << "Novas vagas: "; cin >> atividades[i].vagas;
            cin.ignore();
            cout << "Dados da atividade atualizados.\n";
            return;
        }
    }
    cout << "Atividade não encontrada.\n";
}

// Altera dados da inscrição
void alterarInscricao() {
    string matricula, nomeAtividade;
    cout << "Digite a matrícula do participante: "; getline(cin, matricula);
    cout << "Digite o nome da atividade: "; getline(cin, nomeAtividade);

    for (int i = 0; i < totalInscricoes; i++) {
        if (inscricoes[i].matriculaParticipante == matricula && inscricoes[i].nomeAtividade == nomeAtividade) {
            cout << "Nova data da inscrição: "; getline(cin, inscricoes[i].dataInscricao);
            cout << "Presença confirmada? (1-sim / 0-nao): "; cin >> inscricoes[i].presencaConfirmada;
            cin.ignore();
            cout << "Dados da inscrição atualizados.\n";
            return;
        }
    }
    cout << "Inscrição não encontrada.\n";
}

// Lista atividades de acordo com o tipo informado
void listarAtividadesPorTipo() {
    string tipo;
    cout << "Digite o tipo de atividade: "; getline(cin, tipo);

    cout << "Atividades do tipo " << tipo << ":\n";
    bool encontrou = false;
    for (int i = 0; i < totalAtividades; i++) {
        if (atividades[i].tipo == tipo) {
            cout << "- " << atividades[i].nome << " | Local: " << atividades[i].local
                 << " | Data: " << atividades[i].data << " | Hora: " << atividades[i].hora
                 << " | Vagas: " << atividades[i].vagas << endl;
            encontrou = true;
        }
    }
    if (!encontrou) {
        cout << "Nenhuma atividade encontrada desse tipo.\n";
    }
}

// Lista participantes que praticam atividades esportivas
void listarParticipantesEsportivos() {
    cout << "Participantes em atividades esportivas:\n";
    bool encontrou = false;
    for (int i = 0; i < totalParticipantes; i++) {
        if (participantes[i].participaDeAtividadesEsportivas) {
            cout << "- " << participantes[i].nome << " | Matrícula: " << participantes[i].matricula
                 << " | Curso: " << participantes[i].curso << " | E-mail: " << participantes[i].email << endl;
            encontrou = true;
        }
    }
    if (!encontrou) {
        cout << "Nenhum participante encontrado que participa de atividades esportivas.\n";
    }
}

// Lista inscrições feitas em uma data específica
void listarInscricoesPorData() {
    string data;
    cout << "Digite a data (DD/MM/AAAA): "; getline(cin, data);

    cout << "Inscrições feitas em " << data << ":\n";
    bool encontrou = false;
    for (int i = 0; i < totalInscricoes; i++) {
        if (inscricoes[i].dataInscricao == data) {
            cout << "- Participante: " << inscricoes[i].matriculaParticipante
                 << " | Atividade: " << inscricoes[i].nomeAtividade
                 << " | Presença: " << (inscricoes[i].presencaConfirmada ? "Confirmada" : "Não confirmada") << endl;
            encontrou = true;
        }
    }
    if (!encontrou) {
        cout << "Nenhuma inscrição encontrada para essa data.\n";
    }
}