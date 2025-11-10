package exceptions;

public class FullRepositoryException extends Exception {
    public FullRepositoryException() {
        super("The repository is full!");
    }

    public FullRepositoryException(String message) {
        super(message);
    }
}
