#include "ProcessClientMessage.h"

void Exec_MSG_SetShortSkill(int conn, char* pMsg)
{
	MSG_SetShortSkill* m = (MSG_SetShortSkill*)pMsg;

	memcpy(pMob[conn].MOB.SkillBar, m->Skill1, 4);
	memcpy(pUser[conn].CharShortSkill, m->Skill2, 16);
}


/*Bom, pra voces praticarem programação deixarei um desafio :)*/
/*Logo abaixo terá uma tabela das id's da 9ª a 12ª skill que ficam no skillbar*/
/*O desafio de vocês é fazer um for concertando a skillbar, Boa sorte a Todos*/
/*By Swedka :D*/

/* // All new skill's Index //
105 106 107 108 TK
109 110 111 112
113 114 115 116

117 118 119 120 FM
121 122 123 124
125 126 127 128

129 130 131 132 BM
133 134 135 136
137 138 139 140

141 142 143 144 HT
145 146 147 148
149 150 151 152
*/