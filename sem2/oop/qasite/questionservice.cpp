#include <algorithm>
#include "questionservice.h"

QuestionService::QuestionService()
{

}

void QuestionService::sortByNumberAnswers(QVector<Question> &questions)
{
    auto pred = [](const Question& a, const Question& b)
    {
        return a.answers.size() > b.answers.size();
    };
    std::sort(questions.begin(), questions.end(), pred);
}

Question QuestionService::filterByQuery(const QVector<Question> &questions, const QString &text)
{
    QVector<int> score;
    std::transform(questions.begin(),
                   questions.end(),
                   std::back_inserter(score),
                   [&text](const Question& q)
    {
       auto qText = q.text.toLower();
       int compLen = std::min(qText.size(), text.size());
       int score = 0;
       for(int i = 0; i < compLen; i++)
       {
           if(qText[i] == q.text[i])
           {
               score++;
           }
       }
       return score;
    });
    auto bestScoreIt = std::max_element(score.begin(), score.end());
    Question bestQuestion = questions[std::distance(score.begin(), bestScoreIt)];
    std::sort(bestQuestion.answers.begin(),
              bestQuestion.answers.end(),
              [](const Answer &a, const Answer &b)
    {
       return a.votes > b.votes;
    });
    return bestQuestion;
}
