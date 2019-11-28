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
import domain.type.StringType;
import domain.value.IValue;
import domain.value.StringValue;
import domain.type.IllegalTypeException;

import java.io.IOException;

public class CloseRFileStatement implements IStatement
{
    private IExpression filePathExpression;

    public CloseRFileStatement(IExpression filePathExpression)
    {
        this.filePathExpression = filePathExpression;
    }

    @Override
    public ProgramState execute(ProgramState state)
            throws IllegalTypeException, UndeclaredVariableException, DescriptorNotExistsException,
            InvalidMemoryAddressException, IOException
    {
        ISymbolTable symbolTable = state.getSymbolTable();
        IFileTable fileTable = state.getFileTable();
        IHeap heap = state.getHeap();

        IValue filepath = filePathExpression.evaluate(symbolTable, heap);
        if(!(filepath.getType() instanceof StringType))
            throw new IllegalTypeException(this.toString(), new StringType(), filepath.getType());
        fileTable.closeDescriptor((StringValue) filepath);
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
