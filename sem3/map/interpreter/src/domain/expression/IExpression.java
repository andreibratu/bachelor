package domain.expression;

import domain.state.heap.DictionaryHeap;
import domain.state.heap.InvalidMemoryAddressException;
import domain.state.symbol.DictSymbolTable;
import domain.state.symbol.UndeclaredVariableException;
import domain.type.IType;
import domain.type.IllegalTypeException;
import domain.value.IValue;

import java.util.Map;

public interface IExpression extends Cloneable
{
    IValue<?> evaluate(DictSymbolTable table, DictionaryHeap heap) throws IllegalTypeException, UndeclaredVariableException, InvalidMemoryAddressException;

    IType typeCheck(Map<String, IType> typeEnv) throws IllegalTypeException;

    Object clone() throws CloneNotSupportedException;
}
