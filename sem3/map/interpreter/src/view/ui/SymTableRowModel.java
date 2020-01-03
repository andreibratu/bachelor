package view.ui;

import domain.value.IValue;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

import java.util.Map;

@SuppressWarnings("unused")
public class SymTableRowModel
{
    private final StringProperty variableName;
    private final StringProperty value;

    public SymTableRowModel(Map.Entry<String, IValue<?>> symTableEntry)
    {
        variableName = new SimpleStringProperty(symTableEntry.getKey());
        value = new SimpleStringProperty(symTableEntry.getValue().toString());
    }

    public String getVariableName() {
        return variableName.get();
    }

    public StringProperty variableNameProperty() {
        return variableName;
    }

    public void setVariableName(String variableName) {
        this.variableName.set(variableName);
    }

    public String getValue() {
        return value.get();
    }

    public StringProperty valueProperty() {
        return value;
    }

    public void setValue(String value) {
        this.value.set(value);
    }
}
