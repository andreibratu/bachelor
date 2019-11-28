package domain.expression;

import controller.Controller;
import controller.IController;
import domain.state.ProgramState;
import domain.statement.IStatement;
import domain.statement.control.CompoundStatement;
import domain.statement.heap.HeapAllocationStatement;
import domain.statement.heap.WriteHeapStatement;
import domain.statement.variable.VariableAssignmentStatement;
import domain.statement.variable.VariableDeclarationStatement;
import domain.type.IntegerType;
import domain.type.ReferenceType;
import domain.value.IntegerValue;
import domain.value.ReferenceValue;
import org.junit.After;
import org.junit.Test;
import repository.IRepository;
import repository.Repository;

import java.io.File;

import static junit.framework.TestCase.assertEquals;
import static junit.framework.TestCase.fail;

public class HeapAllocationStatementTest
{
    @Test
    public void testHeapAllocationStatement()
    {
        IStatement statement = new CompoundStatement(
            new VariableDeclarationStatement("v", new ReferenceType(new IntegerType())),
            new CompoundStatement(
                new HeapAllocationStatement(
                        "v",
                        new ValueExpression(new ReferenceValue(new IntegerType()))
                ),
                new CompoundStatement(
                    new WriteHeapStatement(
                            "v",
                            new ValueExpression(new IntegerValue(20))
                    ),
                    new CompoundStatement(
                        new VariableDeclarationStatement("foo", new IntegerType()),
                        new VariableAssignmentStatement(
                                "foo",
                                new ReadHeapExpression(new VariableExpression("v"))
                        )
                    )
                )
            )
        );

        ProgramState mockState = new ProgramState(statement);
        IRepository mockRepository = new Repository(mockState, "testlog.txt");
        IController mockController = new Controller(mockRepository, true);

        try
        {
            mockController.allSteps();
            assertEquals(mockState.getSymbolTable().queryVariable("foo").getValue(), 20);
        } catch (Exception e)
        {
            fail(e.getMessage());
        }
    }

    @After
    public void cleanup() throws Exception
    {
        File file = new File("testlog.txt");
        if(!file.delete())
        {
            throw new Exception("HeapAllocStatTest: Could not remove side effect file!");
        }
    }
}
