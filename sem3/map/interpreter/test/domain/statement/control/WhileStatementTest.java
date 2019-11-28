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
import domain.state.file.DescriptorExistsException;
import domain.state.file.DescriptorNotExistsException;
import domain.state.file.FileDoesNotExistException;
import domain.state.heap.InvalidMemoryAddressException;
import domain.state.symbol.UndeclaredVariableException;
import domain.state.symbol.VariableAlreadyDefinedException;
import domain.statement.IStatement;
import domain.statement.print.PrintStatement;
import domain.statement.variable.VariableAssignmentStatement;
import domain.statement.variable.VariableDeclarationStatement;
import domain.type.IllegalTypeException;
import domain.value.IntegerValue;
import org.junit.Test;
import org.junit.jupiter.api.AfterEach;
import repository.IRepository;
import repository.Repository;

import java.io.File;
import java.io.IOException;

import static junit.framework.TestCase.assertEquals;
import static junit.framework.TestCase.fail;

public class WhileStatementTest
{
    @Test(expected = IllegalTypeException.class)
    public void testWhileStatementInvalidCondition() throws IllegalTypeException
    {
        IStatement statement = new WhileStatement(
            new ValueExpression(new IntegerValue(6)),
            new PrintStatement(new ValueExpression(new IntegerValue(8)))
        );

        ProgramState mockState = new ProgramState(statement);
        IRepository mockRepository = new Repository(mockState, "testlog.txt");
        IController mockController = new Controller(mockRepository, false);

        try
        {
            mockController.allSteps();
        } catch (VariableAlreadyDefinedException| DescriptorExistsException |
                DescriptorNotExistsException | UndeclaredVariableException |
                IOException | FileDoesNotExistException | InvalidMemoryAddressException e)
        {
            fail(e.getMessage());
        }
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

        ProgramState state = new ProgramState(statement);
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
