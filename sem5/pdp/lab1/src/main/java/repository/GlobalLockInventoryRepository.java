package repository;

import domain.Order;
import domain.Pair;
import domain.Product;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.stream.Collectors;

public class GlobalLockInventoryRepository implements InventoryRepository
{
    private final HashMap<Product, Integer> inventory;
    private final List<Order> executedOrders;

    public GlobalLockInventoryRepository()
    {
        inventory = new HashMap<>();
        executedOrders = new ArrayList<>();
    }

    @Override
    public void addProduct(Product product, int quantity)
    {
        synchronized (inventory)
        {
            inventory.compute(product, (k, v) -> (v == null) ? quantity : (quantity + v));
        }
    }

    @Override
    public void executeOrder(List<Pair<Product, Integer>> items)
    {
        synchronized (inventory)
        {
            synchronized (executedOrders)
            {
                Order newOrder = new Order(items);
                items.forEach(item -> inventory.computeIfPresent(item.getKey(), (k, v) -> (v - item.getValue())));
                // No need to lock executedOrders since only one thread can get inside this block
                executedOrders.add(newOrder);
            }
        }
    }

    @Override
    public Order buildReport()
    {
        synchronized (executedOrders)
        {
            List<Pair<Product, Integer>> joinedSubs = executedOrders.stream()
                    .map(Order::getSubs)
                    .flatMap(Collection::stream)
                    .collect(Collectors.toList());
            return new Order(joinedSubs);
        }
    }

    @Override
    public void reset()
    {
        inventory.clear();
        executedOrders.clear();
    }
}
