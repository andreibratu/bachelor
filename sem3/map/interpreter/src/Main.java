import controller.Controller;
import controller.IController;
import domain.expression.ArithmeticExpression;
import domain.expression.ReadHeapExpression;
import domain.expression.ValueExpression;
import domain.expression.VariableExpression;
import domain.operator.ArithmeticOperator;
import domain.state.ProgramState;
import domain.statement.*;
import domain.statement.control.CompoundStatement;
import domain.statement.file.CloseRFileStatement;
import domain.statement.file.OpenRFileStatement;
import domain.statement.file.ReadFileStatement;
import domain.statement.heap.HeapAllocationStatement;
import domain.statement.heap.WriteHeapStatement;
import domain.statement.print.PrintStatement;
import domain.statement.variable.VariableAssignmentStatement;
import domain.statement.variable.VariableDeclarationStatement;
import domain.type.IntegerType;
import domain.type.ReferenceType;
import domain.type.StringType;
import domain.value.IntegerValue;
import domain.value.ReferenceValue;
import domain.value.StringValue;
import repository.IRepository;
import repository.Repository;
import view.text.TextMenu;
import view.text.command.ExitCommand;
import view.text.command.RunExampleCommand;

public class Main {

    public static void main(String[] args) {
        IStatement ex1 = new CompoundStatement(
            new CompoundStatement(
                new VariableDeclarationStatement("a", new IntegerType()),
                new VariableDeclarationStatement("b", new IntegerType())
            ),
            new PrintStatement(new VariableExpression("a"))
        );

        IStatement ex2 = new CompoundStatement(
            new VariableDeclarationStatement("a", new IntegerType()),
            new CompoundStatement(
                new VariableDeclarationStatement("b", new IntegerType()),
                new CompoundStatement(
                    new VariableAssignmentStatement(
                        "a",
                        new ArithmeticExpression(
                            new ValueExpression(new IntegerValue(2)),
                            new ArithmeticExpression(
                                new ValueExpression(new IntegerValue(3)),
                                new ValueExpression(new IntegerValue(5)),
                                ArithmeticOperator.STAR),
                            ArithmeticOperator.PLUS)),
                    new CompoundStatement(
                        new VariableAssignmentStatement(
                            "b",
                            new ArithmeticExpression(
                                    new VariableExpression("a"),
                                    new ValueExpression(new IntegerValue(1)),
                                    ArithmeticOperator.PLUS)),
                        new PrintStatement(new VariableExpression("b"))
                    ))
            )
        );

        IStatement ex3 = new CompoundStatement(
            new VariableDeclarationStatement("foo", new StringType()),
            new CompoundStatement(
                new VariableAssignmentStatement("foo", new ValueExpression(new StringValue("test.txt"))),
                new CompoundStatement(
                    new OpenRFileStatement(new VariableExpression("foo")),
                    new CompoundStatement(
                        new VariableDeclarationStatement("a", new IntegerType()),
                        new CompoundStatement(
                            new ReadFileStatement(new VariableExpression("foo"), "a"),
                            new CompoundStatement(
                                new PrintStatement(new VariableExpression("a")),
                                new CloseRFileStatement(new VariableExpression("foo"))))))));

        IStatement ex4 = new CompoundStatement(
            new VariableDeclarationStatement("v", new ReferenceValue(new IntegerType())),
            new CompoundStatement(
                new HeapAllocationStatement("v", new ValueExpression(new IntegerValue(20))),
                new CompoundStatement(
                    new VariableDeclarationStatement("a", new ReferenceValue(new ReferenceType(new IntegerType()))),
                    new CompoundStatement(
                        new HeapAllocationStatement("a", new VariableExpression("v")),
                        new CompoundStatement(
                            new HeapAllocationStatement("v", new ValueExpression(new IntegerValue(50))),
                            new PrintStatement(new ReadHeapExpression(
                                new ReadHeapExpression(new VariableExpression("a"))))
                        )
                    )
                )
            )
        );

        ProgramState pr1 = new ProgramState(ex1);
        ProgramState pr2 = new ProgramState(ex2);
        ProgramState pr3 = new ProgramState(ex3);
        ProgramState pr4 = new ProgramState(ex4);

        IRepository repo1 = new Repository(pr1, "log1.txt");
        IRepository repo2 = new Repository(pr2, "log2.txt");
        IRepository repo3 = new Repository(pr3, "log3.txt");
        IRepository repo4 = new Repository(pr4, "log4.txt");

        IController ctrl1 = new Controller(repo1, false);
        IController ctrl2 = new Controller(repo2, false);
        IController ctrl3 = new Controller(repo3, false);
        IController ctrl4 = new Controller(repo4, true);

        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0", "exit"));
        menu.addCommand(new RunExampleCommand("1", ex1.toString(), ctrl1));
        menu.addCommand(new RunExampleCommand("2", ex2.toString(), ctrl2));
        menu.addCommand(new RunExampleCommand("3", ex3.toString(), ctrl3));
        menu.addCommand(new RunExampleCommand("4", ex4.toString(), ctrl4));
        menu.show();
    }
}