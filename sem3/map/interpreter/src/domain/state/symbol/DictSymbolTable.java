package domain.state.symbol;

import domain.value.IValue;

import java.util.HashMap;
import java.util.Map;

public class DictSymbolTable
{
    private final HashMap<String, IValue<?>> dictionary;

    public DictSymbolTable()
    {
        this.dictionary = new HashMap<>();
    }

    public DictSymbolTable(DictSymbolTable table)
    {
        this.dictionary = new HashMap<>();
        for(Map.Entry<String, IValue<?>> entry : table.dictionary.entrySet())
        {
            String key = entry.getKey();
            IValue<?> value = null;
            try {
                value = (IValue<?>) (entry.getValue()).clone();
            } catch (CloneNotSupportedException e) {
                e.printStackTrace();
            }
            dictionary.put(key, value);
        }
    }

    public void createVariable(String variable, IValue<?> value) throws VariableAlreadyDefinedException
    {
        if(dictionary.containsKey(variable)) throw new VariableAlreadyDefinedException(variable);
        dictionary.put(variable, value);
    }

    public void updateVariable(String variable, IValue<?> value) throws UndeclaredVariableException
    {
        if (!dictionary.containsKey(variable)) throw new UndeclaredVariableException(variable);
        dictionary.put(variable, value);
    }

    public IValue<?> queryVariable(String variable) throws UndeclaredVariableException
    {
        if(!dictionary.containsKey(variable)) throw new UndeclaredVariableException(variable);
        return dictionary.get(variable);
    }

    @Override
    public String toString()
    {
        StringBuilder builder = new StringBuilder();
        builder.append("SYMBOLS\n");
        for(Map.Entry<String, IValue<?>> entry : dictionary.entrySet())
        {
            builder.append(entry.getKey()).append(" -> ").append(entry.getValue().toString()).append("\n");
        }
        return builder.toString();
    }
//
//    public HashMap<String, IValue<?>> getContent()
//    {
//        HashMap<String, IValue<?>> clone = new HashMap<>();
//        for(Map.Entry<String, IValue<?>> entry : dictionary.entrySet())
//        {
//            String key = entry.getKey();
//            IValue<?> value = null;
//            try
//            {
//                value = (IValue<?>) (entry.getValue()).clone();
//            } catch (CloneNotSupportedException e)
//            {
//                e.printStackTrace();
//            }
//            clone.put(key, value);
//        }
//        return clone;
//    }

    public HashMap<String, IValue<?>> getDictionary() { return dictionary; }
}
