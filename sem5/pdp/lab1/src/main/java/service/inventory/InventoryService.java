package service.inventory;

import domain.Pair;
import domain.Product;
import repository.InventoryRepository;
import service.RandomService;
import domain.command.AddInventoryCommand;
import domain.command.BuildReportCommand;
import domain.command.ExecuteOrderCommand;
import domain.command.InventoryCommand;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;

public class InventoryService
{
    private static List<Pair<Product, Integer>> generateRandomInventory()
    {
        List<String> productNames = Stream
                    .generate(() -> RandomService.generateRandomString(RandomService.generateRandomInt(7, 8)))
                    .limit(500)
                    .collect(Collectors.toList());
        System.out.println("Generated inventory..");
        return productNames.stream()
                .map(name -> new Product(name, RandomService.generateRandomDouble(5, 10)))
                .map(product -> new Pair<>(product, RandomService.generateRandomInt(5000, 50000)))
                .collect(Collectors.toList());
    }

    private static List<Pair<Product, Integer>> buildChunks(List<Pair<Product, Integer>> inventory)
    {
        List<Pair<Product, Integer>> chunks = new ArrayList<>();
        inventory.forEach(productQuantityPair -> {
            Product product = productQuantityPair.getKey();
            int quantity = productQuantityPair.getValue();
            while (quantity > 0)
            {
                int uppBound = Math.max(1, quantity / 10) + 1;
                int ordered = RandomService.generateRandomInt(1, uppBound);
                chunks.add(new Pair<>(product, ordered));
                quantity -= ordered;
            }
        });
        System.out.println("Divided into chunks..");
        return chunks;
    }

    private static List<List<Pair<Product, Integer>>> buildOrders(List<Pair<Product, Integer>> chunks)
    {
        List<List<Pair<Product, Integer>>> orders = new ArrayList<>();
        List<Pair<Product, Integer>> currOrder = new ArrayList<>();
        for(Pair<Product, Integer> chunk: chunks)
        {
            boolean includeInCurrent = currOrder.size() == 0 ||
                    RandomService.generateRandomDouble(0, 1) <= 0.2;
            if (includeInCurrent)
            {
                currOrder.add(chunk);
            }
            else
            {
                orders.add(new ArrayList<>(currOrder));
                currOrder = new ArrayList<>();
            }
        }
        System.out.println("Built orders..");
        return orders;
    }

    public static List<Function<InventoryRepository, InventoryCommand>> buildSchedule()
    {
        List<Pair<Product, Integer>> inventory = InventoryService.generateRandomInventory();
        List<Pair<Product, Integer>> subs = InventoryService.buildChunks(inventory);
        Collections.shuffle(subs);
        List<List<Pair<Product, Integer>>> orders = buildOrders(subs);

        List<Function<InventoryRepository, InventoryCommand>> finalListCommands = new ArrayList<>();

        // Build intermediate commands - order execution and reports
        orders.forEach(order ->
                finalListCommands.add(repository -> new ExecuteOrderCommand(repository, order))
        );
        IntStream.range(0, orders.size() / 10).forEach(idx -> finalListCommands.add(
                BuildReportCommand::new
        ));
        // Shuffle middle orders
        Collections.shuffle(finalListCommands);
        // Add command to populate inventory at beginning of schedule
        finalListCommands.add(0, repository -> new AddInventoryCommand(repository, subs));
        // Add final report per requirements
        finalListCommands.add(BuildReportCommand::new);
        System.out.println("Generated schedule..");
        return finalListCommands;
    }
}
