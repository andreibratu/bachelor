package domain.statement.control;

import controller.Controller;
import controller.IController;
import domain.expression.ArithmeticExpression;
import domain.expression.LogicalExpression;
import domain.expression.ValueExpression;
import domain.expression.VariableExpression;
import domain.operator.ArithmeticOperator;
import domain.operator.LogicalOperator;
import domain.state.ProgramState;
import domain.statement.IStatement;
import domain.statement.print.PrintStatement;
import domain.statement.variable.VariableAssignmentStatement;
import domain.statement.variable.VariableDeclarationStatement;
import domain.type.IllegalTypeException;
import domain.value.IntegerValue;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import repository.IRepository;
import repository.Repository;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.PrintStream;

import static junit.framework.TestCase.assertEquals;
import static junit.framework.TestCase.fail;

public class WhileStatementTest
{
    private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
    private final ByteArrayOutputStream errContent = new ByteArrayOutputStream();
    private final PrintStream originalOut = System.out;
    private final PrintStream originalErr = System.err;

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

    @Before
    public void setUpStreams()
    {
        System.setOut(new PrintStream(outContent));
        System.setErr(new PrintStream(errContent));
    }

    @After
    public void restoreStreams()
    {
        System.setOut(originalOut);
        System.setErr(originalErr);
    }

    @Test(expected = IllegalTypeException.class)
    public void testWhileStatementInvalidCondition() throws IllegalTypeException
    {
        IStatement statement = new WhileStatement(
            new ValueExpression(new IntegerValue(6)),
            new PrintStatement(new ValueExpression(new IntegerValue(8)))
        );

        new ProgramState(statement);
        fail("IllegalType should have been thrown by invalid condition");
    }

    @Test
    public void testWhileStatement()
    {
        IStatement statement = new CompoundStatement(
            new VariableDeclarationStatement("a", new IntegerValue(6)),
            new CompoundStatement(
                new VariableDeclarationStatement("b", new IntegerValue(2)),
                new WhileStatement(
                    new LogicalExpression(
                        new VariableExpression("b"),
                        new ValueExpression(new IntegerValue(0)),
                        LogicalOperator.GT
                    ),
                    new CompoundStatement(
                        new VariableAssignmentStatement(
                                "a",
                                new ArithmeticExpression(
                                        new VariableExpression("a"),
                                        new ValueExpression(new IntegerValue(2)),
                                        ArithmeticOperator.STAR
                                )
                        ),
                        new VariableAssignmentStatement(
                                "b",
                                new ArithmeticExpression(
                                    new VariableExpression("b"),
                                    new ValueExpression(new IntegerValue(1)),
                                    ArithmeticOperator.MINUS
                                )
                        )
                    )
                )
            )
        );

        ProgramState state = null;
        try {
            state = new ProgramState(statement);
        } catch (IllegalTypeException e) {
            fail(e.getMessage());
        }
        IRepository mockRepository = new Repository(state, "testlog.txt");
        IController mockController = new Controller(mockRepository, false);

        try
        {
            mockController.allSteps();
            assertEquals(state.getSymbolTable().queryVariable("a").getValue(), 24);
        } catch (Exception e)
        {
            fail(e.getMessage());
        }
    }

    @AfterEach
    public void cleanup()
    {
        File sideEffect = new File("testlog.txt");
        if(!sideEffect.delete())
        {
            fail("WhileStatTest: Could not remove side effect file!");
        }
    }
}
