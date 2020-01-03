package controller;

public interface IController
{
     void removeCompletedPrograms();

     void oneStepAllPrograms() throws InterruptedException;

     void allSteps() throws InterruptedException;
}
