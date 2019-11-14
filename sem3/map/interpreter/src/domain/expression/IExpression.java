package domain.expression;

import domain.state.heap.IHeap;
import domain.state.heap.InvalidMemoryAddressException;
import domain.state.symbol.ISymbolTable;
import domain.type.IllegalTypeException;
import domain.value.IValue;
import domain.state.symbol.UndeclaredVariableException;

public interface IExpression extends Cloneable
{
    IValue evaluate(ISymbolTable table, IHeap heap) throws IllegalTypeException, UndeclaredVariableException, InvalidMemoryAddressException;

    Object clone() throws CloneNotSupportedException;
}
