package adt.dictionary;

public class InvalidKeyException extends Exception
{
    public InvalidKeyException()
    {
        super("Key does not exist in the dictionary!");
    }
}
