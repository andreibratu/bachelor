package domain;

import java.util.HashMap;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Order
{
    final private HashMap<Product, Integer> soldProducts;

    public Order(List<Pair<Product, Integer>> items)
    {
        soldProducts = new HashMap<>();
        items.forEach(
            item -> soldProducts.compute(
                item.getKey(),
                (k, v) -> (v == null) ? item.getValue() : v + item.getValue()
            )
        );
    }

    public List<Pair<Product, Integer>> getSubs()
    {
        return soldProducts.entrySet().stream()
                .map(entry -> new Pair<>(entry.getKey(), entry.getValue()))
                .collect(Collectors.toList());
    }

    public double getOrderPrice()
    {
        return soldProducts.entrySet().stream()
                .map(entry -> entry.getKey().getPrice() * entry.getValue())
                .reduce((double) 0, Double::sum);
    }

    @Override
    public String toString()
    {
        Stream<String> entriesToStr = soldProducts.entrySet().stream()
                .map(entry ->
                        entry.getKey().toString() +
                        entry.getValue().toString() +
                        " | " +
                        entry.getKey().getPrice() * entry.getValue()
                );
        String finalPrice = String.valueOf(this.getOrderPrice());
        entriesToStr = Stream.concat(entriesToStr, Stream.of(finalPrice));
        return entriesToStr.collect(Collectors.joining("\n", "====\n", "====\n"));
    }
}
