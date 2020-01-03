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
import domain.type.StringType;
import domain.value.IValue;
import domain.value.StringValue;
import domain.type.IllegalTypeException;

import java.io.IOException;
import java.util.Map;

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
        DictSymbolTable symbolTable = state.getSymbolTable();
        DictionaryFileTable fileTable = state.getFileTable();
        DictionaryHeap heap = state.getHeap();

        IValue<?> filepath = filePathExpression.evaluate(symbolTable, heap);
        if(!(filepath.getType() instanceof StringType))
            throw new IllegalTypeException(this.toString(), new StringType(), filepath.getType());
        fileTable.closeDescriptor((StringValue) filepath);
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
