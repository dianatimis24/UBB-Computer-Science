package exceptions;

public class MyIndexOutOfBoundsException extends ADTException {
    public MyIndexOutOfBoundsException() {
        super("Index out of bounds!");
    }

    public MyIndexOutOfBoundsException(String message) {
        super(message);
    }
}
