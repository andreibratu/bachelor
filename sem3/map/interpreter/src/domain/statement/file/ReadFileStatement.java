package domain.statement.file;

import domain.expression.IExpression;
import domain.state.ProgramState;
import domain.state.file.DescriptorNotExistsException;
import domain.state.file.IFileTable;
import domain.state.heap.IHeap;
import domain.state.heap.InvalidMemoryAddressException;
import domain.state.symbol.ISymbolTable;
import domain.state.symbol.UndeclaredVariableException;
import domain.statement.IStatement;
import domain.type.IntegerType;
import domain.type.StringType;
import domain.value.IValue;
import domain.value.IntegerValue;
import domain.value.StringValue;
import domain.type.IllegalTypeException;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFileStatement implements IStatement
{
    private IExpression filepathExpression;
    private String variableName;

    @Override
    public ProgramState execute(ProgramState state)
            throws IllegalTypeException, UndeclaredVariableException, DescriptorNotExistsException,
            IOException, InvalidMemoryAddressException
    {
        ISymbolTable symbolTable = state.getSymbolTable();
        IHeap heap = state.getHeap();
        IFileTable fileTable = state.getFileTable();

        IValue variable = symbolTable.queryVariable(variableName);
        if(!(variable instanceof IntegerValue))
            throw new IllegalTypeException(this.toString(), new IntegerType(), variable.getType());

        IValue filepath = filepathExpression.evaluate(symbolTable, heap);
        if(!(filepath instanceof StringValue))
            throw new IllegalTypeException(this.toString(), new StringType(), filepath.getType());

        BufferedReader reader = fileTable.getDescriptor((StringValue) filepath);
        String line = reader.readLine();
        IntegerValue newValue = (line.length() != 0) ?
                new IntegerValue(Integer.parseInt(line)) : new IntegerType().defaultValue();
        symbolTable.updateVariable(variableName, newValue);
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
