package exceptions;

public class MyFileAlreadyOpenedException extends MyException {
    public MyFileAlreadyOpenedException(String message) {
        super(message);
    }
}
