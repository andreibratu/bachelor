package domain.statement.file;

import domain.expression.IExpression;
import domain.state.ProgramState;
import domain.state.file.DescriptorExistsException;
import domain.state.file.IFileTable;
import domain.state.heap.IHeap;
import domain.state.heap.InvalidMemoryAddressException;
import domain.state.symbol.ISymbolTable;
import domain.state.symbol.UndeclaredVariableException;
import domain.statement.IStatement;
import domain.type.IType;
import domain.type.StringType;
import domain.value.IValue;
import domain.value.StringValue;
import domain.type.IllegalTypeException;

import java.io.FileNotFoundException;
import java.util.Map;

public class OpenRFileStatement implements IStatement
{
    private IExpression filePathExpression;

    public OpenRFileStatement(IExpression expression)
    {
        this.filePathExpression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state)
            throws IllegalTypeException, UndeclaredVariableException,
            DescriptorExistsException, InvalidMemoryAddressException, FileNotFoundException
    {
        ISymbolTable symbolTable = state.getSymbolTable();
        IFileTable fileTable = state.getFileTable();
        IHeap heap = state.getHeap();

        IValue<?> result = filePathExpression.evaluate(symbolTable, heap);
        if(!(result instanceof StringValue))
            throw new IllegalTypeException(this.toString(), new StringType(), result.getType());
        fileTable.createDescriptor((StringValue) result);
        return null;
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
    public String toString() {
        return "open(" + this.filePathExpression.toString() + ")";
    }

    @Override
    public Object clone() throws CloneNotSupportedException
    {
        OpenRFileStatement clone = (OpenRFileStatement) super.clone();
        clone.filePathExpression = (IExpression) this.filePathExpression.clone();
        return clone;
    }
}
