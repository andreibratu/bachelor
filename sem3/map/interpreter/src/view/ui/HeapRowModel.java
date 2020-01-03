package view.ui;

import domain.value.IValue;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

import java.util.Map;

@SuppressWarnings("unused")
public class HeapRowModel
{
    private final SimpleStringProperty address;
    private final SimpleStringProperty value;

    public HeapRowModel(Map.Entry<Integer, IValue<?>> heapEntry)
    {
        this.address = new SimpleStringProperty(heapEntry.getKey().toString());
        this.value = new SimpleStringProperty(heapEntry.getValue().toString());
    }

    public String getAddress() {
        return address.get();
    }

    public StringProperty addressProperty() {
        return address;
    }

    public void setAddress(String address) {
        this.address.set(address);
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
