package exceptions;

public class MyEmptyStackException extends ADTException {
    public MyEmptyStackException() {
        super("Empty stack!");
    }

    public MyEmptyStackException(String message) {
        super(message);
    }
}
