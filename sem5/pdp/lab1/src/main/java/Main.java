import repository.AtomicValueInventoryRepository;
import repository.GlobalLockInventoryRepository;
import repository.InventoryRepository;
import service.ExecutionService;
import service.inventory.InventoryService;
import domain.command.InventoryCommand;

import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.function.Function;

public class Main
{
    public static void main(String[] args)
    {
        List<Function<InventoryRepository, InventoryCommand>> schedule = InventoryService.buildSchedule();
        List<ExecutionService> experiments = List.of(
            new ExecutionService(
                    new GlobalLockInventoryRepository(),
                    schedule,
                    3,
                    50,
                    "global-3-500"
            ),
            new ExecutionService(
                new GlobalLockInventoryRepository(),
                schedule,
                5,
                50,
                "global-5-500"
            ),
            new ExecutionService(
                new GlobalLockInventoryRepository(),
                schedule,
                    10,
                    50,
                    "global-10-50-500"
            ),
            new ExecutionService(
                    new GlobalLockInventoryRepository(),
                    schedule,
                    20,
                    50,
                    "global-20-50-500"
            ),
            new ExecutionService(
                new AtomicValueInventoryRepository(),
                schedule,
                3,
                50,
                "atomic-3-50-500"
            ),
            new ExecutionService(
                    new AtomicValueInventoryRepository(),
                    schedule,
                    5,
                    50,
                    "atomic-5-50-500"
            ),
            new ExecutionService(
                    new AtomicValueInventoryRepository(),
                    schedule,
                    10,
                    50,
                    "atomic-10-50-500"
            ),
            new ExecutionService(
                    new AtomicValueInventoryRepository(),
                    schedule,
                    20,
                    50,
                    "atomic-20-50-500"
            ),
            new ExecutionService(
                    new GlobalLockInventoryRepository(),
                    schedule,
                    1,
                    50,
                    "global-1-50-500"
            ),
            new ExecutionService(
                    new AtomicValueInventoryRepository(),
                    schedule,
                    1,
                    50,
                    "atomic-1-50-500"
            )
        );
        AtomicInteger idx = new AtomicInteger();
        experiments.forEach(experiment -> {
            experiment.execute();
            idx.addAndGet(1);
            System.out.println("Finished experiment " + idx.get() + "..");
        });
    }
}
