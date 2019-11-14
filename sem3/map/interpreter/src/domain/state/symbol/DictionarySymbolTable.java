package domain.state.symbol;

import domain.value.IValue;

import java.util.HashMap;

public class DictionarySymbolTable implements ISymbolTable
{
    private HashMap<String, IValue> dictionary;

    public DictionarySymbolTable()
    {
        this.dictionary = new HashMap<>();
    }

    @Override
    public void createVariable(String variable, IValue value) throws VariableAlreadyDefinedException
    {
        if(dictionary.containsKey(variable)) throw new VariableAlreadyDefinedException(variable);
        dictionary.put(variable, value);
    }

    @Override
    public void updateVariable(String variable, IValue value) throws UndeclaredVariableException
    {
        if (!dictionary.containsKey(variable)) throw new UndeclaredVariableException(variable);
        dictionary.put(variable, value);
    }

    @Override
    public IValue queryVariable(String variable) throws UndeclaredVariableException
    {
        if(!dictionary.containsKey(variable)) throw new UndeclaredVariableException(variable);
        return dictionary.get(variable);
    }

    @Override
    @SuppressWarnings("unchecked")
    public Object clone() throws CloneNotSupportedException
    {
        DictionarySymbolTable clone = (DictionarySymbolTable) super.clone();
        clone.dictionary = (HashMap<String, IValue>) dictionary.clone();
        return clone;
    }
}
