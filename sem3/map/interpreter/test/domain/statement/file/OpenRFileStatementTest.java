package domain.statement.file;

import domain.expression.ValueExpression;
import domain.state.ProgramState;
import domain.statement.IStatement;
import domain.type.IllegalTypeException;
import domain.value.StringValue;
import org.junit.Test;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;

import java.io.File;
import java.io.IOException;

import static org.junit.Assert.fail;

public class OpenRFileStatementTest
{
    @AfterAll
    public static void tearDown()
    {
        ProgramState.setGlobalId(1);
    }

    @BeforeEach
    public void setUp()
    {
        ProgramState.setGlobalId(1);
        File testFile = new File("test.txt");
        try
        {
            if(!testFile.createNewFile())
            {
                fail("OpenRFileStatementTest: Could not create test file!");
            }
        } catch (IOException e)
        {
            fail(e.getMessage());
        }
    }

    @AfterEach
    public void cleanUp()
    {
        File testFile = new File("test.txt");
        if(!testFile.delete())
        {
            fail("OpenRFileStatementTest: Could not remove test file!");
        }
    }

    @Test
    public void testFileOpening()
    {
        IStatement statement = new OpenRFileStatement(
            new ValueExpression(new StringValue("test.txt"))
        );
        ProgramState mockState = null;
        try {
            mockState = new ProgramState(statement);
        } catch (IllegalTypeException e) {
            fail(e.getMessage());
        }
        try
        {
            statement.execute(mockState);
            mockState.getFileTable().getDescriptor(new StringValue("test.txt"));
        } catch (Exception e)
        {
            fail(e.getMessage());
        }
    }
}
