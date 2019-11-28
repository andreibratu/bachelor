package domain.statement.file;

import domain.expression.IExpression;
import domain.state.ProgramState;
import domain.state.file.DescriptorExistsException;
import domain.state.file.FileDoesNotExistException;
import domain.state.file.IFileTable;
import domain.state.heap.IHeap;
import domain.state.heap.InvalidMemoryAddressException;
import domain.state.symbol.ISymbolTable;
import domain.state.symbol.UndeclaredVariableException;
import domain.statement.IStatement;
import domain.type.StringType;
import domain.value.IValue;
import domain.value.StringValue;
import domain.type.IllegalTypeException;

import java.io.FileNotFoundException;

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
            DescriptorExistsException, InvalidMemoryAddressException, FileNotFoundException
    {
        ISymbolTable symbolTable = state.getSymbolTable();
        IFileTable fileTable = state.getFileTable();
        IHeap heap = state.getHeap();

        IValue result = filepath.evaluate(symbolTable, heap);
        if(!(result instanceof StringValue))
            throw new IllegalTypeException(this.toString(), new StringType(), result.getType());
        fileTable.createDescriptor((StringValue) result);
        return state;
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
