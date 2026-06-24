package exceptions;

public class MyInvalidFileFormatException extends MyException {
    public MyInvalidFileFormatException() {
        super("Invalid line in file.");
    }

    public MyInvalidFileFormatException(String message) {
        super(message);
    }
}
