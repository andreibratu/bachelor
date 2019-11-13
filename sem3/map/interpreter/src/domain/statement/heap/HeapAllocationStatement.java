package domain.statement.heap;


import adt.dictionary.IDictionary;
import adt.dictionary.InvalidKeyException;
import domain.expression.IExpression;
import domain.state.Heap;
import domain.state.ProgramState;
import domain.statement.IStatement;
import domain.type.IType;
import domain.type.ReferenceType;
import domain.value.IValue;
import domain.value.ReferenceValue;
import exception.io.DescriptorExistsException;
import exception.io.DescriptorNotExistsException;
import exception.io.FileDoesNotExistException;
import exception.type.IllegalTypeException;
import exception.variable.UndeclaredVariableException;
import exception.variable.VariableAlreadyDefinedException;

import java.io.IOException;
import java.sql.Ref;

public class HeapAllocationStatement implements IStatement {

    private String variableName;
    private IExpression expression;

    public HeapAllocationStatement(String variableName, IExpression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws IllegalTypeException, UndeclaredVariableException
    {
        IDictionary<String, IValue> symbolTable = state.getSymbolTable();
        Heap heap = state.getHeap();
        return state;
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        return null;
    }
}
