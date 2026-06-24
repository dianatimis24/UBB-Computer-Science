package exceptions;

public class MyHeapAddressNotAssociatedException extends MyException {
    public MyHeapAddressNotAssociatedException(String message) {
        super(message);
    }
    public MyHeapAddressNotAssociatedException(int address) {
        super("Address " + address + " in heap is not associated to a value.");
    }
}
