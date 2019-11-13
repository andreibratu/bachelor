package domain.statement.file;

import adt.dictionary.IDictionary;
import domain.expression.IExpression;
import domain.state.ProgramState;
import domain.statement.IStatement;
import domain.type.StringType;
import domain.value.IValue;
import domain.value.StringValue;
import exception.io.DescriptorExistsException;
import exception.io.FileDoesNotExistException;
import exception.type.IllegalTypeException;
import exception.variable.UndeclaredVariableException;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;

public class OpenRFileStatement implements IStatement
{
    private IExpression filepath;

    public OpenRFileStatement(IExpression expression)
    {
        this.filepath = expression;
    }

    @Override
    public ProgramState execute(ProgramState state)
        throws IllegalTypeException, UndeclaredVariableException,
            DescriptorExistsException, FileDoesNotExistException
    {
        IDictionary<String, IValue> symbolTable = state.getSymbolTable();
        IDictionary<StringValue, BufferedReader> fileTable = state.getFileTable();

        IValue result = filepath.evaluate(symbolTable);
        if(!(result instanceof StringValue))
            throw new IllegalTypeException(this.toString(), new StringType(), result.getType());
        if(fileTable.isDefined((StringValue) result))
            throw new DescriptorExistsException(((StringValue) result).getValue());
        try
        {
            FileReader reader = new FileReader(((StringValue) result).getValue());
            BufferedReader buffered = new BufferedReader(reader);
            fileTable.put((StringValue) result.getValue(), buffered);
            return state;
        } catch (FileNotFoundException e) {
            throw new FileDoesNotExistException(((StringValue) result).getValue());
        }
    }

    @Override
    public String toString() {
        return "open(" + this.filepath.toString() + ")";
    }

    @Override
    public Object clone() throws CloneNotSupportedException
    {
        OpenRFileStatement clone = (OpenRFileStatement) super.clone();
        clone.filepath = (IExpression) this.filepath.clone();
        return clone;
    }
}
