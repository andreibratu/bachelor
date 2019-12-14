package domain.statement.fork;

import controller.Controller;
import controller.IController;
import domain.expression.ReadHeapExpression;
import domain.expression.ValueExpression;
import domain.expression.VariableExpression;
import domain.state.ProgramState;
import domain.statement.IStatement;
import domain.statement.control.CompoundStatement;
import domain.statement.heap.HeapAllocationStatement;
import domain.statement.heap.WriteHeapStatement;
import domain.statement.print.PrintStatement;
import domain.statement.variable.VariableAssignmentStatement;
import domain.statement.variable.VariableDeclarationStatement;
import domain.type.IllegalTypeException;
import domain.type.IntegerType;
import domain.type.ReferenceType;
import domain.value.IValue;
import domain.value.IntegerValue;
import org.junit.Test;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import repository.IRepository;
import repository.Repository;

import java.util.Arrays;
import java.util.List;

import static junit.framework.TestCase.assertEquals;
import static junit.framework.TestCase.fail;

public class ForkStatementTest
{
    @BeforeEach
    public static void setUp()
    {
        ProgramState.setGlobalId(1);
    }

    @AfterEach
    public static void tearDown()
    {
        ProgramState.setGlobalId(1);
    }

    @Test
    public void testForkStatement()
    {
        IStatement statement = new CompoundStatement(
            new VariableDeclarationStatement("v", new IntegerType()),
            new CompoundStatement(
                new VariableDeclarationStatement(
                    "a",
                    new ReferenceType(new IntegerType())
                ),
                new CompoundStatement(
                    new VariableAssignmentStatement(
                        "v",
                        new ValueExpression(new IntegerValue(10))
                    ),
                    new CompoundStatement(
                        new HeapAllocationStatement(
                            "a",
                            new ValueExpression(new IntegerValue(22))
                        ),
                        new CompoundStatement (
                            new ForkStatement(
                                new CompoundStatement(
                                    new WriteHeapStatement(
                                        "a",
                                        new ValueExpression(new IntegerValue(30))),
                                    new CompoundStatement(
                                        new VariableAssignmentStatement(
                                            "v",
                                            new ValueExpression(new IntegerValue(32))),
                                        new CompoundStatement(
                                            new PrintStatement(new VariableExpression("v")),
                                            new PrintStatement(
                                                new ReadHeapExpression(new VariableExpression("a"))
                                            )
                                        )
                                    )
                                )
                            ),
                            new CompoundStatement(
                                new PrintStatement(new VariableExpression("v")),
                                new PrintStatement(new ReadHeapExpression(new VariableExpression("a")))
                            )
                        )
                    )
                )
            )
        );

        ProgramState.setGlobalId(1);

        ProgramState programState = null;
        try {
            programState = new ProgramState(statement);
        } catch (IllegalTypeException e) {
            fail(e.getMessage());
        }
        IRepository repository = new Repository(programState, "testlog.txt");
        IController controller = new Controller(repository, true);

        try
        {
            controller.allSteps();
            assertEquals(3, ProgramState.getGlobalIdId());
            List<IValue<?>> output = programState.getOut();
            List<IValue<?>> expected = Arrays.asList(
                new IntegerValue(10), new IntegerValue(30),
                new IntegerValue(32), new IntegerValue(30)
            );
            output.containsAll(expected);
        } catch (InterruptedException e)
        {
            fail(e.getMessage());
        }
    }
}
