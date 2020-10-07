package repository;

import domain.Order;
import domain.Pair;
import domain.Product;

import java.util.List;

public interface InventoryRepository
{
    void addProduct(Product product, int quantity);

    void executeOrder(List<Pair<Product, Integer>> items);

    void reset();

    Order buildReport();
}
