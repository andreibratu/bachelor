package repository;

public class RepositoryFullException extends Exception {
    @Override
    public String getMessage() {
        return "Repository is full.";
    }
}
