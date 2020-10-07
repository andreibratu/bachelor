package domain;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
@AllArgsConstructor
public class Product
{
    private String name;
    private double price;

    @Override
    public String toString() {
        return name + " " + price;
    }
}
