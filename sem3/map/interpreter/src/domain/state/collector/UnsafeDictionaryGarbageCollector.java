package domain.state.collector;

import domain.state.heap.DictionaryHeap;
import domain.state.symbol.DictSymbolTable;
import domain.value.IValue;
import domain.value.ReferenceValue;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class UnsafeDictionaryGarbageCollector implements IGarbageCollector
{
    private final DictSymbolTable symbolTable;
    private final DictionaryHeap heap;

    public UnsafeDictionaryGarbageCollector(DictSymbolTable symbolTable, DictionaryHeap heap)
    {
        this.symbolTable = symbolTable;
        this.heap = heap;
    }

    private List<Integer> getAddressesFromSymbolTable()
    {
        return this.symbolTable.getDictionary().values().stream()
                .filter(v -> v instanceof ReferenceValue)
                .map(v -> ((ReferenceValue) v).getValue())
                .collect(Collectors.toList());
    }

    @Override
    public void free()
    {
        List<Integer> addresses = this.getAddressesFromSymbolTable();
        Map<Integer, IValue<?>> beforeHeap = this.heap.getContent();
        Map<Integer, IValue<?>> freedHeap = beforeHeap.entrySet().stream()
                .filter(e -> addresses.contains(e.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
        this.heap.setContent((HashMap<Integer, IValue<?>>) freedHeap);
    }
}
