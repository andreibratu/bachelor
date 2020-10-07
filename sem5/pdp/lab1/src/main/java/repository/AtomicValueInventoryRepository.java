package repository;

import domain.Order;
import domain.Pair;
import domain.Product;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Collectors;

public class AtomicValueInventoryRepository implements InventoryRepository
{
    private final HashMap<Product, AtomicInteger> inventory;
    private final List<Order> executedOrders;

    public AtomicValueInventoryRepository()
    {
        inventory = new HashMap<>();
        executedOrders = new ArrayList<>();
    }

    @Override
    public void addProduct(Product product, int quantity)
    {
        if (inventory.get(product) == null)
        {
            inventory.put(product, new AtomicInteger(quantity));
        }
        else
        {
            inventory.get(product).addAndGet(quantity);
        }
    }

    @Override
    public void executeOrder(List<Pair<Product, Integer>> items)
    {
        try
        {
            Order newOrder = new Order(items);
            items.forEach(item -> {
                inventory.get(item.getKey()).addAndGet(-item.getValue());
            });
            synchronized (executedOrders)
            {
                executedOrders.add(newOrder);
            }
        }
        catch (NullPointerException e)
        {
            e.printStackTrace();
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
