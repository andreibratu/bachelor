package domain.statement.print;

import domain.expression.IExpression;
import domain.state.ProgramState;
import domain.state.heap.IHeap;
import domain.state.heap.InvalidMemoryAddressException;
import domain.state.symbol.ISymbolTable;
import domain.state.symbol.UndeclaredVariableException;
import domain.statement.IStatement;
import domain.value.IValue;
import domain.type.IllegalTypeException;

import java.util.List;

public class PrintStatement implements IStatement
{
    private IExpression expression;

    public PrintStatement(IExpression expression)
    {
        this.expression = expression;
    }

    public String toString() {
        return "print("+ expression.toString()+")";
    }

    @Override
    public ProgramState execute(ProgramState state)
            throws IllegalTypeException, UndeclaredVariableException, InvalidMemoryAddressException
    {
        List<IValue> list = state.getOut();
        ISymbolTable table = state.getSymbolTable();
        IHeap heap = state.getHeap();

        list.add(this.expression.evaluate(table, heap));
        return state;
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        PrintStatement clone = (PrintStatement) super.clone();
        clone.expression = (IExpression) this.expression.clone();
        return clone;
    }
}
