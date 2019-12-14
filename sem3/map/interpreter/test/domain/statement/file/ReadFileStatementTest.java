package domain.statement.file;

import controller.Controller;
import controller.IController;
import domain.expression.ValueExpression;
import domain.expression.VariableExpression;
import domain.state.ProgramState;
import domain.statement.IStatement;
import domain.statement.control.CompoundStatement;
import domain.statement.variable.VariableAssignmentStatement;
import domain.statement.variable.VariableDeclarationStatement;
import domain.type.IllegalTypeException;
import domain.type.IntegerType;
import domain.type.StringType;
import domain.value.StringValue;
import org.junit.After;
import org.junit.Test;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import repository.IRepository;
import repository.Repository;

import java.io.File;

import static junit.framework.TestCase.assertEquals;
import static junit.framework.TestCase.fail;

public class ReadFileStatementTest
{
    @BeforeEach
    public void tearDown()
    {
        ProgramState.setGlobalId(1);
    }

    @AfterEach
    public void setUp()
    {
        ProgramState.setGlobalId(1);
    }

    @Test
    public void testReadingFile()
    {
        IStatement statement =
            new CompoundStatement(
                new VariableDeclarationStatement("foo", new StringType()),
                new CompoundStatement(
                    new VariableAssignmentStatement(
                        "foo",
                        new ValueExpression(new StringValue("test.txt"))),
                    new CompoundStatement(
                        new OpenRFileStatement(new VariableExpression("foo")),
                        new CompoundStatement(
                            new VariableDeclarationStatement("a", new IntegerType()),
                            new ReadFileStatement(new VariableExpression("foo"), "a")
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
        IController mockController = new Controller(mockRepository, true);
        try
        {
            mockController.allSteps();
            assertEquals(mockState.getSymbolTable().queryVariable("a").getValue(), 5);
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
            throw new Exception(
                "ReadFileStatementTest: Could not remove side effect file!"
            );
        }
    }
}
