package view;

import adt.Dictionary;
import adt.MyList;
import adt.MyStack;
import controller.Controller;
import controller.IController;
import domain.expression.ArithmeticExpression;
import domain.expression.ValueExpression;
import domain.expression.VariableExpression;
import domain.operator.ArithmeticOperator;
import domain.state.ProgramState;
import domain.statement.*;
import domain.value.IntegerValue;
import repository.IRepository;
import repository.MemoryRepository;

public class Main {

    public static void main(String[] args) {
        IStatement simpleStatement = new CompoundStatement(
            new VarDeclStatement("a", new IntegerValue(6)),
            new PrintStatement(new VariableExpression("a"))
        );

        IStatement ex1 = new CompoundStatement(
            new VarDeclStatement("a", new IntegerValue(0)),
            new CompoundStatement(
                new VarDeclStatement("b", new IntegerValue(0)),
                new CompoundStatement(
                    new AssignmentStatement(
                        "a",
                        new ArithmeticExpression(
                            new ValueExpression(new IntegerValue(2)),
                            new ArithmeticExpression(
                                new ValueExpression(new IntegerValue(3)),
                                new ValueExpression(new IntegerValue(5)),
                                ArithmeticOperator.STAR),
                            ArithmeticOperator.PLUS)),
                    new CompoundStatement(
                        new AssignmentStatement(
                            "b",
                            new ArithmeticExpression(
                                    new VariableExpression("a"),
                                    new ValueExpression(new IntegerValue(1)),
                                    ArithmeticOperator.PLUS)),
                        new PrintStatement(new VariableExpression("b"))
                    ))
            )
        );
        ProgramState program = new ProgramState(
            new MyStack<>(),
            new Dictionary<>(),
            new MyList<>(),
            ex1
        );
        IRepository repository = new MemoryRepository();
        repository.addProgram(program);
        IController controller = new Controller(repository);
        try {
            controller.allSteps();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}