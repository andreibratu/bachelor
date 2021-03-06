package domain.statement.heap;

import controller.Controller;
import controller.IController;
import domain.expression.ReadHeapExpression;
import domain.expression.ValueExpression;
import domain.expression.VariableExpression;
import domain.state.ProgramState;
import domain.statement.IStatement;
import domain.statement.control.CompoundStatement;
import domain.statement.variable.VariableAssignmentStatement;
import domain.statement.variable.VariableDeclarationStatement;
import domain.type.IllegalTypeException;
import domain.type.IntegerType;
import domain.type.ReferenceType;
import domain.value.IntegerValue;
import domain.value.ReferenceValue;
import org.junit.Test;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import repository.IRepository;
import repository.Repository;

import java.io.File;

import static junit.framework.TestCase.assertEquals;
import static junit.framework.TestCase.fail;

public class HeapStatementIntegrationTest
{
    @AfterEach
    public static void setUp()
    {
        ProgramState.setGlobalId(1);
    }

    @BeforeEach
    public static void tearDown()
    {
        ProgramState.setGlobalId(1);
    }

    /** Allocate an integer value on the heap and attempt to read it*/
    @Test
    public void testAllocationDereferenceMechanism()
    {
        IStatement statement = new CompoundStatement(
            new VariableDeclarationStatement("v", new ReferenceType(new IntegerType())),
            new CompoundStatement(
                new HeapAllocationStatement(
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
        );

        ProgramState mockState = null;
        try {
            mockState = new ProgramState(statement);
        } catch (IllegalTypeException e) {
            fail(e.getMessage());
        }
        IRepository mockRepository = new Repository(mockState, "testlog.txt");
        IController mockController = new Controller(mockRepository, false);

        try
        {
            mockController.allSteps();
            assertEquals(mockState.getSymbolTable().queryVariable("foo").getValue(), 20);
        } catch (Exception e)
        {
            fail(e.getMessage());
        }
    }

    /** Test heap write/ read operations on a reference to reference */
    @Test
    public void testReferenceToReferenceMechanism()
    {
        IStatement statement = new CompoundStatement(
            new VariableDeclarationStatement("a", new ReferenceType(new IntegerType())),
            new CompoundStatement(
                new HeapAllocationStatement(
                    "a",
                    new ValueExpression(new IntegerValue(50))
                ),
                new CompoundStatement(
                    new WriteHeapStatement("a", new ValueExpression(new IntegerValue(42))),
                    new CompoundStatement(
                        new VariableDeclarationStatement(
                        "b",
                                new ReferenceType(new ReferenceType(new IntegerType()))
                        ),
                        new CompoundStatement(
                            new HeapAllocationStatement(
                    "b",
                                new VariableExpression("a")
                            ),
                            new CompoundStatement(
                                new VariableDeclarationStatement("foo", new IntegerType()),
                                new VariableAssignmentStatement(
                                "foo",
                                    new ReadHeapExpression(
                                        new ReadHeapExpression(new VariableExpression("b"))
                                    )
                                )
                            )
                        )
                    )
                )
            )
        );

        ProgramState mockState = null;
        try {
            mockState = new ProgramState(statement);
        } catch (IllegalTypeException e) {
            fail(e.getMessage());
        }
        IRepository mockRepository = new Repository(mockState, "testlog.txt");
        IController mockController = new Controller(mockRepository, false);

        try
        {
            mockController.allSteps();
            assertEquals(mockState.getSymbolTable().queryVariable("foo").getValue(), 42);
        } catch (Exception e)
        {
            fail(e.getMessage());
        }
    }

    @Test
    public void testMultipleAllocationSameReference()
    {
        IStatement statement = new CompoundStatement(
            new VariableDeclarationStatement("v", new ReferenceValue(new IntegerType())),
            new CompoundStatement(
                new HeapAllocationStatement("v", new ValueExpression(new IntegerValue(20))),
                new CompoundStatement(
                    new VariableDeclarationStatement(
                            "a",
                            new ReferenceValue(new ReferenceType(new IntegerType()))),
                    new CompoundStatement(
                        new HeapAllocationStatement("a", new VariableExpression("v")),
                        new CompoundStatement(
                            new HeapAllocationStatement("v", new ValueExpression(new IntegerValue(50))),
                            new CompoundStatement(
                                new VariableDeclarationStatement("foo", new IntegerType()),
                                new VariableAssignmentStatement(
                                    "foo",
                                    new ReadHeapExpression(
                                        new ReadHeapExpression(new VariableExpression("a"))
                                    )
                                )
                            )
                        )
                    )
                )
            )
        );

        ProgramState mockState = null;
        try {
            mockState = new ProgramState(statement);
        } catch (IllegalTypeException e) {
            fail(e.getMessage());
        }
        IRepository mockRepository = new Repository(mockState, "testlog.txt");
        IController mockController = new Controller(mockRepository, false);

        try
        {
            mockController.allSteps();
            assertEquals(50, mockState.getSymbolTable().queryVariable("foo").getValue());
        } catch (Exception e)
        {
            fail(e.getMessage());
        }
    }

    @AfterEach
    public void cleanup() throws Exception
    {
        File file = new File("testlog.txt");
        if(!file.delete())
        {
            throw new Exception("HeapAllocStatTest: Could not remove side effect file!");
        }
    }
}
