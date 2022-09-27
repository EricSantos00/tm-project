#include "Quiz.h"

void questionQuiz()
{
	SortQuiz = rand() % TOTAL_QUIZ;

	//eQuiz[SortQuiz];
}

void quizTerritory(int a_iConn, int Item, int Territorio)
{

	pMob[a_iConn].QuizTerritory = Territorio + 1;
	pMob[a_iConn].ItemQuiz = Item;

	questionQuiz();
	
	pMob[a_iConn].CorrectQuiz = eQuiz[SortQuiz].Correct;
	SendQuizMessage(a_iConn, eQuiz[SortQuiz].Title, eQuiz[SortQuiz].Answer0,
		eQuiz[SortQuiz].Answer1, eQuiz[SortQuiz].Answer2, eQuiz[SortQuiz].Answer3, eQuiz[SortQuiz].Correct);
}
