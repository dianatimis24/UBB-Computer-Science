package exceptions;

public class MyKeyNotFoundException extends ADTException {
    public MyKeyNotFoundException() {
        super("Key not found!");
    }

    public MyKeyNotFoundException(String message) {
        super(message);
    }
}
