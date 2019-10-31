package domain.statement;

import adt.IDictionary;
import domain.state.ProgramState;
import domain.value.Value;

public class VarDeclStatement implements IStatement {
    private String name;
    private Value value;

    public VarDeclStatement(String name, Value value)
    {
        this.name = name;
        this.value = value;
    }

    @Override
    public ProgramState execute(ProgramState state) throws Exception {
        IDictionary<String, Value> symbolTable = state.getSymbolTable();
        if (symbolTable.isDefined(this.name)) throw new Exception("Variable with given name already exists");
        symbolTable.add(name, value);
        return state;
    }

    @Override
    public IStatement deepCopy() {
        return new VarDeclStatement(name, value.deepCopy());
    }
}
