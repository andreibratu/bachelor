package domain.statement.file;

import domain.expression.IExpression;
import domain.state.ProgramState;
import domain.state.file.DescriptorNotExistsException;
import domain.state.file.DictionaryFileTable;
import domain.state.heap.DictionaryHeap;
import domain.state.heap.InvalidMemoryAddressException;
import domain.state.symbol.DictSymbolTable;
import domain.state.symbol.UndeclaredVariableException;
import domain.statement.IStatement;
import domain.type.IType;
import domain.type.IntegerType;
import domain.type.StringType;
import domain.value.IValue;
import domain.value.IntegerValue;
import domain.value.StringValue;
import domain.type.IllegalTypeException;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.Map;

public class ReadFileStatement implements IStatement
{
    private IExpression filePathExpression;
    private String variableName;

    public ReadFileStatement(IExpression filePathExpression, String variableName)
    {
        this.filePathExpression = filePathExpression;
        this.variableName = variableName;
    }

    @Override
    public Map<String, IType> typeCheck(Map<String, IType> typeEnv) throws IllegalTypeException
    {
        IType expressionType = filePathExpression.typeCheck(typeEnv);
        IType stringType = new StringType();
        if(!expressionType.equals(stringType))
            throw new IllegalTypeException(this.toString(), stringType, expressionType);
        return typeEnv;
    }

    @Override
    public ProgramState execute(ProgramState state)
            throws IllegalTypeException, UndeclaredVariableException, DescriptorNotExistsException,
            IOException, InvalidMemoryAddressException
    {
        DictSymbolTable symbolTable = state.getSymbolTable();
        DictionaryHeap heap = state.getHeap();
        DictionaryFileTable fileTable = state.getFileTable();

        IValue<?> variable = symbolTable.queryVariable(variableName);
        if(!(variable instanceof IntegerValue))
            throw new IllegalTypeException(this.toString(), new IntegerType(), variable.getType());

        IValue<?> filepath = filePathExpression.evaluate(symbolTable, heap);
        if(!(filepath instanceof StringValue))
            throw new IllegalTypeException(this.toString(), new StringType(), filepath.getType());

        BufferedReader reader = fileTable.getDescriptor((StringValue) filepath);
        String line = reader.readLine();
        IntegerValue newValue = (line.length() != 0) ?
                new IntegerValue(Integer.parseInt(line)) : new IntegerType().defaultValue();
        symbolTable.updateVariable(variableName, newValue);
        return null;
    }

    @Override
    public Object clone() throws CloneNotSupportedException
    {
        ReadFileStatement clone = (ReadFileStatement) super.clone();
        clone.variableName = this.variableName;
        clone.filePathExpression = (IExpression) this.filePathExpression.clone();
        return clone;
    }

    @Override
    public String toString() {
        return "read("  + this.variableName + ", " + this.filePathExpression.toString() + ")";
    }
}
