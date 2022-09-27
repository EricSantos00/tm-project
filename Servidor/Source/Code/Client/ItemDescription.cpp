#include "main.h"
int teste;

int CreateObjectText(STRUCT_ITEM* item, char* line1, char* line2, char* line3, char* line4, char* line5, char* line6, char* line7, char* line8, char* line9, char* line10, int* color1, int* color2, int* color3, int* color4, int* color5, int* color6, int* color7, int* color8, int* color9, int* color10)
{
	memset(line2, 0x0, sizeof(line2));
	memset(line3, 0x0, sizeof(line3));
	memset(line4, 0x0, sizeof(line4));
	memset(line5, 0x0, sizeof(line5));
	memset(line6, 0x0, sizeof(line6));
	memset(line7, 0x0, sizeof(line7));
	memset(line8, 0x0, sizeof(line8));
	memset(line9, 0x0, sizeof(line9));
	memset(line10, 0x0, sizeof(line10));

	for (int i = 0; i < 3; i++)
	{
		if (item->stEffect[i].cEffect >= 116 && item->stEffect[i].cEffect <= 125)
		{
			if (item->sIndex >= 2330 && item->sIndex <= 2389) continue;

			switch (item->stEffect[i].cEffect)
			{
			case 118:
			{
				sprintf(line1, "[Cor: Verde]");
				*color1 = Yellow;
				return 1;
			}
			case 119:
			{
				sprintf(line1, "[Cor: Prateado]");
				*color1 = Yellow;
				return 1;
			}
			case 120:
			{
				sprintf(line1, "[Cor: Preto]");
				*color1 = Yellow;
				return 1;
			}
			case 121:
			{
				sprintf(line1, "[Cor: Roxo]");
				*color1 = Yellow;
				return 1;
			}
			case 122:
			{
				sprintf(line1, "[Cor: Marrom]");
				*color1 = Yellow;
				return 1;
			}
			case 123:
			{
				sprintf(line1, "[Cor: Rosa]");
				*color1 = Yellow;
				return 1;
			}
			case 124:
			{
				sprintf(line1, "[Cor: Amarelo]");
				*color1 = Yellow;
				return 1;
			}
			case 125:
			{
				sprintf(line1, "[Cor: Azul Claro]");
				*color1 = Yellow;
				return 1;
			}
			}
		}
	}

	if (item->sIndex == 5548)
	{
		sprintf_s(line6, 128, "Elixir que torna sua montaria imortal.");
		*color6 = White;
		sprintf_s(line8, 128, "- Não é necessario uso de ração.");
		*color8 = Yellow;
		sprintf_s(line9, 128, "- Ativo somente no personagem.");
		*color9 = Yellow;
		sprintf_s(line10, 128, "- Duração: 24 horas.");
		*color10 = Yellow;
		return 10;
	}
	if (item->sIndex == 5549)
	{
		sprintf_s(line2, 128, "[Item Premium]");
		*color2 = Yellow;
		sprintf_s(line4, 128, "Item utilizado para registrar um grupo para");
		*color4 = Orange;
		sprintf_s(line5, 128, "participar do Calabouço Zumbi.");
		*color5 = Orange;
		sprintf_s(line7, 128, "Registros disponível nos minutos 56 á 59.");
		*color7 = Yellow;
		sprintf_s(line8, 128, "Minimo 06 participantes no grupo para acessar a área.");
		*color8 = Yellow;
		sprintf_s(line9, 128, "Recomendável a utilização de bloods devido a quantidade de monstros.");
		*color9 = Yellow;
		sprintf_s(line10, 128, "Acesse nosso site para obter informações sobre o Calabouço.");
		*color10 = White;
		return 10;
	}
	if (item->sIndex == 5565)
	{
		sprintf_s(line1, 128, "[Item Premium]");
		*color1 = Yellow;
		sprintf_s(line3, 128, "Item utilizado para purificar o");
		*color3 = White;
		sprintf_s(line4, 128, "Amuleto Lendário aumentando o seu level.");
		*color4 = White;
		sprintf_s(line6, 128, "Level 0 para Level 1.");
		*color6 = Orange;
		sprintf_s(line8, 128, "Somente em itens acima de +9.");
		*color8 = Yellow;
		sprintf_s(line10, 128, "Chance de sucesso: 80 porcento.");
		*color10 = Yellow;
		return 10;
	}
	if (item->sIndex == 5566)
	{
		sprintf_s(line1, 128, "[Item Premium]");
		*color1 = Yellow;
		sprintf_s(line3, 128, "Item utilizado para purificar o");
		*color3 = White;
		sprintf_s(line4, 128, "Amuleto Lendário aumentando o seu level.");
		*color4 = White;
		sprintf_s(line6, 128, "Level 1 para Level 2.");
		*color6 = Orange;
		sprintf_s(line8, 128, "Somente em itens acima de +9.");
		*color8 = Yellow;
		sprintf_s(line10, 128, "Chance de sucesso: 80 porcento.");
		*color10 = Yellow;
		return 10;
	}
	if (item->sIndex == 5567)
	{
		sprintf_s(line1, 128, "[Item Premium]");
		*color1 = Yellow;
		sprintf_s(line3, 128, "Item utilizado para purificar o");
		*color3 = White;
		sprintf_s(line4, 128, "Amuleto Lendário aumentando o seu level.");
		*color4 = White;
		sprintf_s(line6, 128, "Level 2 para Level 3.");
		*color6 = Orange;
		sprintf_s(line8, 128, "Somente em itens acima de +9.");
		*color8 = Yellow;
		sprintf_s(line10, 128, "Chance de sucesso: 80 porcento.");
		*color10 = Yellow;
		return 10;
	}
	if (item->sIndex == 5568)
	{
		sprintf_s(line1, 128, "[Item Premium]");
		*color1 = Yellow;
		sprintf_s(line3, 128, "Item utilizado para purificar o");
		*color3 = White;
		sprintf_s(line4, 128, "Amuleto Lendário aumentando o seu level.");
		*color4 = White;
		sprintf_s(line6, 128, "Level 3 para Level 4.");
		*color6 = Orange;
		sprintf_s(line8, 128, "Somente em itens acima de +9.");
		*color8 = Yellow;
		sprintf_s(line10, 128, "Chance de sucesso: 80 porcento.");
		*color10 = Yellow;
		return 10;
	}
	if (item->sIndex == 5569)
	{
		sprintf_s(line1, 128, "[Item Premium]");
		*color1 = Yellow;
		sprintf_s(line3, 128, "Item utilizado para purificar o");
		*color3 = White;
		sprintf_s(line4, 128, "Amuleto Lendário aumentando o seu level.");
		*color4 = White;
		sprintf_s(line6, 128, "Level 4 para Level 5.");
		*color6 = Orange;
		sprintf_s(line8, 128, "Somente em itens acima de +9.");
		*color8 = Yellow;
		sprintf_s(line10, 128, "Chance de sucesso: 80 porcento.");
		*color10 = Yellow;
		return 10;
	}
	if (item->sIndex == 5570)
	{
		sprintf_s(line1, 128, "[Item Premium]");
		*color1 = Yellow;
		sprintf_s(line3, 128, "Item utilizado para purificar o");
		*color3 = White;
		sprintf_s(line4, 128, "Amuleto Lendário aumentando o seu level.");
		*color4 = White;
		sprintf_s(line6, 128, "Aumento nas atribuições do Lendário.");
		*color6 = Orange;
		sprintf_s(line8, 128, "Somente em itens acima de +9.");
		*color8 = Yellow;
		sprintf_s(line10, 128, "Chance de sucesso: 80 porcento.");
		*color10 = Yellow;
		return 10;
	}
	if (item->sIndex == 5573)
	{
		sprintf_s(line1, 128, "[Item de Quest]");
		*color1 = Yellow;
		sprintf_s(line4, 128, "Elixir valioso que permite");
		*color4 = White;
		sprintf_s(line5, 128, "permanecer em locais de caça por mais tempo");
		*color5 = White;
		sprintf_s(line8, 128, "- Perde o efeito, se deslogar ou morrer.");
		*color8 = Yellow;
		sprintf_s(line9, 128, "- Aumenta a permanência em quests.");
		*color9 = Yellow;
		sprintf_s(line10, 128, "- Efeito acumulativo em até (20) minutos.");
		*color10 = Yellow;
		return 10;
	}

	if (item->sIndex == 413)
	{
		char buffer[12];
		*(short*)&buffer[0] = 12;
		*(short*)&buffer[4] = 0xD00;
		*(short*)&buffer[6] = GetClientID();
		SendPacket(&buffer[0], 12);

		sprintf_s(line1, 128, "[Item Refinamento]");
		*color1 = Yellow;
		sprintf_s(line3, 128, "Item utilizado para refinar");
		*color3 = White;
		sprintf_s(line4, 128, "sets, armas,acessorios etc...");
		*color4 = White;
		sprintf_s(line6, 128, "Aumenta o lvl do item em +1");
		*color6 = Orange;
		sprintf_s(line8, 128, "em caso de sucesso");
		*color8 = Orange;
		sprintf_s(line10, 128, "itens Até +9 e +10");
		*color10 = Yellow;
		return 10;

	}

	if (item->sIndex >= 2300 && item->sIndex <= 2329)
	{
		for (int a = 0; a <= 1; a++)
		{
			if (item->stEffect[a].cValue <= 0)
			{
				sprintf_s(line1, 128, "Aguardando incubação.");
				*color1 = CornBlueName;

				return 10;
			}
		}
	}

	//Macro Eternal
	if (item->sIndex == 3789)
	{
		sprintf_s(line1, 128, "[Item Premium]");
		*color1 = Yellow;
		sprintf_s(line3, 128, "efetivo apenas quando equipado.");
		*color3 = White;
		sprintf_s(line4, 128, "comsumível apenas quando equipado.");
		*color4 = White;
		sprintf_s(line6, 128, "[ATRIBUTOS:]");
		*color6 = Orange;
		sprintf_s(line7, 128, "Macro auto perga M e A");
		*color7 = Yellow;
		sprintf_s(line8, 128, " ");
		*color8 = Yellow;
		return 10;
	}

	//Contrato Montaria
	if (item->sIndex >= 3790 && item->sIndex <= 3791)
	{
		sprintf_s(line1, 128, "[Item Premium]");
		*color1 = Yellow;
		sprintf_s(line3, 128, "Contrato para receber beneficios.");
		*color3 = White;
		sprintf_s(line4, 128, "Clique direito para usar.");
		*color4 = White;
		sprintf_s(line6, 128, "[ATRIBUTOS:]");
		*color6 = Orange;
		sprintf_s(line7, 128, "Receba uma Montaria ");
		*color7 = Yellow;
		sprintf_s(line8, 128, "de acordo com o tipo de contrato ");
		*color8 = Yellow;
		return 10;
	}

	//Contrato Macro
	if (item->sIndex == 3792)
	{
		sprintf_s(line1, 128, "[Item Premium]");
		*color1 = Yellow;
		sprintf_s(line3, 128, "Contrato para receber beneficios.");
		*color3 = White;
		sprintf_s(line4, 128, "Clique direito para usar.");
		*color4 = White;
		sprintf_s(line6, 128, "[ATRIBUTOS:]");
		*color6 = Orange;
		sprintf_s(line7, 128, "Receba uma Macro para agua ");
		*color7 = Yellow;
		sprintf_s(line8, 128, "Macro(7d) consumivel ao equipar ");
		*color8 = Yellow;
		return 10;
	}

	//Kit +1
	if (item->sIndex == 3793)
	{
		sprintf_s(line1, 128, "[Item Premium]");
		*color1 = Yellow;
		sprintf_s(line3, 128, "Kit de joias.");
		*color3 = White;
		sprintf_s(line4, 128, "Clique direito para usar.");
		*color4 = White;
		sprintf_s(line6, 128, "[ATRIBUTOS:]");
		*color6 = Orange;
		sprintf_s(line7, 128, "Recebe uma joia aleatoria (4x)");
		*color7 = Yellow;
		sprintf_s(line8, 128, "Recebe uma pedra do Sabio ");
		*color8 = Yellow;
		return 10;
	}

	//Kit +1
	if (item->sIndex == 3794)
	{
		sprintf_s(line1, 128, "[Item Premium]");
		*color1 = Yellow;
		sprintf_s(line3, 128, "Bau de joias.");
		*color3 = White;
		sprintf_s(line4, 128, "Clique direito para usar.");
		*color4 = White;
		sprintf_s(line6, 128, "[ATRIBUTOS:]");
		*color6 = Orange;
		sprintf_s(line7, 128, "Recebe uma joia aleatoria");
		*color7 = Yellow;
		return 10;
	}

	if (item->sIndex >= 3210 && item->sIndex <= 3212)
	{
		sprintf_s(line1, 128, "[Item Premium]");
		*color1 = Yellow;
		sprintf_s(line3, 128, "Box de Eventos.");
		*color3 = White;
		sprintf_s(line4, 128, "Clique direito para usar.");
		*color4 = White;
		sprintf_s(line6, 128, "[ATRIBUTOS:]");
		*color6 = Orange;
		sprintf_s(line7, 128, "Receba um item aleatorio do evento");
		*color7 = Yellow;
		return 10;
	}
	//Bau do Guerreiro
	if (item->sIndex == 3213)
	{
		sprintf_s(line1, 128, "[Item Premium]");
		*color1 = Yellow;
		sprintf_s(line2, 128, "Bau Premium.");
		*color2 = White;
		sprintf_s(line3, 128, "Clique direito para usar.");
		*color3 = White;
		sprintf_s(line4, 128, "[ATRIBUTOS:]");
		*color4 = Orange;
		sprintf_s(line5, 128, "1x Poção Divina(30d)");
		*color5 = Yellow;
		sprintf_s(line6, 128, "1x Poção Saude(30d)");
		*color6 = Yellow;
		sprintf_s(line7, 128, "2x Bolsa do Andarilho");
		*color7 = Yellow;
		sprintf_s(line8, 128, "1x Elixir da Coragem(30d)");
		*color8 = Yellow;
		sprintf_s(line9, 128, "1x Sephira (30d)");
		*color9 = Yellow;
		return 10;
	}

	//Moedas Epoints.
	if (item->sIndex > 3015 && item->sIndex < 3020)
	{
		sprintf_s(line1, 128, "[Item Premium]");
		*color1 = Yellow;
		sprintf_s(line3, 128, "Moeda de Epoints");
		*color3 = White;
		sprintf_s(line4, 128, "comsumível ao clique direito");
		*color4 = White;
		sprintf_s(line6, 128, "[ATRIBUTOS:]");
		*color6 = Orange;
		sprintf_s(line7, 128, "Pontos de Epoints");
		*color7 = Yellow;
		sprintf_s(line8, 128, "de acordo com sua raridade. ");
		*color8 = Yellow;
		return 10;
	}


	if (item->sIndex >= 794 && item->sIndex <= 799)
	{
		std::string nTerritory = "";
		switch (item->sIndex)
		{
		case 794:
			nTerritory = "Arima";
			break;
		case 795:
			nTerritory = "Barnel";
			break;
		case 796:
			nTerritory = "Campus";
			break;
		case 797:
			nTerritory = "Gobi";
			break;
		case 798:
			nTerritory = "IceCrow";
			break;
		case 799:
			nTerritory = "NONE";
			break;
		default:
			break;
		}
		sprintf_s(line1, 128, "[Item Guild]");
		*color1 = Yellow;
		sprintf_s(line3, 128, "Chave para Abrir Território");
		*color3 = White;
		sprintf_s(line4, 128, "comsumível ao clique direito");
		*color4 = White;
		sprintf_s(line6, 128, "[ATRIBUTOS:]");
		*color6 = Orange;
		sprintf_s(line7, 128, "Libera acesso ao território:");
		*color7 = Yellow;
		sprintf_s(line8, 128, "[%s].",nTerritory.c_str());
		*color8 = Yellow;
		return 10;
	}

	if (item->sIndex >= 2330 && item->sIndex <= 2389) return 0;

	//switch (item->sIndex)
	//{

	//}
	return 0;
}