package domain.statement.file;

import adt.dictionary.IDictionary;
import adt.dictionary.InvalidKeyException;
import domain.expression.IExpression;
import domain.state.ProgramState;
import domain.statement.IStatement;
import domain.type.IType;
import domain.type.IntegerType;
import domain.type.StringType;
import domain.value.IValue;
import domain.value.IntegerValue;
import domain.value.StringValue;
import exception.io.DescriptorNotExistsException;
import exception.type.IllegalTypeException;
import exception.variable.UndeclaredVariableException;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFileStatement implements IStatement
{
    private IExpression filepathExpression;
    private String variableName;

    @Override
    public ProgramState execute(ProgramState state)
            throws IllegalTypeException, UndeclaredVariableException, DescriptorNotExistsException, IOException
    {
        IDictionary<String, IValue> symbolTable = state.getSymbolTable();
        IDictionary<StringValue, BufferedReader> fileTable = state.getFileTable();

        IType variableType = null;
        try {
            variableType = symbolTable.lookUp(variableName).getType();
        } catch (InvalidKeyException e) {
            throw new UndeclaredVariableException(variableName);
        }
        if(!(variableType instanceof IntegerType))
            throw new IllegalTypeException(this.toString(), new IntegerType(), variableType);
        IValue filepath = filepathExpression.evaluate(symbolTable);
        if(!(filepath.getType() instanceof StringType))
            throw new IllegalTypeException(this.toString(), new StringType(), filepath.getType());
        BufferedReader reader;
        try {
            reader = fileTable.lookUp((StringValue) filepath);
        } catch (InvalidKeyException e) {
            throw new DescriptorNotExistsException(((StringValue) filepath).getValue());
        }
        String line = reader.readLine();
        IntegerValue newValue = (line.length() != 0) ?
                new IntegerValue(Integer.parseInt(line)) : new IntegerType().defaultValue();
        symbolTable.put(variableName, newValue);
        return state;
    }

    @Override
    public Object clone() throws CloneNotSupportedException
    {
        ReadFileStatement clone = (ReadFileStatement) super.clone();
        clone.variableName = this.variableName;
        clone.filepathExpression = (IExpression) this.filepathExpression.clone();
        return clone;
    }

    @Override
    public String toString() {
        return "readValue("  + this.variableName.toString() + ", " + this.filepathExpression.toString() + ")";
    }
}
