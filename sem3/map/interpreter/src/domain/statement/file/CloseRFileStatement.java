package domain.statement.file;

import adt.dictionary.IDictionary;
import adt.dictionary.InvalidKeyException;
import domain.expression.IExpression;
import domain.state.ProgramState;
import domain.statement.IStatement;
import domain.type.StringType;
import domain.value.IValue;
import domain.value.StringValue;
import exception.io.DescriptorNotExistsException;
import exception.type.IllegalTypeException;
import exception.variable.UndeclaredVariableException;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseRFileStatement implements IStatement
{
    private IExpression filePathExpression;

    CloseRFileStatement(IExpression filePathExpression)
    {
        this.filePathExpression = filePathExpression;
    }

    @Override
    public ProgramState execute(ProgramState state)
            throws IllegalTypeException, UndeclaredVariableException, DescriptorNotExistsException, IOException
    {
        IDictionary<String, IValue> symbolTable = state.getSymbolTable();
        IDictionary<StringValue, BufferedReader> fileTable = state.getFileTable();

        IValue filepath = filePathExpression.evaluate(symbolTable);
        if(!(filepath.getType() instanceof StringType))
            throw new IllegalTypeException(this.toString(), new StringType(), filepath.getType());
        try
        {
            fileTable.lookUp((StringValue) filepath).close();
            fileTable.remove((StringValue) filepath);
        } catch (InvalidKeyException e)
        {
            throw new DescriptorNotExistsException(((StringValue) filepath).getValue());
        }
        return state;
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        CloseRFileStatement clone = (CloseRFileStatement) super.clone();
        clone.filePathExpression = (IExpression) this.filePathExpression.clone();
        return clone;
    }

    @Override
    public String toString() {
        return "close(" + this.filePathExpression + ")";
    }
}
