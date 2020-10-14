package service;

import lombok.SneakyThrows;
import lombok.ToString;
import repository.InventoryRepository;
import domain.command.InventoryCommand;

import java.io.File;
import java.io.FileWriter;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

@ToString
public class ExecutionService
{
    private final InventoryRepository repository;
    private final List<Function<InventoryRepository, InventoryCommand>> schedule;
    private final Integer threads;
    private final Integer trials;
    private final String reportFileName;

    public ExecutionService(
            InventoryRepository repository,
            List<Function<InventoryRepository, InventoryCommand>> schedule,
            Integer threads,
            Integer trials,
            String reportFileName
    )
    {
        this.repository = repository;
        this.schedule = schedule;
        this.threads = threads;
        this.trials = trials;
        this.reportFileName = reportFileName;
    }

    @SneakyThrows
    private double runTrial(int trialIdx)
    {
        ExecutorService executor = Executors.newFixedThreadPool(threads);
        // Fill in the repository
        List<InventoryCommand> commands = schedule.stream()
                .map(fnc ->  fnc.apply(repository))
                .collect(Collectors.toList());

        List<InventoryCommand> parallel_tasks = commands.subList(1, commands.size() - 1);
        // Start execution
        Long startTime = System.currentTimeMillis();
        // Fill in inventory
        commands.get(0).call();
        // Run intermediate operations in parallel
        executor.invokeAll(parallel_tasks);
        // Wait for threads to join
        executor.shutdown();
        // Run final report
        commands.get(commands.size()-1).call();

        Long endTime = System.currentTimeMillis();
        System.out.println("Finished trial " + trialIdx + "..");
        return (double) (endTime - startTime) / 1000;
    }

    @SneakyThrows
    public void execute()
    {
        double averageRunTimeSeconds = IntStream.range(0, trials)
                .mapToDouble(idx -> {
                    repository.reset();
                    return runTrial(idx);
                })
                .average()
                .orElseThrow();
        String arch = System.getProperty("os.arch");
        int availableThreads = Runtime.getRuntime().availableProcessors();
        String repositoryType = repository.toString();

        String finalReportPath = reportFileName + "-results";
        File reportFile = new File(finalReportPath);
        //noinspection ResultOfMethodCallIgnored
        reportFile.createNewFile();
        FileWriter writer = new FileWriter(finalReportPath);

        writer.write("Repository: " + repositoryType + "\n");
        writer.write("Architecture: " + arch + "\n");
        writer.write("Logical number of cores: " + availableThreads + "\n");
        writer.write("Used threads: " + threads + "\n");
        writer.write("Average run time: " + averageRunTimeSeconds + "\n");
        writer.write("Number of trials: " + trials + "\n");
        writer.close();
    }
}
