package domain.state.heap;

public class InvalidMemoryAddressException extends Exception {

    public InvalidMemoryAddressException(String context, int address) {
        super(context + "Address " + address + " is invalid");
    }
}
