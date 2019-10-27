package view;

import controller.Controller;
import repository.IRepository;
import repository.MemoryRepository;

public class Main {
    private static IRepository repository = new MemoryRepository();
    private static Controller controller = new Controller(repository);

    public static void main(String[] args) {
    }
}