package domain.statement.variable;

import domain.expression.IExpression;
import domain.state.ProgramState;
import domain.state.heap.IHeap;
import domain.state.heap.InvalidMemoryAddressException;
import domain.state.symbol.ISymbolTable;
import domain.state.symbol.UndeclaredVariableException;
import domain.statement.IStatement;
import domain.type.IType;
import domain.type.IllegalTypeException;
import domain.value.IValue;

import java.util.Map;

public class VariableAssignmentStatement implements IStatement
{
    private String id;
    private IExpression expression;

    public VariableAssignmentStatement(String id, IExpression expression)
    {
        this.id = id;
        this.expression = expression;
    }

    @Override
    public String toString() {
        return this.id + " = " + this.expression.toString();
    }

    @Override
    public Map<String, IType> typeCheck(Map<String, IType> typeEnv) throws IllegalTypeException
    {
        IType typeVar = typeEnv.get(id);
        IType typeExpression = expression.typeCheck(typeEnv);
        if(!typeVar.equals(typeExpression)) throw new IllegalTypeException(this.toString(), typeVar, typeExpression);
        return typeEnv;
    }

    @Override
    public ProgramState execute(ProgramState state)
            throws IllegalTypeException, UndeclaredVariableException, InvalidMemoryAddressException
    {
        ISymbolTable symbolTable = state.getSymbolTable();
        IHeap heap = state.getHeap();

        IValue<?> expressionValue = expression.evaluate(symbolTable, heap);
        IType variableType = symbolTable.queryVariable(id).getType();

        if (expressionValue.getType().equals(variableType)) symbolTable.updateVariable(id, expressionValue);
        else throw new IllegalTypeException(id, variableType, expressionValue.getType());

        return null;
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        VariableAssignmentStatement clone = (VariableAssignmentStatement) super.clone();
        clone.id = this.id;
        clone.expression = (IExpression) this.expression.clone();
        return clone;
    }
}
